## Mini Project #1

### Description:
You just got a job at GOOGLE (Giant OOps: Geeks Learning from Errors) Google has decided to add one utility to its operating system. You are called to write the new utility. The program should read an integer number N from the input and using multiple processes to speed up the answer, print values from 1 to N. The main program will create 2 children.\
\
The first child will print values 1 to N/3 (integer division), the second child will print from N/3 +1 to 2N/3, while the main program prints the remaining values. Your mission is to write the program (it should be very short, less than 50 lines for sure) that creates the new child processes and executes the printing (screen display). You will submit your source code through D2L on or before the due date (make it a text file: .txt). You must use C or C++ in the CYGWIN system or any UNIX like system. You can work in a group of at most 3 students.\

#### Possible input: 
10
1 2 3 (output of first child)\
4 5 6 (output of the second child)\
7 8 9 10 (output of the main program)\
\
Hints: notice that because the program are running concurrently, the output in the screen may be a little different such as 1 4 5 7 2 3 6 8 9 10. The user never types anything wrong so you do not need to check the input for errors. It is also important to notice that you could write such a program without using fork, however you are required to do it. An example of printing command for an integer number x in C language is printf(“text %d”, x);
