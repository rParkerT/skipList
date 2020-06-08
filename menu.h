#pragma once

#include "skipList.h"
#include <iostream>
#include <limits>
#include <string>

// select the actions for skip list :
// insert new node
// erase node
// print all nodes
// exit selection
template <typename T> void select(SkipList<T> &skipList) noexcept {
  char selection;

  do {
    std::cout << std::endl;
    std::cout << "Select action for skip list" << std::endl;
    std::cout << "To insert element to skip list, enter - I" << std::endl;
    std::cout << "To erase element in skip list, enter - E" << std::endl;
    std::cout << "To print elements of skip list, enter - P" << std::endl;
    std::cout << "To search element of skip list, enter - S" << std::endl;
    std::cout << "To exit app, enter - Q" << std::endl;
    std::cout << std::endl;
    std::cin >> selection;

    if (selection == 'I' || selection == 'i') {
      std::cout << "adding element" << std::endl;
      insertNodeinList(skipList);
    } else if (selection == 'E' || selection == 'e') {
      std::cout << "erasing element" << std::endl;
      eraseNode(skipList);
    } else if (selection == 'P' || selection == 'p') {
      std::cout << "print all elements" << std::endl;
      print(skipList);
    } else if (selection == 'S' || selection == 's') {
      std::cout << "search element in skip list" << std::endl;
      searchNode(skipList);
    } else if (selection != 'I' && selection != 'i' && selection != 'E' &&
               selection != 'e' && selection != 'P' && selection != 'p' &&
               selection != 'Q' && selection != 'q' && selection != 'S' &&
               selection != 's')
      std::cout << "unknown input" << std::endl;
  } while (selection != 'Q' && selection != 'q');
}

// insert new node in skip list with key and value defined by user
template <typename T> void insertNodeinList(SkipList<T> &skipList) {
  T value;
  std::cout << "Add value of new node" << std::endl;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input of value, try again: ";
  }
  if (!skipList.insertNode(value))
    std::cout << "Duplicate, no node added" << std::endl;
  else
    std::cout << "Inserted node with value " << value << std::endl;
}

// erase node in skip list with key defined by user
template <typename T> void eraseNode(SkipList<T> &skipList) {
  T value;
  std::cout << "Add value of node that's to be deleted" << std::endl;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input of value, try again: ";
  }
  if (!skipList.eraseNode(value))
    std::cout << "No node in skip list with value " << value << " to erase"
              << std::endl;
  else
    std::cout << "Erased node with value " << value << std::endl;
}

// print all nodes in skip list
template <typename T> void print(const SkipList<T> &skipList) {
  skipList.print();
}

// search node in skip list with key defined by user
template <typename T> void searchNode(SkipList<T> &skipList) {
  T value;
  std::cout << "Add value of node that's to be searched" << std::endl;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input of value, try again: ";
  }
  if (!skipList.searchNode(value))
    std::cout << "No node found with value " << value << " in skip list"
              << std::endl;
  else
    std::cout << "Found node with value " << value << std::endl;
}
