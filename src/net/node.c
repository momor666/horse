#include "node.h"
#include <stdio.h>

static uint64_t current_uuid = 0;

void 
node_init(struct node* n, uint16_t type)
{
    n->uuid = ++current_uuid;
    n->ports_num = 0;
    n->ports = NULL;
    n->type = type;
    n->flow_buff.top = -1;
}

void 
node_destroy_ports(struct node *n)
{
    /* Free ports */
    struct port *cur_port, *tmp;
    HASH_ITER(hh, n->ports, cur_port, tmp) {
        HASH_DEL(n->ports, cur_port);  
        free(cur_port->ipv4_addr);
        free(cur_port->ipv6_addr);
        free(cur_port);
    }
}

void 
node_add_port(struct node *n, uint32_t port_id, uint8_t eth_addr[ETH_LEN], uint32_t speed, uint32_t curr_speed)
{
    struct port *p = port_new(port_id, eth_addr, speed, curr_speed);
    HASH_ADD(hh, n->ports, port_id, sizeof(uint32_t), p);
    n->ports_num++;
}

/* Retrieve a datapath port */
struct port* 
node_port(const struct node *n, uint32_t port)
{
    struct port *p;
    HASH_FIND(hh, n->ports, &port, sizeof(uint32_t), p);
    return p;
}

bool 
node_is_buffer_empty(struct node *n)
{
    return n->flow_buff.top < 0? 1:0;
}

bool node_flow_queue(struct node*n, struct netflow flow){
    if (n->flow_buff.top > BUFFER_MAX){
        return 0;
    }
    n->flow_buff.top++;
    n->flow_buff.flows[n->flow_buff.top] = flow;
    return 1;
}

struct netflow node_flow_dequeue(struct node *n){
    struct netflow f = n->flow_buff.flows[n->flow_buff.top];
    n->flow_buff.top--;
    return f;
}