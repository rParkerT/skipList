Implementation of skip list data structure that allows O(logn) search and insert
complexity (skipList.h). Implementation is done following W. Pugh's paper:
ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf.
To compare skip list insertion, search and erase time complexity, liked list
data structure was also implemented (linkedList.h).

CMake is used for project build. For building tests for testSkipList.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
<pre>
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./tests
</pre>
To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
To check coverage: gcov-10 testSkipList.cpp.gcno

Benchmark results:
<pre>
-------------------------------------------------------------------------------
Benchmark - insert of elements in linked and skip list
-------------------------------------------------------------------------------
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Insert 100 element in skip list                100             1    17.8937 ms
                                        180.507 us    177.927 us    186.457 us
                                        18.7549 us    9.66014 us    36.4911 us

Insert 100 element in linked list              100             1    229.881 ms
                                        5.07832 ms    4.84784 ms    5.31391 ms
                                         1.1898 ms    1.09066 ms    1.30104 ms


-------------------------------------------------------------------------------
Benchmark - search and erase of element in linked and skip list
-------------------------------------------------------------------------------
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Search one element in skip list of                                             
100000 elements                      
                                        4.09596 us    3.37509 us    7.02422 us
                                        6.44995 us    1.23271 us    15.0965 us

Search one element in linked list                                              
of 100000 element                              100             1    35.6833 ms
                                        348.197 us    340.187 us    357.677 us
                                        44.4439 us     38.529 us    50.7627 us

Erase of one element in skip list                                              
of 100000 elements                             100            50      10.73 ms
                                        2.95974 us    2.79894 us    3.23794 us
                                        1.05164 us    704.315 ns    1.81654 us

Erase of one element in linked list                                            
of 100000 element                              100             1     42.764 ms
                                        436.727 us    426.697 us    449.237 us
                                        56.6339 us    48.2948 us    68.9935 us

</pre>

Since the search is more efficient in skip list, that is why all the operations are
faster for skip list. To make insert more efficient in linked list, ordering should be removed,
but that would make search even more slower.
