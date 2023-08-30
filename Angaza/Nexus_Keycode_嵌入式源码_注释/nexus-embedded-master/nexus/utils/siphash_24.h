/** \file siphash_24.h
 * \brief Siphash 2-4 algorithm used by Nexus internally.
 * \author Angaza
 * \copyright 2020 Angaza, Inc.
 * \license This file is released under the MIT license
 *
 * The above copyright notice and license shall be included in all copies
 * or substantial portions of the Software.
 *
 * By default, the implementation of this header is included within
 * `common/siphash_24.c`. The header is provided at this 'top level' so that
 * product-side code may also use the same Siphash functionality (if required),
 * and so that the Siphash functionality is usable by other Nexus modules
 * (such as Nexus Channel) without duplicating code.
 */

#ifndef __NEXUS__COMMON__INC__SIPHASH_24_H_
#define __NEXUS__COMMON__INC__SIPHASH_24_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Compute a Siphash 2-4 hash result over input bytes.
 *
 * Given a key and an input stream of bytes, compute the Siphash 2-4 64-bit
 * (8 byte) result.
 *
 * `out` must be able to contain at least 8 bytes.
 * `in` may be any length of bytes.
 *
 * \param out pointer to output where the Siphash 2-4 result will be placed.
 * \param in pointer to input bytes to compute hash over
 * \param inlen length of input bytes to compute from `in`
 * \param key 128-bit (16 byte) secret key used to compute hash result
 * 
 * 计算输入字节的Siphash 2-4哈希结果
 * 给定一个密钥和一个字节输入流，计算Siphash 2-4位（8字节）的结果.
 * 'out'必须至少包含8个字节。
 * 'in' 可以是任意长度的字节。
 * 
 * \out      只想Siphash 2-4结果将被放置的输出指针。
 * \in       指向要计算哈希值的输入字节的指针。
 * \linlen   要从' in '计算的输入字节长度。
 * \key      用于计算哈希结果的128位(16字节)秘密密钥。
 * 
 */
void siphash24_compute(uint8_t* out,
                       const uint8_t* in,
                       const uint32_t inlen,
                       const uint8_t* key);

#ifdef __cplusplus
}
#endif

#endif
