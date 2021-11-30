## Mini Project #2

### Description:
You will be working with a threads program. You will need to be creative and may try different approaches to test the parallelism between threads. Your mission is to have a global array in your code with 6000 integers, initialized with values 1 to 6000 in the main program (array[i]=i). You will also create 3 threads (identified by tid values 1 to 3). Each one of them will add the values of the array with subscripts in the range (tid -1)*2000 to (tid*2000-1) to a global variable TOTAL, one value at a time (do not add them up in temporary variable before adding to the TOTAL, i.e., it must be coded as TOTAL = TOTAL + array[i]).\
\
You will run the code initially without using semaphores and in a second run, with semaphores and report any difference in the results. Your main program should print the TOTAL value after all threads have completed their work. You will hand in the printout of your source code containing the semaphores solution and the output values of both runs (with and without semaphores) on the due date (no late work will be accepted). Use Cygwin or any other Unix/Linux system you may have access to. You can work in a group of at most 3 students.\
\
Hints: you may need to use the function pthread_join(), but you will not need conditional variables. gcccompiler should work and create a file a.exe in Cygwin, if using C++ then the compiler should be g++ Executing a.exe>out.txt will redirect the output to the file out.txt. You may need to run the program with ./a.exe depending on how your system is configured. The next two examples should help with the coding. 


## P-Threads Programming: Advanced Computer Architecture:

### Description:
You are going to create a pthreaded array calculator. The calculator must be able to perform the typical traditional arithmetic operations, such as addition, substraction, multiplication, division.\
- Arrays a, and b are integer arrays, with 1’000.000 million integers each.
-	All the elements in array a are 1, while all those in b are 2.
-	The addition function will create array “addition”, in which addition[0] = a[0] + b[0], etc (You get the idea). Follow a similar logic for substraction, multiplication and division.
\
Task # 1:\
- Write a threaded program that uses four (4) threads.  In this program
- Thread 0 will take care of the addition
- Thread 1 susbtraction 
- Thread 2 multipliaction
- Thread 3 division

