#pragma once

#include <iostream>

namespace list {

/**
 * Implementation of the ordered Linked List class.
 *
 * Linked List is a linear collection of data elements in which every element
 * points to the next element. This class was added in order to compare time
 * duration of insertion and search of element in Skip List and Linked List. It
 * is expected that duration of element insertion is longer in Skip List, but
 * search of element is shorter.
 *
 * @tparam V type of data stored in Linked List
 */
template <typename V> class LinkedList {
private:
  /**
   * Implementation of the Node structure.
   *
   * Each Node carries a key and a pointer to next Node.
   *
   * @tparam V data type of key in Node
   */
  struct Node {
    V value;    ///< key value of Node
    Node *next; ///< pointer to next Node in Linked List

    /**
     * Node constructor.
     * Each Node is constructed using key value and pointer to next Node.
     *
     * @tparam T data type of key in Node
     */
    explicit Node(V v) : value(v), next(nullptr) {}
  };

  /**
   * Head Node's value is the smallest value of each Node in Linked List.
   */
  Node *head = nullptr;

  /**
   * Adds Node to Linked List
   *
   * @tparam V data type of key in Node
   *
   * @return Node with set value
   */
  Node *addNode(V value) { return new Node(value); }

public:
  /**
   * Constructor of Linked List
   *
   * Constructor takes no arguments. During Linked List object construction,
   * head Node is created.
   *
   */
  LinkedList();

  /**
   * Destructor  of Linked List
   *
   * During Linked List destruction, all elements of Linked List are deleted.
   *
   */
  ~LinkedList();

  /// Disabling construction of Linked List object using copy constructor
  LinkedList(const LinkedList &rhs) = delete;

  /// Disabling construction of Linked List object using copy assignment
  LinkedList &operator=(const LinkedList &rhs) = delete;

  /**
   * Insert Node to Linked List
   *
   * Nodes are inserted in order, from the lowest to the highest key value. All
   * links for Node that's to be inserted are fetched. Pointer of predecessor
   * and new Node, and new Node and next Node is connected.
   *
   * @tparam V newValue key value of Node
   *
   */
  void insertNode(V newValue);

  /**
   * Removes Node to Linked List
   *
   * Pointers of Node's predecessor is fetched. Pointers of
   * predecessor and successor of removed Node are connected.
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * deleted in Skip List, else returns false
   */
  bool eraseNode(V value);

  /**
   * Search Node in Linked List for given key value
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * inserted in Linked List, else returns false
   */
  const bool searchNode(V value);
};

template <typename V> LinkedList<V>::LinkedList() {
  V valueMin = std::numeric_limits<V>::min();
  head = new Node(valueMin);
}

template <typename V> LinkedList<V>::~LinkedList() {
  Node *current = head;
  while (current) {
    head = current->next;
    delete current;
    current = head;
  }
}

template <typename V> void LinkedList<V>::insertNode(V newValue) {
  Node *tempNode, *newNode;
  newNode = addNode(newValue);
  tempNode = head;
  while (tempNode->next != nullptr && tempNode->next->value < newValue) {
    tempNode = tempNode->next;
  }
  newNode->next = tempNode->next;
  tempNode->next = newNode;
}

template <typename V> bool LinkedList<V>::eraseNode(V newValue) {
  Node *tempNode, *prevNode;
  tempNode = head;
  while (tempNode != nullptr && tempNode->value != newValue) {
    prevNode = tempNode;
    tempNode = tempNode->next;
  }
  if (prevNode->next == nullptr) {
    return false;
  } else {
    prevNode->next = tempNode->next;
    delete tempNode;
    return true;
  }
  return false;
}

template <typename V> const bool LinkedList<V>::searchNode(V value) {
  Node *tempNode = head;
  while (tempNode != nullptr) {
    if (tempNode->value == value) {
      return true;
    }
    tempNode = tempNode->next;
  }
  return false;
}

} // namespace list

