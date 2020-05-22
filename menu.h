#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "skipList.h"

using namespace std;

// select the actions for skip list :
// insert new node
// erase node
// print all nodes
// exit selection
template<typename T>
void select(SkipList<T>& skipList) noexcept {

	char selection;

	do {

	cout << endl;
	cout << "Select action for skip list" << endl;
	cout << "To insert element to skip list, enter - I" << endl;
	cout << "To erase element in skip list, enter - E" << endl;
	cout << "To print elements of skip list, enter - P" << endl;
	cout << "To search element of skip list, enter - S" << endl;
	cout << "To exit app, enter - Q" << endl;
	cout << endl;
	cin >> selection;

	if (selection == 'I' || selection == 'i') {
		cout << "adding element" << endl;
		insertNode(skipList);
	}
	else if (selection == 'E' || selection == 'e') {
		cout << "erasing element" << endl;
		eraseNode(skipList);
	}
	else if (selection == 'P' || selection == 'p') {
		cout << "print all elements" << endl;
		print(skipList);
	}
	else if (selection == 'S' || selection == 's') {
		cout << "search element in skip list" << endl;
		searchNode(skipList);
	}
	else if (selection != 'I' && selection != 'i' && 
			selection != 'E' && selection != 'e' &&
			selection != 'P' && selection != 'p' &&
			selection != 'Q' && selection != 'q' &&
			selection != 'S' && selection != 's')
		cout << "unknown input" << endl;
	} while (selection != 'Q' && selection != 'q');
		
}

// insert new node in skip list with key and value defined by user
template<typename T>
void insertNode(SkipList<T>& skipList) {

	int key = 0;
	cout << "Add key of new node" << endl;
    while(!(cin >> key)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input of key, try again: ";
    }

	T value;
	cout << "Add value of new node" << endl;
    while(!(cin >> value)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input of value, try again: ";
    }

	skipList.insertNode(key, value, false);
}

// erase node in skip list with key defined by user
template<typename T>
void eraseNode(SkipList<T>& skipList) {

	int key = 0;
	cout << "Add key of node that's to be deleted" << endl;
    while(!(cin >> key)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input of key, try again: ";
    }

	skipList.eraseNode(key);
}

// print all nodes in skip list
template<typename T>
void print(const SkipList<T>& skipList) {

	skipList.print();
}

// search node in skip list with key defined by user
template<typename T>
void searchNode(SkipList<T>& skipList) {

	int key = 0;
	cout << "Add key of node that's to be searched" << endl;
    while(!(cin >> key)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input of key, try again: ";
    }

	skipList.searchNode(key);
}