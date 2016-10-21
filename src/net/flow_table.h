#ifndef FLOW_TABLE_H
#define FLOW_TABLE_H 1

#include "lib/flow.h"
#include <inttypes.h>

/* Total number of tables per datapath */
#define MAX_TABLES 128

/* Mini flow tables are hash maps that 
*  contain only one combination of match 
*  fields. 
*
*  In the struct, flows is the hash 
*  table of flows and mask indicates 
*  the active fields of the table. 
**/
struct mini_flow_table {
    struct flow* flows;
    struct flow_key mask;
    struct mini_flow_table *prev; /* needed for a doubly-linked list only */
    struct mini_flow_table *next; /* needed for singly- or doubly-linked lists */
};

typedef struct flow* flow_hash_list;

struct flow_table {
    struct mini_flow_table *flows; /*List of flows hash maps*/
};

struct flow_table* flow_table_new(void);
void add_flow(struct flow_table* ft, struct flow* f);

#endif /* FLOW_TABLE_H */ 