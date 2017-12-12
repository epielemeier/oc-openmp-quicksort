# OpenMP Quicksort
OpenMP implementation of sorting data with Quicksort. Prints out a pretty table for varying size `arrays` and `threads`. This benchmark sorts the same data set 3 times for each configuration and displays the minimum run time. For CMSC-5813 Parallel Programming with Dr. Patton at Oklahoma Christian University.

Solved by **Emily Pielemeier**.

Sample output:
```
 # Threads | # Elements                                                                                           |
           | 10                     |  100                    |  1000                   |  10000                  | 
           | Time      | Efficiency |  Time      | Efficiency |  Time      | Efficiency |  Time      | Efficiency | 
         1 | 0.000001  | 1.000000   |  0.000008  | 1.000000   |  0.000172  | 1.000000   |  0.002709  | 1.000000   | 
         2 | 0.000003  | 0.211357   |  0.000011  | 0.361266   |  0.000144  | 0.597299   |  0.001559  | 0.868686   | 
         4 | 0.003266  | 0.000089   |  0.006036  | 0.000328   |  0.002955  | 0.014538   |  0.014498  | 0.046714   | 
         8 | 0.000034  | 0.004234   |  0.000037  | 0.027072   |  0.000159  | 0.135134   |  0.001597  | 0.212034   | 
```

## Prerequisites
1. C compiler, i.e. `gcc`
2. [CMake](https://cmake.org/download/)
3. [OpenMP](http://www.openmp.org/resources/openmp-compilers-2/)

Runs on **Linux**.
