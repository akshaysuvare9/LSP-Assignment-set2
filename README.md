# LSP-Assignment-set2

1.
6_mtspawn: write a Pthreads MT (multithreaded) app to spawn threads; the number of threads to spawn is to be given as a command-line parameter (you require a validity check on max number of threads to create based on both the resource limit RLIMIT_NPROC (use the prlimit(2) to query it) and the overall system limit) 

[Weightage: 5]


2.
7_mtcopy: write a Pthreads MT (multithreaded) app to copy a large file to a specified destination directory; determine the number of threads to use based on the number of CPU cores on your system (it must be dynamic, not hard-coded); have each thread copy a (calculated) portion of the source file to the destination file (test this program with file size >= 1 GB and ensure it works as advertised) [Weightage: 10]
