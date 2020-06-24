CC = gcc
INCLUDES =

ifeq (${mode}, release)
	FLAGS = -O3 -march=native -Wall -fPIC
else
	mode = debug
	FLAGS = -O3 -g -Wall -fPIC
endif

LIB_FLAGS =
OBJS = intal.o intal_sampletest.o
PROJECT_NAME = intal

ifeq (${mode}, debug)
	PROJECT = ${PROJECT_NAME}_debug
else
	PROJECT = ${PROJECT_NAME}
endif

${PROJECT}: ${OBJS} clean_emacs_files
	@echo "Building on "${mode}" mode"
	@echo ".........................."
	${CC} ${INCLUDES} ${FLAGS} ${OBJS} -o $@ ${LIB_FLAGS}
	-make clean

project_test: intal.o clean_emacs_files
	@echo "Building "$@" on "${mode}" mode"
	@echo ".........................."
	${CC} ${INCLUDES} ${FLAGS} intal.o -o $@ ${LIB_FLAGS}
	-make clean

library: libIntal.so clean_emacs_files
	@echo "Building "$@" on "${mode}" mode"
	@echo ".........................."
	-make clean

run_unit_tests: library
	@echo "Running Unit Tests"
	@echo ".........................."
	python3 intal_unit_tests.py
	@echo ".........................."
	-make clean

libIntal.so: intal.o
	${CC} -shared ${INCLUDES} ${FLAGS} intal.o -o $@ ${LIB_FLAGS}

intal.o:
	${CC} ${INCLUDES} ${FLAGS} -c intal.c -o $@ ${LIB_FLAGS}
intal_sampletest.o:
	${CC} ${INCLUDES} ${FLAGS} -c intal_sampletest.c -o $@ ${LIB_FLAGS}

.PHONEY: clean clean_emacs_files clean_all
clean:
	-rm -rf ${OBJS}
clean_emacs_files:
	-rm -rf *~
clean_all: clean clean_emacs_files
	-rm -rf ${PROJECT_NAME} ${PROJECT_NAME}_debug project_test libIntal.so
