// copied from:
// https://github.com/platformio/platform-ststm32/blob/master/examples/zephyr-blink/src/main.c

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "oc/include/oc_api.h"
#include "oc/messaging/coap/coap.h"

#include "nxp_channel.h"
#include "nxp_common.h"
#include "nxp_keycode.h"

// Module to convert Nexus Channel messages to
// 'on the wire' representation.
// 在线传递消息？？？
#include "product_data_link.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <string.h>
#include <zephyr.h>

// Flash filesystem, specific to this implementation 实现flash文件管理系统
#include "flash_filesystem.h"
#include "payg_led_display.h"
#include "product_nexus_identity.h"
#include "product_payg_state_manager.h"

// Interactive UART 'command console', for demonstration purposes
// 交互式uart控制台，用于演示目的
#include "demo_console.h"

// Zephyr logging for easier demonstration purposes
// 为了更容易演示Zephyr记录
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

static void _assign_nexus_payg_identities(void)
{
    // Store testing values to flash for:   存储测试值到flash：
    // Nexus ID / PAYG ID       支付ID
    // Keycode Secret Key   密钥
    // Channel Secret Key   通道密钥
    // NOTE: In production, these should vary from device to device!    在生产中因设备而异
    const struct nx_id TEST_NEXUS_ID = {
        0xFFFF, // authority ID 0xFFFF for 'testing'       权限ID，用于测试
        12345678, // arbitrary device ID 12345678 (0x00bc614e)  任何设备ID
    };
    // A fake key just used for demo purposes...    用于演示目的的假密钥
    const struct nx_common_check_key TEST_NEXUS_COMMON_DEMO_SECRET_KEY = {
        {0xDE,
         0xAD,
         0xBE,
         0xEF,
         0x10,
         0x20,
         0x30,
         0x40,
         0x04,
         0x03,
         0x02,
         0x01,
         0xFE,
         0xEB,
         0xDA,
         0xED}};
    product_nexus_identity_set_nexus_id(&TEST_NEXUS_ID);
    product_nexus_identity_set_nexus_keycode_secret_key(
        &TEST_NEXUS_COMMON_DEMO_SECRET_KEY);
    product_nexus_identity_set_nexus_channel_secret_key(
        &TEST_NEXUS_COMMON_DEMO_SECRET_KEY);
}

void main(void)
{
    // Wait 1s for the UART/console to initialize
    // 等待15秒UART进行初始化
    k_busy_wait(1 * 1000 * 1000); // us

    // Initialize flash filesystem/NV
    // 初始化Flash文件系统
    if (!flash_filesystem_init())
    {
        // should never reach here  不应该到达这里
        assert(false);
        return;
    }
    // In a real device, this would not happen in every boot in main.c, but
    // 在实际设备中，这不会在main.c中每次引导中发生
    // would happen once in the factory during provisioning
    // 但在工厂配置期间会发生一次
    _assign_nexus_payg_identities();

    // Initialize PAYG LED display hardware
    // 初始化PAYG LED显示硬件
    payg_led_display_init();

    // Initialize internal PAYG state management
    // 初始化内部PAYG状态管理
    product_payg_state_manager_init();

    // Prepare data link, and use
    // 准备数据链接，并使用
    // `nx_channel_network_receive` to process received
    // 处理接收到的进程
    // messages.    消息
    product_data_link_init(&nx_channel_network_receive);

    LOG_INF("---Nexus Embedded Demonstration Started (CONTROLLER)---");

    while (1)
    {
        // Will wait for user input from "demo_console" and loop forever.
        // 等待来自“demo_console”的用户输入并永远循环。
        demo_console_wait_for_user_input();
    }
}
