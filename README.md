# Finding-the-K-Closest-Sheep-IDs-Search-Algorithm-Analysis-
This project focuses on finding the K closest values to a given target in a sorted array, inspired by a real-world scenario where sheep are identified by unique, non-consecutive IDs. When a sheep is removed from the system, the goal is to efficiently identify the K sheep with the closest IDs to the missing one.

Three different search algorithms are implemented and adapted for this task:

Linear Search

Binary Search

Jump Search

Each algorithm is modified to handle cases where the target value does not exist in the array and instead return the K nearest values, prioritizing smaller IDs in tie situations.

To evaluate performance, the project generates sorted random arrays of various sizes, ranging from small to very large datasets. For each array size, the algorithms are tested with different values of K (from very small to large fractions of the array size). Execution times are measured and compared to analyze how algorithm efficiency scales with input size and K.

The results are presented using tables and performance plots, allowing comparison between theoretical time complexities and observed execution times. The project also includes a detailed discussion of best, average, and worst-case behaviors, as well as how sorting assumptions affect each algorithm.

This project demonstrates algorithm adaptation, time complexity analysis, performance benchmarking, and experimental evaluation of search algorithms in C++.
