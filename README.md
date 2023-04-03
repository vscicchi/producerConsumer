# producerConsumer

This program is an example of the Producer and Consumer Problem, in which
two different programs work between a buffer to manage items. The producer
creates the items, and the consumer consumes them, removing them from the
buffer. The purpose of the project is to give an example of OS tracking of
processes entering critical sections of code, allowing them to execute the
needed parts for their program while not interfering with other processes
that run with them.

In this version of the program, there is a maximum of two items that can
exist at any one time on the buffer. Adding to it when it is full will not
go through, nor will consuming an item when there are zero in the buffer.
This particular program uses semaphores to allow certain sections of code to
execute and provide a system of regulation in the program.

To run the program:
- 1 will add an item to the buffer
- 2 will remove an item from the buffer
- 0 will close the program
