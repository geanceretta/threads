# threads
Pi calculation using series, multiple threads, comparing elapsed time when using more cores of the CPU, and stabilizing when more threads are created than availiable on CPU.

For compiling, use this parameters (use `-lm` only if ld return error for pow):

`gcc pi-series.c -lpthread -o pi-series.bin -lm`

# Some test results:
![](https://github.com/geanceretta/threads/blob/master/threads-vs-time.png)

# Future improvements:
Including graphs of CPU utilization:
https://github.com/rigel314/ttysys
