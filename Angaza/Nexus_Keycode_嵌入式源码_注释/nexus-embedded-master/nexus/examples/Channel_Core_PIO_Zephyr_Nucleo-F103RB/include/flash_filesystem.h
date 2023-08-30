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
 * 这些不被Nexus库使用，并且可以是0到65535之间的任何值。它们用于唯一地标记写入闪存的数据，这些数据由产品代码使用。
 */
enum flash_filesystem_product_nv_id
{
    // Recommended flash IDs for Nexus Identity information
    // 推荐用于Nexus Identity信息的flash id
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_ID = 1,
    // Nexus Keycode Secret key (see product_nexus_identity.h)
    // 秘密密钥(见product_nexus_identity.h)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_KEYCODE_SECRET_KEY = 2,
    // Nexus Channel Secret key (see product_nexus_identity.h)
    // Nexus通道密钥(参见product_nexus_identity.h)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_NEXUS_CHANNEL_SECRET_KEY = 3,
    // Amount of PAYG credit remaining (uint32_t)
    // 现收现付余额(uint32 t)
    FLASH_FILESYSTEM_PRODUCT_NV_ID_PAYG_MANAGER_CREDIT_REMAINING = 4,
    // Threshold for 'low battery' state for battery resource (see
    // battery_res.h/.c)
    // 电池资源“低电量”状态阈值
    FLASH_FILESYSTEM_PRODUCT_NV_ID_BATTERY_THRESHOLD = 100,
    // Developers can add other custom IDs as desired
    // 开发人员可以根据需要添加其他自定义id
    FLASH_FILESYSTEM_PRODUCT_NV_ID_OTHER_CUSTOM_IDS_HERE = 500,
};
/**
 * @brief flash_filesystem_init
 *
 * Initialize filesystems for Nexus Library and Product persistent
 * storage. Should be called *once* upon system boot, and must be
 * successfully executed before any flash read/writes are performed.
 * 初始化Nexus库和产品持久性的文件系统
 * 存储。应该在系统启动时被调用一次，并且必须是
 * 在执行任何flash读/写之前成功执行。
 * 
 * @return true on success. False if either filesystem fails to initialize.
 * 真正的成功。如果任何一个文件系统初始化失败，则为False。
 */
bool flash_filesystem_init(void);

/**
 * @brief flash_filesystem_write_product_nv
 *
 * Write an entry to the *product* NV file system.
 * 向*product* NV文件系统写入一个条目。
 *
 * @param[in] id Id of the entry to be written         条目
 * @param[in] data Pointer to the data to be written   数据指针
 * @param[in] len Number of bytes to be written        字节数
 *
 * @return Number of bytes written. On success, it will be equal to the number
 * of bytes requested to be written. On failure returns 0.
 * 写入字节数。论成功，就等于数
 * 请求写入的字节数。失败时返回0。
 */
int flash_filesystem_write_product_nv(enum flash_filesystem_product_nv_id id,
                                      const void* data,
                                      size_t len);

/**
 * @brief flash_filesystem_write_nexus_nv Flash文件系统写入nexus nv
 *
 * Write an entry to the *Nexus* Library NV file system.
 * 写一个条目到*Nexus* Library NV文件系统。
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
 * @brief flash_filesystem_read_product_nv  Flash文件系统读取产品nv
 *
 * Read an entry from the *Product* NV file system.
 * 从*Product* NV文件系统中读取一个条目。
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
 * @brief flash_filesystem_read_nexus_nv   Flash文件系统读取nexus nv
 *
 * Read an entry from the *Nexus* Library NV file system.
 * 从*Nexus* Library NV文件系统读取一个条目。
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
