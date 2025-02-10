CC=gcc

TARGET?=s21_string.a
TEST_TARGET?=test_s21_string.a
TEST_EXE?=test
TEST_GCOV_EXE?=test_gcov
OUTFILE=output.html
SRC_DIR?=.
TEST_SRC_DIR?=./tests

OBJ_DIR?=./objs
TEST_OBJ_DIR?=./tests/objs

INC_DIR:=./
TEST_INC_DIR:=./tests_includes

INC:=$(shell find $(INC_DIR) -name "*.h")
SRC:=$(shell find $(SRC_DIR) -name "s21_*.c")

TEST_INC:=$(shell find $(TEST_INC_DIR) -name "*.h")
TEST_SRC:=$(shell find $(TEST_SRC_DIR) -name "*.c")

OBJS:=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
GCOV_OBJS:=$(addprefix $(TEST_OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
TEST_OBJS:=$(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o))) # $(TEST_OBJ_DIR)/main.o

GCDA=$(shell find $(TEST_OBJ_DIR) -name "*.gcda")
GCNO=$(shell find $(TEST_OBJ_DIR) -name "*.gcno")

AR:= ar rc
RAN:= ranlib
RM:= rm -f
MK:=mkdir -p

ASAN:=
STDFLAGS=-c -Wall -Wextra -Werror -std=c11
# ifeq ($(shell uname), Linux)
# 	STDFLAGS += -lm -pthread
# endif
CFLAGS?= $(STDFLAGS) $(ASAN)
TST_CFLAGS:= -g $(STDFLAGS)
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage

CHECK_CFLAGS := -I/opt/homebrew/include -I$(INC_DIR)
CHECK_LIBS := -L/opt/homebrew/lib -lcheck

all: test s21_string.a gcov_report

gcov_obj: $(GCOV_OBJ)

$(TARGET): $(OBJS)
	$(AR) $(TARGET) $(OBJS)
	$(RAN) $(TARGET)

$(TEST_TARGET): $(GCOV_OBJS) $(INC)
	$(AR) $(TEST_TARGET) $(GCOV_OBJS)
	$(RAN) $(TEST_TARGET)

test: $(TARGET) $(TEST_OBJ_DIR)/main.o $(TEST_OBJS) $(TEST_INC)
	$(CC) $(TEST_OBJS) $(TEST_OBJ_DIR)/main.o $(ASAN) $(GCOV_FLAGS) -o $(TEST_EXE) $(CHECK_LIBS) -L. $(TARGET)
	./$(TEST_EXE) > test_output.txt

test_gcov: $(TEST_TARGET) $(TEST_OBJ_DIR)/main.o $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(TEST_OBJ_DIR)/main.o $(GCOV_FLAGS) -o $(TEST_GCOV_EXE) $(CHECK_LIBS) -L. $(TEST_TARGET)

$(TEST_OBJ_DIR)/main.o: main.c
	@$(MK) $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) -o $(TEST_OBJ_DIR)/main.o main.c

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(TEST_INC)
	@$(MK) $(TEST_OBJ_DIR)
	$(CC) $(TST_CFLAGS) $(CHECK_CFLAGS) -o $@ -c $<

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@$(MK) $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(GCOV_OBJS): $(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(TEST_INC)
	@$(MK) $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $@ -c $<

gcov_report: $(GCOV_TARGET)

$(GCOV_TARGET): CFLAGS += $(GCOV_FLAGS)
$(GCOV_TARGET): $(GCOV_INFO)
	genhtml $(GCOV_INFO) -o $(GCOV_TARGET)

html:
	@echo "<html lang=\"ru\"><head><meta charset=\"utf-8\"><title>Вывод результата</title></head><body><pre>" > $(OUTFILE)
	@cat test_output.txt >> $(OUTFILE)
	@echo "</pre></body></html>" >> $(OUTFILE)

open:
ifeq ($(shell uname), Linux)
	@xdg-open $(OUTFILE)
else ifeq ($(shell uname), Darwin)
	@open $(OUTFILE)
else
	@echo "Please open $(OUTFILE) manually."
endif

clean:
	$(RM) $(OBJS)
	$(RM) $(GCDA)
	$(RM) $(GCNO)
	$(RM) $(TEST_OBJS)
	$(RM) $(GCOV_OBJS)
	$(RM) tests/objs/main.o
	$(RM) $(OUTFILE)
	$(RM) test_output.txt

fclean: clean
	$(RM) $(TARGET)
	$(RM) $(TEST_TARGET)
	$(RM) $(TEST_EXE)
	$(RM) $(TEST_GCOV_EXE)
	$(RM) $(GCOV_INFO)
	$(RM) -r $(GCOV_TARGET)
	$(RM) tests/objs/main.o
	$(RM) -R objs
	$(RM) -R tests/objs

rebuild: fclean all

verter:
	cp -R ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n -style=google *.c tests/*.c
	clang-format -n -style=google *.h tests_includes/*.h
	clang-format -i -style=google *.c tests/*.c
	clang-format -i -style=google *.h tests_includes/*.h
	clang-format -n -style=google *.c tests/*.c
	clang-format -n -style=google *.h tests_includes/*.h
	rm .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.h
	cppcheck --enable=all --suppress=missingIncludeSystem ./tests/*.c
	cppcheck --enable=all --suppress=missingIncludeSystem ./tests_includes/*.h

.PHONY: all clean fclean re open html

