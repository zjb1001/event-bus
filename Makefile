CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -pedantic -std=c11
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SRCDIR = src
TESTDIR = test
OBJDIR = obj
TESTBINDIR = test_bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLES = publisher subscriber
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))
TEST_EXECUTABLES = $(patsubst $(TESTDIR)/%.cpp,$(TESTBINDIR)/%,$(TEST_SOURCES))

GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: $(EXECUTABLES) $(TEST_EXECUTABLES)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

publisher: $(OBJDIR)/publisher.o $(OBJDIR)/event_bus.o
	$(CC) $(CFLAGS) $^ -o $@

subscriber: $(OBJDIR)/subscriber.o $(OBJDIR)/event_bus.o
	$(CC) $(CFLAGS) $^ -o $@

$(TESTBINDIR)/%: $(OBJDIR)/%.o $(OBJDIR)/event_bus.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLES) $(TESTBINDIR)

run_publisher:
	./publisher

run_subscriber:
	./subscriber

run: run_publisher run_subscriber

test: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES) ; do \
		echo "Running $$test" ; \
		$$test ; \
	done

.PHONY: all clean run_publisher run_subscriber run test