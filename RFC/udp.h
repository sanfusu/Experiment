/**
 * @ref     :   https://www.rfc-editor.org/rfc/rfc768.txt
 * @author  :   sanfusu@foxmail.com
 * @date    :   2019-02-26 09:58:20
 * @update  :   2019-02-26 09:58:32
 * 
 * UDP(user datagram protocol 协议的底层协议为 IP 协议)
 *  0      7 8     15 16    23 24    31  
 * +--------+--------+--------+--------+ 
 * |     Source      |   Destination   | 
 * |      Port       |      Port       | 
 * +--------+--------+--------+--------+ 
 * |                 |                 | 
 * |     Length      |    Checksum     | 
 * +--------+--------+--------+--------+ 
 * |                                     
 * |          data octets ...            
 * +---------------- ...    
 * 
 * UDP 接口必须能够从 IP 头部获取到源地址，目的地址和协议字段。             
 */
#ifndef __UDP_H
#define __UDP_H

#include <stdint.h>

/** udp_hdr_t
 * src_port: 
 *      发送进程的端口，若缺失其他信息，可以假定认为回复的端口也是 src_port
 *      可选字段，不用的时候，用 0 来填充。
 * dst_port:
 *      在特定的网络目的地址的上下文环境中有效。
 * len:
 *      UDP 包括头部和数据的总长度（以 8 bit 字节为单位）
 *      最小值为 8
 * checksum:
 *      IP pseudo header + UDP header + data + 补足的 0 字节 的 16 bit 和的 1 的补码（取反）
 */
typedef struct udp_hdr
{
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t len;
    uint16_t checksum;
} udp_hdr_t;

/** ip_pseudo_hdr_t
 * 伪 ip 头部，实际上可能不是如此
 */
typedef struct ip_pseudo_hdr
{
    uint32_t src_addr;
    uint32_t dst_addr;
    uint8_t zero;
    uint8_t protocol;
    uint16_t len;
} ip_pseudo_hdr_t;
#endif