#include <event2/event.h>

struct ev_loop {
    int id;
    int stopped;
    struct event_base *base;
};

struct ev_loop *ev_loop_new(int id);
void ev_loop_destroy(struct ev_loop *ev);
void ev_loop_run(struct ev_loop *ev);
void ev_loop_stop(struct ev_loop *ev);
void *thread_adapter(void* arg);