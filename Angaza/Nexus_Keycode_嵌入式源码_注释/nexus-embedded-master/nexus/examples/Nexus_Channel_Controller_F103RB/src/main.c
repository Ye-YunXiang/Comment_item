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
// ���ߴ�����Ϣ������
#include "product_data_link.h"

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <string.h>
#include <zephyr.h>

// Flash filesystem, specific to this implementation ʵ��flash�ļ�����ϵͳ
#include "flash_filesystem.h"
#include "payg_led_display.h"
#include "product_nexus_identity.h"
#include "product_payg_state_manager.h"

// Interactive UART 'command console', for demonstration purposes
// ����ʽuart����̨��������ʾĿ��
#include "demo_console.h"

// Zephyr logging for easier demonstration purposes
// Ϊ�˸�������ʾZephyr��¼
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

static void _assign_nexus_payg_identities(void)
{
    // Store testing values to flash for:   �洢����ֵ��flash��
    // Nexus ID / PAYG ID       ֧��ID
    // Keycode Secret Key   ��Կ
    // Channel Secret Key   ͨ����Կ
    // NOTE: In production, these should vary from device to device!    �����������豸����
    const struct nx_id TEST_NEXUS_ID = {
        0xFFFF, // authority ID 0xFFFF for 'testing'       Ȩ��ID�����ڲ���
        12345678, // arbitrary device ID 12345678 (0x00bc614e)  �κ��豸ID
    };
    // A fake key just used for demo purposes...    ������ʾĿ�ĵļ���Կ
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
    // �ȴ�15��UART���г�ʼ��
    k_busy_wait(1 * 1000 * 1000); // us

    // Initialize flash filesystem/NV
    // ��ʼ��Flash�ļ�ϵͳ
    if (!flash_filesystem_init())
    {
        // should never reach here  ��Ӧ�õ�������
        assert(false);
        return;
    }
    // In a real device, this would not happen in every boot in main.c, but
    // ��ʵ���豸�У��ⲻ����main.c��ÿ�������з���
    // would happen once in the factory during provisioning
    // ���ڹ��������ڼ�ᷢ��һ��
    _assign_nexus_payg_identities();

    // Initialize PAYG LED display hardware
    // ��ʼ��PAYG LED��ʾӲ��
    payg_led_display_init();

    // Initialize internal PAYG state management
    // ��ʼ���ڲ�PAYG״̬����
    product_payg_state_manager_init();

    // Prepare data link, and use
    // ׼���������ӣ���ʹ��
    // `nx_channel_network_receive` to process received
    // ������յ��Ľ���
    // messages.    ��Ϣ
    product_data_link_init(&nx_channel_network_receive);

    LOG_INF("---Nexus Embedded Demonstration Started (CONTROLLER)---");

    while (1)
    {
        // Will wait for user input from "demo_console" and loop forever.
        // �ȴ����ԡ�demo_console�����û����벢��Զѭ����
        demo_console_wait_for_user_input();
    }
}
