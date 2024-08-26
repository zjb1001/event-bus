#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_MSG_SIZE 256
#define PROJECT_ID 123

typedef struct {
    long mtype;
    char mtext[MAX_MSG_SIZE];
} message_t;

int create_event_bus();
int publish_event(int msqid, const char* event_name, const char* event_data);
int subscribe_event(int msqid, long event_type);

long hash(const char* str);

#endif // EVENT_BUS_H
