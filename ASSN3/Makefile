CXX = g++
CC = $(CXX)
CFLAGS = -g -Wall
BUILD_DIR = build
TARGET = assn3
SRCS = $(wildcard src/*.cpp src/*/*.cpp)
OBJS = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

clean: 
	rm -rf $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -I include/

-include $(DEPS)

$(BUILD_DIR)/%.o: src/%.cpp | create_build_dirs
	$(CC) $(CFLAGS) -MMD -c -o $@ $< -I include/

create_build_dirs:
	@mkdir -p $(dir $(OBJS))