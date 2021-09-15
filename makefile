
#LIBRARY MODULE
GCC:=g++
FLAGS:=-g
SOURCES:=$(shell find . -name  "*.cpp" ! -path "./Test/*" )
HEADERS:=$(shell find . -name  "*.h" ! -path "./Test/*" )
INC:=
LIBS:=
OUTPUT:=libSerializer

all : ${OUTPUT}.a test
	./testing

${OUTPUT}.a : ${SOURCES} ${HEADERS}
	${GCC} ${SOURCES} ${INC} ${FLAGS} -c
	ar rcs ${OUTPUT}.a *.o
	objdump -drCat -Mintel --no-show-raw-insn ${OUTPUT}.a > ${OUTPUT}.s
	rm -f *.o

clear :
	rm -f ${OUTPUT}.a *.o *.s
	rm -f testing

test : test/test.cpp
	g++ test/test.cpp ../Tester/libTester.a ${OUTPUT}.a ${INC} ${LIBS} ${FLAGS} -o testing