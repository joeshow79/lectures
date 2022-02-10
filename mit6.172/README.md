# Course Homepage
https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-172-performance-engineering-of-software-systems-fall-2018/lecture-slides/index.htm

# Test env<br>
##Hardware: AMAX<br>
###CPU<br>

>lscpu<br>
>Architecture:          x86_64<br>
>CPU op-mode(s):        32-bit, 64-bit<br>
>Byte Order:            Little Endian<br>
>CPU(s):                32<br>
>On-line CPU(s) list:   0-31<br>
>Thread(s) per core:    2<br>
>Core(s) per socket:    8<br>
>Socket(s):             2<br>
>NUMA node(s):          2<br>
>Vendor ID:             GenuineIntel<br>
>CPU family:            6<br>
>Model:                 79<br>
>Model name:            Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz<br>
>Stepping:              1<br>
>CPU MHz:               1200.855<br>
>CPU max MHz:           3000.0000<br>
>CPU min MHz:           1200.0000<br>
>BogoMIPS:              4201.59<br>
>Virtualization:        VT-x<br>
>L1d cache:             32K<br>
>L1i cache:             32K<br>
>L2 cache:              256K<br>
>L3 cache:              20480K<br>
>NUMA node0 CPU(s):     0-7,16-23<br>
>NUMA node1 CPU(s):     8-15,24-31<br>
>Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch epb invpcid_single intel_pt ssbd ibrs ibpb stibp kaiser tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm rdseed adx smap xsaveopt cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local dtherm ida arat pln pts md_clear flush_l1d<br>
###Memory<br>
>MemTotal:       131920660 kB<br>
>MemFree:        97190088 kB<br>
>MemAvailable:   126386380 kB<br>
>Buffers:         2762540 kB<br>
>Cached:         24147912 kB<br>
>SwapCached:            0 kB<br>
>Active:          8491872 kB<br>
>Inactive:       20924064 kB<br>
>Active(anon):    2514032 kB<br>
>Inactive(anon):   287084 kB<br>
>Active(file):    5977840 kB<br>
>Inactive(file): 20636980 kB<br>
>Unevictable:           0 kB<br>
>Mlocked:               0 kB<br>
>SwapTotal:       7999484 kB<br>
>SwapFree:        7999484 kB<br>
>Dirty:               144 kB<br>
>Writeback:             0 kB<br>
>AnonPages:       2505480 kB<br>
>Mapped:          2087144 kB<br>
>Shmem:            295640 kB<br>
>Slab:            4610680 kB<br>
>SReclaimable:    3207588 kB<br>
>SUnreclaim:      1403092 kB<br>
>KernelStack:       14256 kB<br>
>PageTables:        27628 kB<br>
>NFS_Unstable:          0 kB<br>
>Bounce:                0 kB<br>
>WritebackTmp:          0 kB<br>
>CommitLimit:    73959812 kB<br>
>Committed_AS:    5937492 kB<br>
>VmallocTotal:   34359738367 kB<br>
>VmallocUsed:           0 kB<br>
>VmallocChunk:          0 kB<br>
>HardwareCorrupted:     0 kB<br>
>AnonHugePages:         0 kB<br>
>CmaTotal:              0 kB<br>
>CmaFree:               0 kB<br>
>HugePages_Total:       0<br>
>HugePages_Free:        0<br>
>HugePages_Rsvd:        0<br>
>HugePages_Surp:        0<br>
>Hugepagesize:       2048 kB<br>
>DirectMap4k:      812368 kB<br>
>DirectMap2M:     8511488 kB<br>
>DirectMap1G:    126877696 kB<br>

##OS<br>
docker ubuntu:18.04

#Compiler<br>
clang: 10.0.0<br>
gcc: 7.5.0

#Build clang to support cilk<br>
* build cilkrts
Follow guidance on git@github.com:OpenCilk/cilkrts.git to build cilkrts

* build opencilk clang 
Follow git@github.com:OpenCilk/opencilk-project.git to build clang

# build app
Refer to hw4's Makefile

#Tool<br>
valgrind
