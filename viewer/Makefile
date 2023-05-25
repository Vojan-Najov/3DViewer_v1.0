TARGET = lib3Dviewer.a

CC = gcc
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
AR = ar rcs

CONFIG_PATH = $(HOME)/.3DViewer_config

CFLAGS = -Wall -Wextra -Werror -DVW_CONF_FILE=\"$(CONFIG_PATH)\"
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0

INCLUDE_DIR = ./include
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)

SRC_DIR = ./src
OBJ_DIR = ./obj
GCOV_OBJ_DIR = ./gcov_obj
SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
GCOV_OBJ = $(SRC:$(SRC_DIR)/%.c=$(GCOV_OBJ_DIR)/%.o)

OBJ_DIRS = $(sort $(dir $(OBJ)))
GCOV_OBJ_DIRS = $(sort $(dir $(GCOV_OBJ)))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

gcov_report: $(GCOV_OBJ)

$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(GCOV_OBJ_DIRS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<


$(OBJ_DIRS):
	$(MKDIR) $@

$(GCOV_OBJ_DIRS):
	$(MKDIR) $@

clean:
	$(RM) $(OBJ)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(GCOV_OBJ)
	$(RMDIR) $(GCOV_OBJ_DIR)
	$(RM) $(TARGET)


re: clean all

format:
	cp ../misc/.clang-format .
	clang-format -i $(SRC) $(TEST_SRC) $(INCLUDE) $(TEST_INCLUDE)
	$(RM) .clang-format

.PHONY: all clean re format
