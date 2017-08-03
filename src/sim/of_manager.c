#include "of_manager.h"
#include "lib/util.h"
#include "lib/openflow.h"

struct of_manager *of_manager_new(struct scheduler *sch)
{
    struct of_manager *om = xmalloc(sizeof(struct of_manager));
    om->of = of_client_new(0);
    om->of->owner = om;
    om->of->message_callback = of_manager_message_cb;
    om->sch = sch;
    return om;
}

void of_manager_send(struct of_manager *om, uint64_t dpid, 
                     uint8_t *buf, size_t len)
{
    /* Retrieve the respective dpid connection to send */
    struct of_conn *conn;
    HASH_FIND(hh, om->of->active_conns, &dpid, sizeof(uint64_t), conn);
    if (conn != NULL) {
        of_conn_send(conn, buf, len);
    }
}

void of_manager_message_cb(struct of_conn* conn, uint8_t type, 
                             void *data, size_t len)
{
    /* Operate directly in the target dp node */
    struct of_client *of = (struct of_client*) conn->conn->owner;
    struct of_manager *om = (struct of_manager*) of->owner;  
    uint64_t time = om->sch->clock;
    uint64_t dp_id = conn->id;

    struct sim_event_of *msg = sim_event_of_msg_in_new(time, dp_id, 
                                                       data, len);

    printf("INSERINDO Mensagem Type %d time %ld\n", type, time);
    scheduler_insert(om->sch, (struct sim_event*) msg);
    printf("ADICIONEI Mensagem \n");
    /* We do not need the type but it is here 
     * because libfluid callback needs it */
    UNUSED(type);
}