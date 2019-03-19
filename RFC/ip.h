/**
 * ---------------------------------------------------------
 * @ref     :   https://www.rfc-editor.org/rfc/rfc791.txt
 * @author  :   sanfusu@foxmail.com
 * @date    :   2019-02-26 10:42:06
 * @update  :   2019-02-26 10:42:10
 * ---------------------------------------------------------
 * 
 * ---------------------------------------------------------
 * ip 协议可以被网络环境中的主机到主机协议调用。
 * ip 协议用于将网络数据包运输到下一个网关或目的主机。
 * 
 * ip 协议主要实现两个基本功能：寻址和分段
 * 
 * Type of Service(TOS):
 *      用来指示所需服务的品质，由网关作为参数来选择合适的网络进行传输
 * Time to Live(TTL):
 *      ip 协议传输单元的生命周期。
 *      由发送方设置，在路由点减一。
 *      如果在送达目的地之前，TTL 减为 0，则销毁该传输单元。
 * Options:
 *      选项在部分环境下有用。但必须实现。
 *      选项包括：时间戳，安全，特殊路由
 * Header Checksum:
 *      如果校验错误，则抛弃该传输单元，可以通过 ICMP 来报告错误。
 * ---------------------------------------------------------
 * 
 * 
 * ---------------------------------------------------------
 * 
 *                                     
 * +------+ +-----+ +-----+     +-----+
 * |Telnet| | FTP | | TFTP| ... | ... |
 * +------+ +-----+ +-----+     +-----+
 *       |   |         |           |   
 *      +-----+     +-----+     +-----+
 *      | TCP |     | UDP | ... | ... |
 *      +-----+     +-----+     +-----+
 *         |           |           |
 *      +--------------------------+----+
 *      |    Internet Protocol & ICMP   |
 *      +--------------------------+----+
 *                     |
 *        +---------------------------+
 *        |   Local Network Protocol  |
 *        +---------------------------+
 * 
 *        Protocol Relationships
 * ---------------------------------------------------------
 * 
 * 
 *  ---------------------------------------------------------
 * Application                                           Application
 * Program                                                   Program
 *       \                                                   /      
 *     Internet Module      Internet Module      Internet Module    
 *           \                 /       \                /           
 *           LNI-1          LNI-1      LNI-2         LNI-2          
 *              \           /             \          /              
 *             Local Network 1           Local Network 2            
 * 
 *                    Transmission Path
 */

#ifndef __IP_H
#define __IP_H
#include <stdint.h>

#define ip32_addr_is_classA(addr32) !((addr32) & (1u << 31))
#define ip32_addr_is_classB(addr32) !!(((addr32) >> 30) == 0x2u)

/**
 *  0               1               2               3   
 *  0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Version|  IHL  |Type of Service|          Total Length         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |         Identification        |Flags|      Fragment Offset    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Time to Live |    Protocol   |         Header Checksum       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                       Source Address                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Destination Address                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Options                    |    Padding    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 
 * 头部需要 32-bit 对齐
 */
typedef struct ip_hdr
{
    uint32_t ver : 4;              // ip 头部的版本
    uint32_t IHL : 4;              // internet header length, 头部长度，单位：32-bit 字
    uint32_t tos : 8;              // type of service
    uint32_t tol : 16;             // Total Length, 单位 8-bit 字节，最多 65535 字节，但要求所有必须可接受 576 字节
    uint32_t id : 16;              // 由发送者设置，用于重组数据包分段
    uint32_t flag : 3;             // 各种控制标签
    uint32_t ttl : 8;              //
    uint32_t protocol : 8;         // 下一级的协议
    uint32_t header_checksum : 16; // 头部 16-bit 字的 1 的补码和的补码（可能会被 CRC 取代）
    uint32_t src_addr;
    uint32_t dest_addr;
    uint32_t options[0];
} ip_hdr_t;

// 大端顺序
// #define IP_HDR_TOS_PRECEDENCE_OFFSET 0x0
// #define IP_HDR_TOS_PRECEDENCE_WIDTH 0x03
// #define IP_HDR_TOS_DELAY_OFFSET (TOS_PRECEDENCE_OFFSET + TOS_PRECEDENCE_WIDTH)
// #define IP_HDR_TOS_DELAY_WIDTH 0x01
// #define IP_HDR_TOS_THROUGHPUT_OFFSET (TOS_DELAY_OFFSET + TOS_DELAY_WIDTH)
// #define IP_HDR_TOS_THROUGHPUT_WIDTH 0x01
// #define IP_HDR_TOS_RELIBILITY_OFFSET (TOS_THROUGHPUT_OFFSET + TOS_THROUGHPUT_WIDTH)
// #define IP_HDR_TOS_RELIBITITY_WIDTH 0x01

#define IP_HDR_TOS_PRECEDENCE_NETWORK_CTRL 0x7
#define IP_HDR_TOS_PRECEDENCE_INTERNETWORK_CTRL 0x6
#define IP_HDR_TOS_PRECEDENCE_CRITIC_ECP 0x5
#define IP_HDR_TOS_PRECEDENCE_FLASH_OVERRIDE 0x4
#define IP_HDR_TOS_PRECEDENCE_FLASH 0x3
#define IP_HDR_TOS_PRECEDENCE_IMMEDIATE 0x2
#define IP_HDR_TOS_PRECEDENCE_PRIORITY 0x1
#define IP_HDR_TOS_PECEDENCE_ROUTINE 0x0

#define IP_HDR_

#endif
