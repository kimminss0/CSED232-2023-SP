CXX = g++
CC = $(CXX)
CFLAG = -g -Wall
BUILD_DIR = build
TARGET = student_database
all: $(TARGET)
clean: 
	rm -rf $(BUILD_DIR) $(TARGET)

$(TARGET): build/main.o build/student_database.o build/avg_aggregator.o build/max_aggregator.o build/min_aggregator.o build/get_menu_input.o build/get_student_info.o build/is_upper.o
	$(CC) $(CFLAG) -o $@ $^ -I include/

build/main.o: src/main.cpp include/student.hpp include/aggregator/min_aggregator.hpp include/aggregator/max_aggregator.hpp include/aggregator/avg_aggregator.hpp include/util.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/student_database.o: src/student_database.cpp include/student_database.hpp include/aggregator.hpp include/util.hpp include/dept.hpp include/list.hpp include/student.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/avg_aggregator.o: src/aggregator/avg_aggregator.cpp include/aggregator/avg_aggregator.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/max_aggregator.o: src/aggregator/max_aggregator.cpp include/aggregator/max_aggregator.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/min_aggregator.o: src/aggregator/min_aggregator.cpp include/aggregator/min_aggregator.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/get_menu_input.o: src/util/get_menu_input.cpp include/util.hpp include/student.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/get_student_info.o: src/util/get_student_info.cpp include/util.hpp include/student.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

build/is_upper.o: src/util/is_upper.cpp include/util.hpp include/student.hpp | $(BUILD_DIR)
	$(CC) $(CFLAG) -c -o $@ $< -I include/

$(BUILD_DIR):
	mkdir -p $@