// copied from:
// https://github.com/platformio/platform-ststm32/blob/master/examples/zephyr-blink/src/main.c

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "oc/include/oc_api.h"
#include "oc/messaging/coap/coap.h"

#include "network.h"
#include "nxp_channel.h"
#include "nxp_common.h"
#include "nxp_keycode.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <string.h>
#include <zephyr.h>

// Flash filesystem, specific to this implementation
#include "flash_filesystem.h"
#include "product_nexus_identity.h"
#include "product_payg_state_manager.h"
// Interactive UART 'command console', for demonstration purposes
#include "demo_console.h"

// Zephyr logging for easier demonstration purposes
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

static void _assign_nexus_payg_identities(void)
{
    // Store testing values to flash for:
    // Nexus ID / PAYG ID
    // Keycode Secret Key
    // Channel Secret Key
    // NOTE: In production, these should vary from device to device!
    const struct nx_id TEST_NEXUS_ID = {
        0xFFFF, // authority ID 0xFFFF for 'testing'        这个ID代表测试
        12345678, // arbitrary device ID 12345678 (0x00bc614e)  任意设备
    };
    // A fake key just used for demo purposes...    用于演示的假密钥
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
    // Wait 1s for the UART/console to initialize       等待1秒控制台初始化
    k_busy_wait(1 * 1000 * 1000); // us

    // Initialize flash filesystem/NV   初始化Flash系统
    if (!flash_filesystem_init())
    {
        // should never reach here
        assert(false);
        return;
    }

    // In a real device, this would not happen in every boot in main.c, but
    // would happen once in the factory during provisioning
    _assign_nexus_payg_identities();        // 分配ID

    // Initialize internal PAYG state management    // 初始化内部状态，就检测有没有ID
    product_payg_state_manager_init();  

    LOG_INF("---Nexus Embedded Demonstration Started---");  // 演示开始

    while (1)
    {
        // Will wait for user input from "demo_console" and loop forever.       // 等待来自用户输入的循环
        demo_console_wait_for_user_input();             // 这里等待的是来自user的输入
    }
}
