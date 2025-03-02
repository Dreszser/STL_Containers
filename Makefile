CFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++17

GCOV_FLAGS = --coverage
LIB = s21_containers.a
CEXE = s21_test
CHECK_FILE = ./tests/*.check
INC = -I s21_containers/tree -I s21_containers/set -I s21_containers/multiset -I s21_containers/vector -I .

CFILES = s21_containers.cc
TEST_FILES = tests/*.cc
TEST_OBJ = *test.o

CC = g++

#============= FLAGS FOR OS =========================================================

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS = -lgtest -lsubunit -lm -lrt -pthread
	OPEN_CM = xdg-open
	LEAKS = valgrind --tool=memcheck --leak-check=full --track-origins=yes
else
	LDFLAGS = -lgtest -lm
	OPEN_CM = open
	LEAKS = leaks -atExit --
endif

rebuild: clean all

all: test

#============= LIBRIRY ==============================================================

# s21_containers.a:
# 	${CC} -g ${CFLAGS} -c ${CFILES} -I .
# 	ar rc ${LIB} *.o
# 	ranlib ${LIB}
# 	rm -rf *.o

# gcov_s21_containers.a:
# 	${CC} -g ${CFLAGS} ${GCOV_FLAGS} -c ${CFILES}  -I .
# 	ar rc ${LIB} *.o
# 	ranlib ${LIB}

#============= CLEAN ================================================================

clean:
	rm -rf *.o *.out *.a s21_test *.gcno *.gcda test.* .clang-format
	rm -rf *.gcov *.log *.html *.css report *.dSYM *.info out test_gcov test

FREE = rm -rf test.c *.o *.gcda *.gcno out

#============= STYLE ================================================================

format_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.cc *.h */*/*.h */*/*.tpp tests/*.cc
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.cc *.h */*/*.h */*/*.tpp tests/*.cc
	rm -f .clang-format

#============= TEST =================================================================

test: clean test.o
	${CC} $(CFLAGS) ${GCOV_FLAGS} ${TEST_OBJ} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

test.o:
	${CC} ${CFLAGS} ${GCOV_FLAGS} -g -c ${TEST_FILES} ${INC}

gcov_report: clean test.o
	${CC} $(CFLAGS) ${GCOV_FLAGS} ${TEST_OBJ} -o ${CEXE} ${LDFLAGS}
	./${CEXE}
	mkdir -p report
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
# gcovr --html-details report/index.html --html-medium-threshold 80 --html-high-threshold 100 --html-title "s21_containers coverage report"
	${FREE}
# ${OPEN_CM} ./report/index.html 

vg: clean test.o  
	${CC} ${TEST_OBJ} ${GCOV_FLAGS} -o out ${LDFLAGS}
	chmod a+x out
	${LEAKS} ./out
	${FREE}

#============= DEBUG ================================================================

debug: clean
	${CC} -g $(CFLAGS) main.cc -o ${CEXE} ${INC}
	./${CEXE}

memory: clean
	${CC} -g $(CFLAGS) main.cc -o ${CEXE} ${INC}
	${LEAKS} ./${CEXE}