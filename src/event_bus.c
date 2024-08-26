#include "event_bus.h"

int create_event_bus() {
    key_t key = ftok(".", PROJECT_ID);
    if (key == -1) {
        perror("ftok");
        return -1;
    }
    
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        return -1;
    }
    
    return msqid;
}

int publish_event(int msqid, const char* event_name, const char* event_data) {
    message_t msg;
    msg.mtype = hash(event_name);
    snprintf(msg.mtext, MAX_MSG_SIZE, "%s:%s", event_name, event_data);
    
    if (msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return -1;
    }
    
    return 0;
}

int subscribe_event(int msqid, long event_type) {
    message_t msg;
    
    if (msgrcv(msqid, &msg, MAX_MSG_SIZE, event_type, 0) == -1) {
        perror("msgrcv");
        return -1;
    }
    
    printf("Received: %s\n", msg.mtext);
    return 0;
}

// Simple hash function for event names
long hash(const char* str) {
    long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
