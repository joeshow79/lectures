CLANG = clang-10
GCC = gcc
#GCC = g++

TARGET = cmm_loop_ijk cmm_loop_ikj cmm_cilk_ijk cmm_cilk_ikj cmm_loop_ijk_o3 cmm_loop_ikj_o3 cmm_cilk_ijk_o3 cmm_cilk_ikj_o3 cmm_cilk_auto_tile mm_dac_auto_thresh mm_dac_auto_thresh_simd mm_clang_simd

N_SIZE = 4096
CILK_FLAGS = -fcilkplus
CFLAGS = -O3
PARAS = -DMATRIX_N=${N_SIZE}

.PHONY : clean test

#cmm_c: cmm.c
#	${CLANG} cmm.c -o $@

cmm_loop_ijk: cmm_loop_ijk.c
	${GCC} $^ ${PARAS} -o $@
	./$@

cmm_cilk_ijk: cmm_cilk_ijk.c
	${GCC} $^ ${CILK_FLAGS} ${PARAS} -o $@
	./$@

cmm_loop_ikj: cmm_loop_ikj.c
	${GCC} $^ ${PARAS} -o $@
	./$@

cmm_cilk_ikj: cmm_cilk_ikj.c
	${GCC} $^ ${CILK_FLAGS} ${PARAS} -o $@
	./$@

cmm_loop_ijk_o3: cmm_loop_ijk.c
	${GCC} $^ ${CFLAGS} ${PARAS} -o $@
	./$@

cmm_cilk_ijk_o3: cmm_cilk_ijk.c
	${GCC} $^ ${CILK_FLAGS} ${CFLAGS} ${PARAS} -o $@
	./$@

cmm_loop_ikj_o3: cmm_loop_ikj.c
	${GCC} $^ ${CFLAGS} ${PARAS} -o $@
	./$@

cmm_cilk_ikj_o3: cmm_cilk_ikj.c
	${GCC} $^ ${CILK_FLAGS} ${CFLAGS} ${PARAS} -o $@
	./$@

cmm_cilk_auto_tile: cmm_cilk_auto_tile.c
	${GCC} $^ ${CILK_FLAGS} ${CFLAGS} ${PARAS} -o $@
	./$@

mm_dac_auto_thresh: mm_dac_auto_thresh.c
	#${GCC} $^ ${CILK_FLAGS} ${CFLAGS} ${PARAS} -o $@
	./$@

mm_dac_auto_thresh_simd: mm_dac_auto_thresh.c
	${GCC} $^ ${CILK_FLAGS} ${CFLAGS} ${PARAS} -march=native -ffast-math -o $@
	./$@

mm_clang_simd: cmm_loop_ikj.c
	${CLANG} -O3 -std=c99 -Rpass=vector -ffast-math -march=native ${PARAS} $^ -o $@
	./$@

all: ${TARGET}

clean: 
	rm -f ${TARGET}	

test: ${TARGET}
	@for t in `echo ${TARGET}`; do \
	    echo ">Testing ./$${t}" ; \
            ./$${t} ; \
	done

cachegrind: 
	valgrind --tool=cachegrind  ./cmm_loop_ijk

#valgrind --tool=cachegrind  ./cmm_c
#Compute 128x128 in i,j,k order MM took 0.534158 mm
#==1107== Cachegrind, a cache and branch-prediction profiler
#==1107== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
#==1107== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
#==1107== Command: ./cmm_c
#==1107== 
#--1107-- warning: L3 cache found, using its data for the LL simulation.
#==1107== 
#==1107== I   refs:      55,075,610
#==1107== I1  misses:         1,217
#==1107== LLi misses:         1,186
#==1107== I1  miss rate:       0.00%
#==1107== LLi miss rate:       0.00%
#==1107== 
#==1107== D   refs:      28,514,251  (23,947,741 rd   + 4,566,510 wr)
#==1107== D1  misses:     2,129,042  ( 2,122,201 rd   +     6,841 wr)
#==1107== LLd misses:         8,753  (     2,041 rd   +     6,712 wr)
#==1107== D1  miss rate:        7.5% (       8.9%     +       0.1%  )
#==1107== LLd miss rate:        0.0% (       0.0%     +       0.1%  )
#==1107== 
#==1107== LL refs:        2,130,259  ( 2,123,418 rd   +     6,841 wr)
#==1107== LL misses:          9,939  (     3,227 rd   +     6,712 wr)
#==1107== LL miss rate:         0.0% (       0.0%     +       0.1%  )
