#include <gtest/gtest.h>
#include "../src/event_bus.h"

TEST(EventBusTest, CreateEventBus) {
    int msqid = create_event_bus();
    EXPECT_GE(msqid, 0);
}

TEST(EventBusTest, PublishAndSubscribe) {
    int msqid = create_event_bus();
    ASSERT_GE(msqid, 0);

    const char* event_name = "test_event";
    const char* event_data = "Hello, World!";

    int publish_result = publish_event(msqid, event_name, event_data);
    EXPECT_EQ(publish_result, 0);

    long event_type = hash(event_name);
    int subscribe_result = subscribe_event(msqid, event_type);
    EXPECT_EQ(subscribe_result, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}