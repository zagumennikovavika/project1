# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Исходные и объектные файлы
SRC = test.c
OBJ = $(SRC:.c=.o)
TARGET = program

# Правило по умолчанию
all: $(TARGET)

# Как собрать исполняемый файл
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Как собрать объектные файлы (если будет несколько)
%.o: %.c student1.h student2.h
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка для Windows
clean:
	del /Q $(OBJ) $(TARGET).exe
