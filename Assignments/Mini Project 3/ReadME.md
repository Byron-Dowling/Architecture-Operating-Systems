## Mini Project #3 : Table Lookaside Buffer

### Description:
Your assignment consists of designing and implementing a program that will analyze the use of a TLB in a paged memory system. TLBs are fully associative cache memory that store the page table entries in use. They are very small, and in this case you will assume that they can store 12 entries. Your program will read the file available for download through the class web page (found on cs.mwsu.edu/~passos or D2L) and identify the page table entries accessed and stored in the TLB, reporting the total number of misses (misses happen when the required page was not in the TLB and have to be brought in). The size of a page is 4096 bytes and the addresses recorded in the file are byte addresses. The TLB uses a FIFO replacement algorithm.\
\
The data file has 1 million addresses. Your program will accept several types of records of input data,
according to the following format:\
\
Code Address (in hexadecimal)\
Where Code is identified by a single digit with the meaning described below. This value does not affect the TLB simulation and should be ignored. The Address is your key information for the simulation:\
0 - address for data read\
1 - address for data write\
2 - address for instruction fetch\
\
An example of the data file contents could be:\
2 415130\
0 1010acac\
2 415134\
\
An example of the analysis, assuming only 20 pages were read and they were:\
1,9,2,1,13,15,12,4,1,9,3,21,19, 15,12,14,17,10,1,21 would result in 14 misses (pages 1, 9, 2, 13, 15, 12, 4, 3, 21,19, 14,17,10, 1)\
\
The address size is 32 bits. A hexadecimal address, shorter than 32 bits, such as AB16 means 000000AB16.\
\
The program must be written in C or C++ and be the smallest possible code to solve the problem. DO NOT CODE ANY SOLUTION THAT CAN BE APPLIED TO OTHER PROBLEMS (HINT: you can readhexadecimal numbers in C++ using unsigned integers and the command FILE>>hex>>number;)
