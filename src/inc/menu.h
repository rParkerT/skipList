#pragma once

#include "skipList.h"
#include <iostream>
#include <limits>
#include <string>

namespace list {

/**
 * Implementation of the Menu selection class for Skip List.
 *
 * Menu selection offers few actions for Skip List, that user can choose from:
 * insert new node with user defined key,
 * erase node for given key,
 * search node for given key,
 * quit menu
 *
 * @tparam T type of data stored in Skip List
 */

template <typename T> class MenuSelection {
private:
  /**
   *  New node, with user defined key, is inserted in Skip List.
   *
   *  @tparam skipList Skip List
   */
  void insertNodeinList(SkipList<T> &skipList);

  /**
   *  Node, with user defined key, is erased from Skip List.
   *
   *  @tparam skipList Skip List
   */
  void eraseNode(SkipList<T> &skipList);

  /**
   *  Node, with user defined key, is searched in Skip List.
   *
   *  @tparam skipList Skip List
   */
  void searchNode(SkipList<T> &skipList);

  /**
   *  Ask for user input, until the user enters valid input value for Skip List.
   *
   *  @tparam value key value of Skip List
   */
  void checkForInvalidInput(T &value);

public:
  /// Constructor takes no arguments
  MenuSelection(){};
  ~MenuSelection(){};

  /**
   *  Select an action for Skip List.
   *  User can select actions, until Q (quit) is selected.
   *
   *  @tparam skipList Skip List
   */
  void select(SkipList<T> &skipList);
};

const char *menu = R"help(
Select action for skip list
To insert element to skip list, enter - I
To erase element in skip list, enter - E
To search element of skip list, enter - S
To exit app, enter - Q
)help";

template <typename T> void MenuSelection<T>::select(SkipList<T> &skipList) {
  char selection;

  do {
    std::cout << menu;
    std::cin >> selection;

    if (selection == 'I' || selection == 'i') {
      std::cout << "adding element" << std::endl;
      insertNodeinList(skipList);
    } else if (selection == 'E' || selection == 'e') {
      std::cout << "erasing element" << std::endl;
      eraseNode(skipList);
    } else if (selection == 'S' || selection == 's') {
      std::cout << "search element in skip list" << std::endl;
      searchNode(skipList);
    } else if (selection != 'I' && selection != 'i' && selection != 'E' &&
               selection != 'e' && selection != 'Q' && selection != 'q' &&
               selection != 'S' && selection != 's')
      std::cout << "unknown input" << std::endl;
  } while (selection != 'Q' && selection != 'q');
}

template <typename T>
void MenuSelection<T>::insertNodeinList(SkipList<T> &skipList) {
  T value;
  checkForInvalidInput(value);
  if (!skipList.insertNode(value))
    std::cout << "Duplicate, no node added" << std::endl;
  else
    std::cout << "Inserted node with value " << value << std::endl;
}

template <typename T> void MenuSelection<T>::eraseNode(SkipList<T> &skipList) {
  T value;
  checkForInvalidInput(value);
  if (!skipList.eraseNode(value))
    std::cout << "No node in skip list with value " << value << " to erase"
              << std::endl;
  else
    std::cout << "Erased node with value " << value << std::endl;
}

template <typename T> void MenuSelection<T>::searchNode(SkipList<T> &skipList) {
  T value;
  checkForInvalidInput(value);
  if (!skipList.searchNode(value))
    std::cout << "No node found with value " << value << " in skip list"
              << std::endl;
  else
    std::cout << "Found node with value " << value << std::endl;
}

template <typename T> void MenuSelection<T>::checkForInvalidInput(T &value) {
  std::cout << "Add value of new node" << std::endl;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input of value, try again: ";
  }
}
} // namespace list
