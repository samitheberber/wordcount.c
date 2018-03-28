CC = gcc -ansi -pedantic -Wall -Wextra -g
SRC_DIR = src
BUILD_DIR = build
PROGRAM_NAME = wordcount

$(PROGRAM_NAME): $(BUILD_DIR)/main.o $(BUILD_DIR)/file.o $(BUILD_DIR)/structure.o
	$(CC) -o $(PROGRAM_NAME) $(BUILD_DIR)/main.o $(BUILD_DIR)/file.o $(BUILD_DIR)/structure.o
$(BUILD_DIR)/file.o: $(SRC_DIR)/file.c $(SRC_DIR)/file.h
	$(CC) -c $(SRC_DIR)/file.c -o $@
$(BUILD_DIR)/structure.o: $(SRC_DIR)/structure.c $(SRC_DIR)/structure.h
	$(CC) -c $(SRC_DIR)/structure.c -o $@
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/file.h $(SRC_DIR)/structure.h
	$(CC) -c $(SRC_DIR)/main.c -o $@

clean:
	rm -rf $(PROGRAM_NAME) $(BUILD_DIR)/*.o
