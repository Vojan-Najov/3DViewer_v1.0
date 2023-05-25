TARGET = test

CC = gcc
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

CFLAGS = -g -Wall -Wextra -Werror

OS := $(shell uname -s)
ITUBUNTU := $(shell uname -a | grep -i Ubuntu)

INCLUDE_DIR = ../viewer/include
TEST_INCLUDE_DIR = ./include

TEST_SRC_DIR = ./src

TEST_OBJ_DIR = ./obj

TEST_SRC = $(wildcard $(TEST_SRC_DIR)/test_*.c)
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))
GCOV_SRC = $(shell find ../viewer/src -type f -name '*.c')
GCOV_OBJ = $(GCOV_SRC:../viewer/src/%.c=../viewer/gcov_obj/%.o)

INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_INCLUDE = $(wildcard $(TEST_INCLUDE_DIR)/*h)

TEST_LIBS := -lcheck -lm

ifeq ($(OS),Linux)
  ifneq ($(ITUBUNTU), )
	TEST_LIBS := -lcheck -lsubunit -lm -lrt -lpthread
  endif
endif

all: $(TARGET)

.PHONY: test

$(TARGET): $(TEST_OBJ)
	make -sC ../viewer/ all
	$(CC) -g -o $@ $? ../viewer/lib3Dviewer.a $(TEST_LIBS)
	./test


$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(TEST_INCLUDE) $(INCLUDE)
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) -o $@ -c $<

gcov_report: $(TEST_OBJ)
	make -sC ../viewer/ gcov_report
	$(CC) -fprofile-arcs -ftest-coverage -o $(TARGET) $? $(GCOV_OBJ) $(TEST_LIBS)
	./test

clean:
	$(RM) $(TEST_OBJ)
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) $(TARGET)

re: fclean all

format:
	cp ../misc/.clang-format .
	clang-format -i $(TEST_SRC) $(TEST_INCLUDE)
	$(RM) .clang-format

.PHONY: all clean re format
