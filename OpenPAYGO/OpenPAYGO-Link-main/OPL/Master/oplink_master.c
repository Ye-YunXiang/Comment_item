/*
 * Filename:    oplink_master.c
 * Project:     OpenPAYGO Link
 * Author:      Daniel Nedosseikine
 * Company:     Solaris Offgrid
 * Created on:  13/01/2020
 * Description: Master node functions.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "crc16.h"
#include "oplink_common.h"
#include "oplink_com.h"
#include "oplink_com_private.h"
#include "slave_list_private.h"
#include "oplink_master.h"

#define CYCLES_PER_SECOND 20 // 1000 / LOOP_TIME    循环时间

static uint8_t new_slave_addr;          //新的从设备地址

bool opl_push_request(uint8_t *uid, uint8_t *data, uint8_t len) {       //发送请求
    uint8_t dest = map_uid_to_addr(uid);
    if(dest == 0) return false; // No uid match     不匹配ID
    return push_request(dest, data, len, true); // Wait for reply   等待回复
}

bool opl_push_broadcast(uint8_t *data, uint8_t len) {           //发送广播
    return push_request(0x00, data, len, false); // Don't wait for reply        不要等待回复
}

static void handle_new_slave(uint8_t *args) {
    new_slave_addr = slave_list_available();
    uint8_t temp_buf[5];
    if(new_slave_addr) {
        switch(args[0]) { // Test the version       测试版本
            case 0x01:
                memcpy(temp_buf, args + 1, 4);
                temp_buf[4] = new_slave_addr;
                opl_send_cmd(DEFAULT_ADDR, FIND, temp_buf, 5, true, true);
                break;
        }
    }
}

static void handle_ack(uint8_t *args, uint8_t len) {            // 确认句柄
    uint8_t addr_buffer;
    switch(get_last_cmd()) {    // 得到末尾的命令
        case FIND:              // 查找
            opl_send_cmd(new_slave_addr, GET_UID, NULL, 0, true, true);
            break;
        case GET_UID:           // 得到用户ID
            if(len <= UID_SIZE) {
                if(len != 0) {
                    slave_list_add(new_slave_addr, args, len);
                }
                else {
                    addr_buffer = new_slave_addr + '0';
                    slave_list_add(new_slave_addr, &addr_buffer, 1);
                }

                opl_send_cmd(new_slave_addr, PING, NULL, 0, true, true);
            }
            break;
        case PING:
            slave_set_ping_period(get_last_dest(), PING_PERIOD);
            break;
    }
}

void opl_init() {
    OPL_LIN_INIT(); // Configure write enable pin   配置写使能引脚
    OPL_LIN_ENABLE_TX();

    opl_node_set_addr(MASTER_ADDR);
    slave_list_init();          // 从设备列表初始化
    request_queue_init();       // 请求队列初始化
    // Set UART to 9-N-1 mode @ 19200 baud with addr 0x0F   设置编码、波特率、写入地址。
    opl_node_set_addr(MASTER_ADDR);
    OPL_UART_INIT(MASTER_ADDR, uart_rx_callback);
}

/* Route the OPLink internal commands. This is called form opl_parse(). It might
 * seem unsafe, but ACK is received only after an internal request, and SIGNAL
 * will only be sent by a slave that made sure that the bus is idle.
 * 路由OPLink内部命令。这被称为form opl_parse()。它可能看起来不安全，
 * 但是ACK只有在内部请求之后才会被接收，
 * 而SIGNAL将只由确保总线处于空闲状态的从服务器发送。
 */
void route_command(uint8_t *buf, uint8_t len) {     // 传递指令
    //if(last_request.reply != pending) {
        switch(buf[0]){
            case SIGNAL:
                handle_new_slave(buf + 1);
                break;
            case ACK:
                handle_ack(buf + 1, --len); // We know len is at least 1
                break;
        }
    //}
}

void opl_keep_alive() {                 // 保持OPL的活动
    static uint32_t old_millis = 0;
    static uint8_t seconds = 0;

    if(OPL_MILLIS() - old_millis > LOOP_TIME) {
        old_millis = OPL_MILLIS();

        if(seconds++ == CYCLES_PER_SECOND) {
            seconds = 0;
            slave_list_ping_tick(); // Just tick      从设备目录ping记号
        }

        if(update_node_state() == RECEIVE_TIMEOUT_ERROR) {
            // Increase slave ping error if it didn't reply to the PING     没有响应Ping就增加从Ping的错误
            if(get_last_cmd() == PING)
                slave_ping_error(get_last_dest());
        }

        if(safe_to_send()) {        // 安全的向前发送
            // Ping has higher priority so it is checked first  Ping具有更高优先级，所以先检测
            uint8_t ping_addr = next_slave_ping();

            if(ping_addr > 0) // Addresses start from 1, 0 means no need to ping    地址从1开始，0不需要Ping
                opl_send_cmd(ping_addr, PING, NULL, 0, true, false);
            else // Dispatch next request if any        调度下一个请求
                dispatch_request();
        }
    }
}
