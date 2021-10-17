
#LIBRARY MODULE
GCC:=g++
FLAGS:=-Wall -Wextra -Wpedantic -g -O1 -std=c++17
SOURCES:=$(shell find ./src -name  "*.cpp" )
HEADERS:=$(shell find ./src -name  "*.h" )
INC:=
LIBS:=
INSTALL_DIR:=${HOME}/.local
NAME:=Serializer
OUTPUT:=build/lib${NAME}.a

all : ${OUTPUT} testing

${OUTPUT} : ${SOURCES} ${HEADERS}
	mkdir -p build
	${GCC} ${SOURCES} ${INC} ${FLAGS} -c
	ar rcs ${OUTPUT} *.o
	objdump -drCat -Mintel --no-show-raw-insn ${OUTPUT} > ${OUTPUT}.s
	rm -f *.o

clear :
	rm -rf build
	rm -rf tests/build
	rm -rf tests/output

build/test: tests/test.cpp ${OUTPUT}
	g++ tests/test.cpp ${OUTPUT} ${INC} ${LIBS} -lTester ${FLAGS} -o build/test

testing : build/test
	rm -rf tests/output
	mkdir tests/output
	./build/test

install: ${OUTPUT} uninstall
	@echo ">>installing to ${INSTALL_DIR}"
	mkdir -p ${INSTALL_DIR}/lib
	cp ${OUTPUT} ${INSTALL_DIR}/lib/lib${NAME}.a
	mkdir -p ${INSTALL_DIR}/include/${NAME}
	for FILE in ${HEADERS}; do \
	F=$$(dirname $$FILE); \
	mkdir -p ${INSTALL_DIR}/include/${NAME}$${F#./src}; \
	cp $${FILE} ${INSTALL_DIR}/include/${NAME}$${FILE#./src}; \
	done

uninstall: 
	rm -f ${INSTALL_DIR}/lib/${OUTPUT}
	rm -rf ${INSTALL_DIR}/include/${NAME}