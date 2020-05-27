# bin-packing
### The Program:
In the bin packing problem, items of different weights (or sizes) must be packed into a finite number of bins each with the capacity C in a way that minimizes the number of bins used. The decision version of the bin packing problem (deciding if objects will fit into <= k bins) is NPcomplete. There is no known polynomial time algorithm to solve the optimization version of the bin packing problem. In this homework you will be examining three greedy approximation algorithms to solve the bin packing problem.

* First-Fit: Put each item as you come to it into the first (earliest opened) bin into which it fits. If there is no available bin then open a new bin.
* First-Fit-Decreasing: First sort the items in decreasing order by size, then use First-Fit on the resulting list.
* Best Fit: Place the items in the order in which they arrive. Place the next item into the bin which will leave the least room left over after the item is placed in the bin. If it does not fit in any bin, start a new bin. No partial item should be in a bin.

Implement the algorithms in Python, C++ or C. Your program named binpack should read in a text file named bin.txt with multiple test cases as explained below and output to the terminal the number of bins each algorithm calculated for each test case. Submit a README file and your program to TEACH.

### Example bin.txt:
The first line is the number of test cases, followed by the capacity of bins for that test case, the number of items and then the weight of each item. You can assume that the weight of an item does not exceed the capacity of a bin for that problem.  
3  
20  
6  
5 10 2 5 4 4  
10  
20  
2 2 2 2 2 2 2 2 2 2 6 6 6 6 6 6 6 6 6 6  
10  
4  
3 8 2 7  

## Sample output:
Test Case 1 First Fit: 2, First Fit Decreasing: 2, Best Fit: 2  
Test Case 2 First Fit: 12, First Fit Decreasing: 12, Best Fit: 12  
Test Case 3 First Fit: 3, First Fit Decreasing: 3, Best Fit: 2  


## To Run the Program:
1. Give yourself permission to the compiler using: "chmod 777 compileall".
2. Run "compileall" to compile the code.
3. To run the program, type "Bin".