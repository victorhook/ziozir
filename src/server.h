#ifndef SERVER_H
#define SERVER_H

#define PORT 8008
#include <stdlib.h>
#include "io.h"

typedef enum {
    ACTION_READ,
    ACTION_WRITE,
    ACTION_MEM_INFO,
    ACTION_EXECUTE,
    ACTION_RESET,
    ACTION_PING,
    ACTION_PONG,
    ACTION_EVENT,
    ACTION_UPDATE_SCREEN,
} action_et;

typedef struct {
    action_et action;
    size_t len;
    key_event_st* events;
} packet_recv_st;

typedef struct {
    action_et action;
} packet_send_st;



#endif /* SERVER_H */
