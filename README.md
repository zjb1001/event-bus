# Event Bus System

This is a simple event bus system that allows inter-process communication using message queues. It provides a publisher-subscriber model for processes to communicate with each other.

## Prerequisites

- GCC compiler
- Make utility
- POSIX-compliant operating system (Linux, macOS, etc.)

## Compilation

To compile the project, navigate to the project root directory and run:

```
make
```

This will compile both the publisher and subscriber executables.

## Usage

### Running the Publisher

To run the publisher:

```
make run_publisher
```

or

```
./publisher
```

The publisher will start sending "say_hi" events every 5 seconds.

### Running the Subscriber

To run the subscriber:

```
make run_subscriber
```

or

```
./subscriber
```

The subscriber will listen for "say_hi" events and print them when received.

### Running Both Publisher and Subscriber

To run both the publisher and subscriber simultaneously:

```
make run
```

Note: You may need to use Ctrl+C to stop the processes as they run continuously.

## Customization

### Adding New Event Types

1. Modify `src/event_bus.h` to add new event type definitions if needed.
2. Update `src/publisher.c` to publish new event types.
3. Update `src/subscriber.c` to subscribe to and handle new event types.

### Modifying Event Data

The current implementation uses a simple string for event data. To use more complex data:

1. Modify the `message_t` struct in `src/event_bus.h`.
2. Update the `publish_event` and `subscribe_event` functions in `src/event_bus.c` accordingly.

## Cleaning Up

To remove all compiled files:

```
make clean
```

## Limitations

- This system uses System V IPC message queues, which may have limitations on message size and queue capacity depending on your system configuration.
- The current implementation does not handle multiple subscribers for the same event type.
- Error handling is minimal and should be expanded for production use.

## Contributing

Feel free to fork this project and submit pull requests for any improvements or bug fixes.
