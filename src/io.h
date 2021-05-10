#ifndef IO_H
#define IO_H


typedef enum {
    KeyUp,
    KeyRelease,
} io_event_et;

typedef struct {
    char key;
    io_event_et event;
} key_event_st;


#endif /* IO_H */
