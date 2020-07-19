Implementation of skip list data structure that allows O(logn) search and insert
complexity (skipList.h). Implementation is done following W. Pugh's paper:
ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf.
Menu to select actions: insert, search and erase was added for skip list (menu.h)
To compare skip list insertion, search and erase time complexity, liked list
data structure was also implemented (linkedList.h).
Both data structures are concurrent.
CMake is used for project build. For building tests for testSkipedList.cpp,
Catch2 repo from GitHub (https://github.com/catchorg/Catch2)
is pulled in local project skipList.
File structure is as follows:
skipList
    | CMakeLists.txt
    |-----> src
    |        | CMakeLists.txt
    |        | main.cpp
    |        |-----> inc
    |                  |-----> skipList.h
    |                  |-----> linkedList.h
    |                  |-----> menu.h
    |-----> test
             | CMakeLists.txt
             |-----> testSkipedList.cpp

To build project and run tests or main:
cmake build -- build       -  saves build files in created build folder   
make all
cd test/
./tests     -    runs all tests in testSkipedList.cpp
or:
cd src/
./skipList  -    runs main


To compare these to data structures, benchmark Catch2 tests were added
(testSkipList.cpp). As expected, linked list has faster insert and erase,
but skip list is faster in search of elements in the list. Here is the example
of benchmark output for these data structures:

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Insert one element in skip list                100            50      10.84 ms
                                        2.20633 us    2.16787 us    2.29147 us
                                        276.884 ns    118.582 ns    478.696 ns

Insert one element in linked list              100           793    10.6262 ms
                                         163.77 ns    156.401 ns    172.806 ns
                                        41.5704 ns    35.9946 ns    50.9687 ns

Search one element in skip list of                                             
100000 elements                                100           139    10.6335 ms
                                        769.545 ns    766.543 ns    780.439 ns
                                        26.0155 ns    7.10899 ns    59.7865 ns

Search one element in linked list                                              
of 100000 element                              100             2    12.5936 ms
                                        61.5393 us    60.9219 us      62.71 us
                                        4.17478 us    2.55764 us    6.76565 us

Erase of one element in skip list                                              
of 100000 elements                             100            40     10.776 ms
                                        2.68774 us    2.66127 us    2.74899 us
                                        193.849 ns    102.949 ns    381.691 ns

Erase of one element in linked list                                            
of 100000 element                              100           672    10.6176 ms
                                        136.839 ns    133.376 ns    148.808 ns
                                        29.1111 ns    8.44665 ns    65.6563 ns
