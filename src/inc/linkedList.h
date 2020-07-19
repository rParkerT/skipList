#pragma once

#include <iostream>
#include <mutex>
#include <thread>

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
   * @tparam T data type of key in Node
   */
  template <typename T> struct Node {
    T value;       ///< key value of Node
    Node<T> *next; ///< pointer to next Node in Linked List

    /**
     * Node constructor.
     * Each Node is constructed using key value and pointer to next Node.
     *
     * @tparam T data type of key in Node
     */
    Node(T v) : value(v), next(nullptr) {}
  };

  /**
   * Head Node's value is the smallest value of each Node in Linked List.
   */
  Node<V> *head = nullptr;

  /**
   * Adds Node to Linked List
   *
   * @tparam V data type of key in Node
   *
   * @return Node with set value
   */
  Node<V> *addNode(V value) { return new Node<V>(value); }

  std::mutex findPredecessor; ///< Node mutex, used to protect Node from
                              ///< multiple thread accesses

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
   * Destructor  of Skip List
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
   * and new Node, and new Node and next Node is connected. If the list is
   * empty, Node is inserted as head Node. If the value of new Node is smaller
   * then the value of head Node, new Node is set as head Node.
   *
   * @tparam V newValue key value of Node
   *
   */
  void insertNode(V newValue);

  /**
   * Removes Node to Skip List
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
  head = new Node<V>(valueMin);
}

template <typename V> LinkedList<V>::~LinkedList() {
  Node<V> *current = head;
  while (current) {
    head = current->next;
    delete current;
    current = head;
  }
}

template <typename V> void LinkedList<V>::insertNode(V newValue) {
  std::lock_guard<std::mutex> guard(findPredecessor);
  Node<V> *tempNode, *newNode;
  newNode = addNode(newValue);
  tempNode = head;
  if (tempNode->next != nullptr && tempNode->next->value < newValue) {
    tempNode = tempNode->next;
  }
  newNode->next = tempNode->next;
  tempNode->next = newNode;
}

template <typename V> bool LinkedList<V>::eraseNode(V newValue) {
  std::lock_guard<std::mutex> guard(findPredecessor);
  Node<V> *tempNode, *prevNode;
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
  std::lock_guard<std::mutex> guard(findPredecessor);
  Node<V> *tempNode = head;
  while (tempNode != nullptr) {
    if (tempNode->value == value) {
      return true;
    }
    tempNode = tempNode->next;
  }
  return false;
}

} // namespace list
