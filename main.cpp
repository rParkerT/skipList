#include <iostream>
#include <string>
#include "menu.h"
#include "skipList.h"
#include <thread>

using namespace std;

int main() {

	SkipList<int> sList;

	cout << "Starting..... " << endl;

	chrono::time_point<chrono::system_clock> start, end; 

	start = chrono::system_clock::now(); 
	for (int i = 0; i < 10000; ++i){
        sList.insertNode(i, i, true);
    }
    end = chrono::system_clock::now(); 
  
    chrono::duration<double> elapsed_seconds = end - start; 
  
    cout << "Elapsed time for inserting of 10000 elements in skip list: " << elapsed_seconds.count() << " s" << endl; 

	select(sList);

	return 0;
}
