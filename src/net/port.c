/* Copyright (c) 2016-2017, Eder Leao Fernandes
 * All rights reserved.
 *
 * The contents of this file are subject to the license defined in
 * file 'doc/LICENSE'.
 *
 *
 * Author: Eder Leao Fernandes <e.leao@qmul.ac.uk>
 */

#include "lib/util.h"
#include "port.h"
#include <string.h>

struct port* port_new(uint32_t port_id, uint8_t eth_addr[ETH_LEN], uint32_t speed, uint32_t curr_speed) {
    struct port* p = xmalloc(sizeof(struct port));
    memset(p, 0x0, sizeof(struct port));
    p->port_id = port_id;
    memcpy(p->eth_address, eth_addr, ETH_LEN);
    p->ipv4_addr = NULL;
    p->ipv6_addr = NULL; 
    p->config |= PORT_UP;
    p->state |= PORT_LIVE;
    /* TODO: Set port speed */
    p->speed = speed;
    p->curr_speed = curr_speed;
    return p;
}

void port_add_v4addr(struct port *p, uint8_t ipv4_addr)
{
    p->ipv4_addr = xmalloc(sizeof(uint32_t));
    *(p->ipv4_addr) = ipv4_addr;
}

void port_add_v6addr(struct port *p, uint8_t ipv6_addr[IPV6_LEN])
{
    p->ipv6_addr = xmalloc(IPV6_LEN);
    memcpy(p->ipv6_addr, ipv6_addr, IPV6_LEN);
}