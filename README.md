Implementation of skip list data structure that allows O(logn) search and insert
complexity (skipList.h). Implementation is done following W. Pugh's paper:
ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf.
To compare skip list insertion, search and erase time complexity, liked list
data structure was also implemented (linkedList.h).

CMake is used for project build. For building tests for testSkipList.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList. Doxygen is used for project documentation.

To build project and project documentation, go to root directory:
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc

To run tests:
$ cd test
$ ./tests

To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
To check coverage: gcov-10 testSkipList.cpp.gcno

Benchmark results:

-------------------------------------------------------------------------------
Benchmark - insert and search of element in linked and skip list
-------------------------------------------------------------------------------
/Users/vedrana/Desktop/skipList/test/testSkipList.cpp:135
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Insert one element in skip list                100            77    10.4412 ms
                                        1.40681 us    1.37992 us    1.47343 us
                                        200.392 ns    66.6338 ns    364.574 ns

Insert one element in linked list              100          1089    10.3455 ms
                                        92.6299 ns    91.4913 ns    94.6685 ns
                                        7.51313 ns    4.74313 ns    11.6833 ns



Search one element in skip list of
100000 elements

                                        4.07136 us    3.35856 us    5.86336 us
                                        5.01957 us    213.914 ns     9.2014 us

Search one element in linked list
of 100000 element                              100             2    12.0076 ms
                                        75.042 us     63.637 us    131.292 us
                                       112.129 us     2.0257 us    267.535 us

Erase of one element in skip list
of 100000 elements                             100            45     10.575 ms
                                       2.47298 us    2.41253 us     2.5932 us
                                       416.367 ns    246.566 ns    703.115 ns

Erase of one element in linked list
of 100000 element                              100             1     1.77054 s
                                         18.2395 ms    17.9913 ms    18.6135 ms
                                         1.5291 ms    1.11387 ms    2.00928 ms


As expected, insert is shorter in linked list, but search, and also erase,
are shorter for skip list.
