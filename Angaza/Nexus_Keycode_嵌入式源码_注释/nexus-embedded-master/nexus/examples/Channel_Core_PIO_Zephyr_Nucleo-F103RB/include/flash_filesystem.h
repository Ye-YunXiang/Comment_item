/** \file flash_filesystem.h
 * \brief A demo implementation of flash filesystem for Nexus and Product Code
 * \author Angaza
 * \copyright 2021 Angaza, Inc.
 * \license This file is released under the MIT license
 *
 * The above copyright notice and license shall be included in all copies
 * or substantial portions of the Software.
 *
 * This module uses the Zephyr "NVS" flash filesystem module to set up
 * two separate 'flash filesystems', one for Nexus persistent storage,
 * one for Product persistent storage.
 *
 * This isolation helps prevent changes to product or Nexus NV storage
 * (sizes, frequency of writes, etc) from negatively impacting system
 * behavior elsewhere.
 *
 * If not using Zephyr NVS to provide persistent storage, modify this file
 * to use a different method of reading and writing to NV for product and
 * Nexus code.
 */

#ifndef FLASH_FILESYSTEM__H
#define FLASH_FILESYSTEM__H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>

// for size_t
#include <stddef.h>

/** Developer-defined custom flash/NV 'ID' tags.
 *
 * These are not used by Nexus Library, and can be any
 * value between 0 and 65535. These are used to uniquely tag
 * data written to flash that is used by the product code.
 * ��Щ����Nexus��ʹ�ã����ҿ�����0��65535֮����κ�ֵ����������Ψһ�ر��д����������ݣ���Щ�����ɲ�Ʒ����ʹ�á�
 */
enum flash_filesystem_product_nv_id
{
    // Recommended flash IDs for Nexus Identity information
    // �Ƽ�����Nexus Identity��Ϣ��flash id
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_ID = 1,
    // Nexus Keycode Secret key (see product_nexus_identity.h)
    // ������Կ(��product_nexus_identity.h)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_KEYCODE_SECRET_KEY = 2,
    // Nexus Channel Secret key (see product_nexus_identity.h)
    // Nexusͨ����Կ(�μ�product_nexus_identity.h)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_CHANNEL_SECRET_KEY = 3,
    // Amount of PAYG credit remaining (uint32_t)
    // �����ָ����(uint32 t)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_PAYG_MANAGER_CREDIT_REMAINING = 4,
    // Threshold for 'low battery' state for battery resource (see
    // battery_res.h/.c)
    // �����Դ���͵�����״̬��ֵ
    FLASH_FILESYSTEM_PRODUCT_NV_ID_BATTERY_THRESHOLD = 100,
    // Developers can add other custom IDs as desired
    // ������Ա���Ը�����Ҫ��������Զ���id
    FLASH_FILESYSTEM_PRODUCT_NV_ID_OTHER_CUSTOM_IDS_HERE = 500,
};
/**
 * @brief flash_filesystem_init
 *
 * Initialize filesystems for Nexus Library and Product persistent
 * storage. Should be called *once* upon system boot, and must be
 * successfully executed before any flash read/writes are performed.
 * ��ʼ��Nexus��Ͳ�Ʒ�־��Ե��ļ�ϵͳ
 * �洢��Ӧ����ϵͳ����ʱ������һ�Σ����ұ�����
 * ��ִ���κ�flash��/д֮ǰ�ɹ�ִ�С�
 * 
 * @return true on success. False if either filesystem fails to initialize.
 * �����ĳɹ�������κ�һ���ļ�ϵͳ��ʼ��ʧ�ܣ���ΪFalse��
 */
bool flash_filesystem_init(void);

/**
 * @brief flash_filesystem_write_product_nv
 *
 * Write an entry to the *product* NV file system.
 * ��*product* NV�ļ�ϵͳд��һ����Ŀ��
 *
 * @param[in] id Id of the entry to be written         ��Ŀ
 * @param[in] data Pointer to the data to be written   ����ָ��
 * @param[in] len Number of bytes to be written        �ֽ���
 *
 * @return Number of bytes written. On success, it will be equal to the number
 * of bytes requested to be written. On failure returns 0.
 * д���ֽ������۳ɹ����͵�����
 * ����д����ֽ�����ʧ��ʱ����0��
 */
int flash_filesystem_write_product_nv(enum flash_filesystem_product_nv_id id,
                                      const void* data,
                                      size_t len);

/**
 * @brief flash_filesystem_write_nexus_nv Flash�ļ�ϵͳд��nexus nv
 *
 * Write an entry to the *Nexus* Library NV file system.
 * дһ����Ŀ��*Nexus* Library NV�ļ�ϵͳ��
 *
 * @param[in] id Id of the entry to be written
 * @param[in] data Pointer to the data to be written
 * @param[in] len Number of bytes to be written
 *
 * @return Number of bytes written. On success, it will be equal to the number
 * of bytes requested to be written. On failure returns 0.
 */
int flash_filesystem_write_nexus_nv(enum flash_filesystem_product_nv_id id,
                                    const void* data,
                                    size_t len);

/**
 * @brief flash_filesystem_read_product_nv  Flash�ļ�ϵͳ��ȡ��Ʒnv
 *
 * Read an entry from the *Product* NV file system.
 * ��*Product* NV�ļ�ϵͳ�ж�ȡһ����Ŀ��
 *
 * @param[in] id Id of the entry to be read
 * @param[out] data Pointer to data buffer
 * @param[in] len Number of bytes to be read
 *
 * @return Number of bytes read. On success, it will be equal to the number
 * of bytes requested to be read. On failure returns 0.
 */
int flash_filesystem_read_product_nv(enum flash_filesystem_product_nv_id id,
                                     void* data,
                                     size_t len);

/**
 * @brief flash_filesystem_read_nexus_nv   Flash�ļ�ϵͳ��ȡnexus nv
 *
 * Read an entry from the *Nexus* Library NV file system.
 * ��*Nexus* Library NV�ļ�ϵͳ��ȡһ����Ŀ��
 *
 * @param[in] id Id of the entry to be read
 * @param[out] data Pointer to data buffer
 * @param[in] len Number of bytes to be read
 *
 * @return Number of bytes read. On success, it will be equal to the number
 * of bytes requested to be read. On failure returns 0.
 */
int flash_filesystem_read_nexus_nv(enum flash_filesystem_product_nv_id id,
                                   void* data,
                                   size_t len);

#ifdef __cplusplus
}
#endif
#endif // FLASH_FILESYSTEM__H
