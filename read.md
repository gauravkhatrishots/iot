-this is a echo program,it prints the input taken from stdin to stdout.
-the program uses two threads, and a pipe.
-the main thread opens a pipe and gets two descriptors of the pipe .
-pd[0] ,file descriptor to read the pipe.
-pd[1] ,file descriptor to write into the pipe.
-input  thread is reading the  value from user and writing it into the pipe 
 using the pd[1] descriptor of the pipe(descriptors are global so both thread has
 access to the pipe.). 
-print thread  is printing the value from the pipe using pd[0] only after input thread
 has written into the pipe .
-the thread synchronization is doing using two semaphores .
-rsem semaphore with initial value '1' for controling execution of read thread.
-psem semaphore with intial value '0' for controlling execution of print thread.
-since initial value of rsem is 1 ,read thread  will be able to go into its
 critical section .
-since initial value of psem is 0 ,print thread will wait for the psem 
 to become 1 , so that it can go into its critical section.
-while entering into its critical section ,read thread makes its rsem value to
 0 (from 1) so it will have to wait for the rsem to become 1 again to enter into 
 its critical section.
-after reading the value from stdin , read thread will post the psem
 (change the value of psem from 0 to 1) , now the print thread can execute.
-now print thread will be able to enter into its critical section (psem is 1 now)
 after entering the value of psem becomes 0 (sem_wait makes it 0 ).
-after printing the value it post the rsem (makes it 1 ) so the rthread now can read 
 again.

both the thread are working continously in while 1 loop.
