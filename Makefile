CC = gcc

INCLUDES_DIR = includes
SYSTEM_DIR = system

CFLAGS = -I$(INCLUDES_DIR)

SOURCES = $(wildcard $(SYSTEM_DIR)/*.c)

TARGET = wireminnow

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
