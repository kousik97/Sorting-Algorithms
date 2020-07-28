# Sort & Selection Algorithms
Optimised generic sort and selection algorithms - C++

Cohort of algorithms implemented : 
  1. Insertion Sort
  2. Merge Sort
  3. Quick Sort
  4. Heap Sort
  5. Bubble sort
  6. Intro-sort
  
Partitioning algorithms implemented:
  1. Hoare Partition - 2 pointer style partition
  2. Lomuto Partition
  3. Lomuto Partition with improvements towards branch prediction
  
The algorithms were benchmarked on 10 million randomly generated floating point numbers. The average time taken from 10 runs are reprted below:
  1. Intro-sort with hoare partition - 2265 ms
  2. Intro-sort with lomuto partition - 3560 ms
  3. Intro-sort with lomuto branchless - 4534 ms
  4. std::sort - 3043 ms

All codes were tested on AMD Ryzen 7 3700x machine with base clock of 3.59 Ghz with 512KB/4MB/32MB cache hierarchy wunning windows 10.
The intro-sort algorithm implemented are optimised only for numeric values. FOr the rest, the code works but could be sub-par to std::sort.

  

