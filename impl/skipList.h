#pragma once

#include <cassert>
#include <chrono>
#include <concepts>
#include <iostream>
#include <limits>
#include <math.h>
#include <random>
#include <vector>

namespace list {

/**
 * AllComparison concept, which specifies the requirements on template arguments
 * used in inserting, erasing and search of the Nodes in Skip List. Requirement
 * is that it is possible to use ==, != and < operator on two Node objects.
 */
template <typename T> concept AllComparison = requires(T a, T b) {
  { a == b }
  ->std::convertible_to<bool>;
  { a != b }
  ->std::convertible_to<bool>;
  { a < b }
  ->std::convertible_to<bool>;
};

/**
 * HasToStringFunction concept, which specifies the requirement on template
 * argument used in outputFunction of SkipList class. Requirement is that user
 * defined Node object have implemented to_string() function, used as info in
 * searchNode function.
 */
template <typename T> concept HasToStringFunction = requires(T a) {
  a.to_string();
};

/**
 * IsStringable concept, which specifies the requirement on template
 * argument used in outputFunction of SkipList class. Requirement is that
 * built-in Node object can be used with std::to_string() function, used as info
 * in searchNode function.
 */
template <typename T> concept IsStringable = requires(T a) {
  std::to_string(a);
};

/**
 * Printable concept, which specifies the requirement on template
 * argument used in searchNode function of SkipList class. This concept is
 * disjunction of two constraints HasToStringFunction and IsStringable.
 */
template <typename T>
concept Printable = HasToStringFunction<T> || IsStringable<T>;
;

/**
 * SearchNode concept, which specifies the requirement on template
 * argument used in searchNode function of SkipList class. This concept is
 * conjunction of two constraints AllComparison and Printable.
 */
template <typename T> concept SearchNode = AllComparison<T> &&Printable<T>;

/**
 * Implementation of the Skip List class.
 *
 * Skip List is data structure that allows O(logn) search complexity as
 * well as O(logn) insertion complexity for n elements. Implementation is done
 * following W. Pugh's paper: ftp://ftp.cs.umd.edu/pub/skipLists/skiplists.pdf
 *
 * @tparam V type of data stored in Skip List
 */
template <typename V> class SkipList {
private:
  /**
   * Implementation of the Node structure.
   *
   * Each Node carries a key and a forward vector carrying pointers to
   * nodes of a different level
   *
   * @tparam T data type of key in Node
   */
  template <typename T> struct Node {
    T value; ///< key value of Node
    std::vector<Node<T> *>
        forward{}; ///< forward vector carrying pointers to nodes, with same
    ///< values, but on a different levels

    /**
     * Node constructor.
     *
     * Each Node is constructed using key value and level size. Level size is
     * determined using random number generator function getRandomLevel().
     *
     * @tparam T data type of key in Node
     * @param level level size determined using random number generator
     */
    explicit Node(T v, int level) : value(v), forward(level, nullptr) {}
  };

  /**
   * Probability is set to be the same to increase or not to increase
   * level for entered Node
   */
  const float probability = 0.5;

  /**
   * Max Level that Node can reach. If probability is set to 0.5, choosing
   * maxLevel to be 32 is appropriate for data structures containing up to
   * 2^32 elements.
   */
  static constexpr int maxLevel = 32;

  int level = 0; ///< used in for loop of levels

  /**
   * Special Node that handles empty list and also configures low edge.
   * Head Node value is set to smallest possible value of data type of Node.
   */
  Node<V> *head = nullptr;

  /**
   * Special Node that handles empty list and also configures high edge
   * Nil node is set to highest possible value of data type of Node.
   */
  Node<V> *nil = nullptr;

  /**
   * Calculates number of levels for node using rng
   *
   * Probabilty if the level will rise or not is the same, if it's rising, limit
   * rise till maxLevel.
   */
  int getRandomLevel() const;

  /**
   * Adds Node to Skip List
   *
   * @tparam V data type of key in Node
   * @param level level size determined using random number generator
   *
   * @return Node with set value and level
   */
  Node<V> *addNode(V value, int level) { return new Node<V>(value, level); }

  /**
   * Prints value of Node if HasToStringFunction concept is satisfied
   *
   * @tparam value value of key in Node
   */
  void outputFunction(HasToStringFunction auto value) {
    std::cout << value.to_string() << std::endl;
  };

  /**
   * Prints value of Node if IsStringable concept is satisfied
   *
   * @tparam value value of key in Node
   */
  void outputFunction(IsStringable auto value) {
    std::cout << std::to_string(value) << std::endl;
  };

public:
  /**
   * Constructor of Skip List
   *
   * Constructor takes no arguments. During Skip List object construction, head
   * and nil Node are created. Head Node points to nil Node.
   *
   */
  SkipList();

  /**
   * Destructor  of Skip List
   *
   * During Skip List destruction, all elements of Skip List are deleted.
   *
   */
  ~SkipList();

  /// Disabling construction of Skip List object using copy constructor
  SkipList(const SkipList &rhs) = delete;

  /// Disabling construction of Skip List object using copy assignment
  SkipList &operator=(const SkipList &rhs) = delete;

  /**
   * Insert Node to Skip List
   *
   * Nodes are inserted in order, from the lowest to the highest key value. All
   * links for Node that's to be inserted are fetched. Pointers of predecessors
   * and new Node, and new Node and successors are connected.
   *
   * @tparam V newValue key value of Node
   *
   * @return true if Node with the same key value as newValue is not already
   * inserted in Skip List, else returns false
   */
  bool insertNode(AllComparison auto newValue);

  /**
   * Removes Node from Skip List
   *
   * All links for Node that's to be removed are fetched. Pointers of
   * predecessors and successors of removed Node are connected.
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * deleted in Skip List, else returns false
   */
  bool eraseNode(AllComparison auto value);

  /**
   * Search Node in Skip List for given key value
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * inserted in Skip List, else returns false
   */
  const bool searchNode(SearchNode auto value);

  /**
   * Operator == overloading function, friend of a SkipList class
   *
   * @tparam U lhs Node object
   * @tparam U rhs Node object
   *
   * @return true if Nodes have same key value
   */
  template <typename U> friend bool operator==(const U &lhs, const U &rhs);

  /**
   * Operator != overloading function, friend of a SkipList class
   *
   * @tparam U lhs Node object
   * @tparam U rhs Node object
   *
   * @return true if Nodes do not have same key value
   */
  template <typename U> friend bool operator!=(const U &lhs, const U &rhs);

  /**
   * Operator < overloading function, friend of a SkipList class
   *
   * @tparam U lhs Node object
   * @tparam U rhs Node object
   *
   * @return true if Node lhs has key value smaller then Node rhs key value
   */
  template <typename U> friend bool operator<(const U &lhs, const U &rhs);
};

template <typename V> SkipList<V>::SkipList() {
  V valueMin = std::numeric_limits<V>::min();
  head = new Node<V>(valueMin, maxLevel);

  V valueMax = std::numeric_limits<V>::max();
  nil = new Node<V>(valueMax, maxLevel);

  level = 0;
  while (level < maxLevel) {
    head->forward.at(level) = nil;
    level++;
  }
}

template <typename V> SkipList<V>::~SkipList() {
  Node<V> *p = head;
  while (p) {
    head = p->forward.at(0);
    delete p;
    p = head;
  }
}

template <typename V> bool operator==(const V &lhs, const V &rhs) {
  return lhs.value == rhs.value;
}

template <typename V> bool operator!=(const V &lhs, const V &rhs) {
  return lhs.value != rhs.value;
}

template <typename V> bool operator<(const V &lhs, const V &rhs) {
  return lhs.value < rhs.value;
}

template <typename V>
bool SkipList<V>::insertNode(AllComparison auto newValue) {
  Node<V> *tempNode = head;
  std::vector<Node<V> *> tempNodeLevels(maxLevel, nullptr);
  for (level = maxLevel - 1; level >= 0; --level) {
    while (tempNode->forward.at(level)->value < newValue &&
           tempNode->forward.at(level) != nil) {
      tempNode = tempNode->forward.at(level);
    }
    tempNodeLevels.at(level) = tempNode;
  }

  tempNode = tempNode->forward.at(0);
  if (tempNode != nil && tempNode->value == newValue) {
    return false;
  } else {
    const int newNodeLevel = getRandomLevel();
    Node<V> *newNode = addNode(newValue, newNodeLevel);
    level = 0;
    while (level < newNodeLevel) {
      newNode->forward.at(level) = tempNodeLevels.at(level)->forward.at(level);
      tempNodeLevels.at(level)->forward.at(level) = newNode;
      level++;
    }
  }
  return true;
}

template <typename V> bool SkipList<V>::eraseNode(AllComparison auto value) {
  Node<V> *tempNode = head;
  std::vector<Node<V> *> tempNodeLevels(maxLevel, nullptr);
  for (level = maxLevel - 1; level >= 0; --level) {
    while (tempNode->forward.at(level)->value < value &&
           tempNode->forward.at(level) != nil) {
      tempNode = tempNode->forward.at(level);
    }
    tempNodeLevels.at(level) = tempNode;
  }

  tempNode = tempNodeLevels.at(0)->forward.at(0);
  if ((tempNode->value == value) && (tempNode != nil)) {
    for (size_t i = 0; i < tempNodeLevels.size(); ++i) {
      if (tempNodeLevels.at(i)->forward.at(i) == tempNode)
        tempNodeLevels.at(i)->forward.at(i) = tempNode->forward.at(i);
    }
    return true;
  }
  return false;
}

template <typename V>
const bool SkipList<V>::searchNode(SearchNode auto value) {
  Node<V> *searchNode = head;
  for (level = maxLevel - 1; level >= 0; --level) {
    while (searchNode->forward.at(level)->value < value &&
           searchNode->forward.at(level) != nil) {
      searchNode = searchNode->forward.at(level);
    }
  }
  searchNode = searchNode->forward.at(0);
  if (searchNode->value == value && searchNode != nil) {
    std::cout << "Found : ";
    outputFunction(value);
    return true;
  }
  return false;
}

template <typename V> int SkipList<V>::getRandomLevel() const {
  std::mt19937_64 rng;
  uint64_t timeSeed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
  rng.seed(ss);
  std::uniform_real_distribution<double> unif(0, 1);
  int level = 1;
  while (unif(rng) < probability && level < maxLevel) {
    level++;
  }
  return level;
}

} // namespace list
