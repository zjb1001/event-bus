#include "event_bus.h"

int main() {
    int msqid = create_event_bus();
    if (msqid == -1) {
        return 1;
    }

    while (1) {
        publish_event(msqid, "say_hi", "Hello, World!");
        sleep(5);  // Publish every 5 seconds
    }

    return 0;
}
