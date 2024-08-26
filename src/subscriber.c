#include "event_bus.h"

int main() {
    int msqid = create_event_bus();
    if (msqid == -1) {
        return 1;
    }

    long event_type = hash("say_hi");
    
    while (1) {
        if (subscribe_event(msqid, event_type) == -1) {
            break;
        }
    }

    return 0;
}