CLANG = clang-10
GCC = gcc

TARGET = fib.ll dax.ll

CILK_FLAGS = -fcilkplus
CFLAGS = -O3
PARAS = -DMATRIX_N=${N_SIZE}

.PHONY : clean all

clean : fib.ll fib.s dax.ll dax.s
	rm -rf $^

all: fib.ll fib.s dax.ll dax.s

fib.ll : fib.c
	${CLANG} $^ -S -emit-llvm -o $@

dax.ll : dax.c
	${CLANG} $^ -S -emit-llvm -o $@

fib.s : fib.ll
	${CLANG} $^ -S -o $@

dax.s : dax.ll
	${CLANG} $^ -S -o $@
