#pragma once

#include <iostream>
#include <limits>
#include <math.h>
#include <random>
#include <vector>

template <typename T> struct Node {
  T value;
  std::vector<Node<T> *> forward{};

  // each node carries a key, value and a forward vector carrying pointers to
  // nodes of a different level
  Node(T v, int level) : value(v), forward(level, nullptr) {}
};

template <typename V> class SkipList {
private:
  // probability is the same to increase or not to increase level for entered
  // node
  const float probability = 0.5;

  // fixes max level value for entire skip list
  static constexpr int maxLevel = 16;

  // used for loop of levels
  int level = 0;

  // special nodes that handle if the list is empty and also configure edges,
  // big enough that the user entry keys will fall between
  Node<V> *head = nullptr;
  Node<V> *nil = nullptr;

  // calculates number of levels for node using rng
  int getRandomLevel() const;

  // adds node to skip list
  Node<V> *addNode(V value, int level) { return new Node<V>(value, level); }

public:
  SkipList();
  ~SkipList();

  SkipList(const SkipList &rhs) = delete;
  SkipList &operator=(const SkipList &rhs) = delete;

  // insert node in skip list
  bool insertNode(V newValue);

  // removes node from skip list
  bool eraseNode(V value);

  // prints all nodes in skip list
  const void print() const;

  // searches node for given key
  const bool searchNode(V value);
};

template <typename V> SkipList<V>::SkipList() {
  V valueMin = std::numeric_limits<V>::min();
  head = new Node<V>(valueMin, maxLevel);

  V valueMax = std::numeric_limits<V>::max();
  nil = new Node<V>(valueMax, maxLevel);

  // point head to nil node
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

template <typename V> bool SkipList<V>::insertNode(V newValue) {
  Node<V> *tempNode = head;
  std::vector<Node<V> *> tempNodeLevels(maxLevel, nullptr);

  // get all links for node that's to be inserted
  for (level = maxLevel - 1; level >= 0; --level) {
    while (tempNode->forward.at(level)->value < newValue &&
           tempNode->forward.at(level) != nil) {
      tempNode = tempNode->forward.at(level);
    }
    tempNodeLevels.at(level) = tempNode;
  }

  tempNode = tempNode->forward.at(0);

  // if the node with the key already exists, set it's value to new value
  if (tempNode != nil && tempNode->value == newValue) {
    return false;
  } else {
    // create new node
    const int newNodeLevel = getRandomLevel();
    Node<V> *newNode = addNode(newValue, newNodeLevel);

    // connect pointers of predecessors and new node to respective successors
    level = 0;
    while (level < newNodeLevel) {
      newNode->forward.at(level) = tempNodeLevels.at(level)->forward.at(level);
      tempNodeLevels.at(level)->forward.at(level) = newNode;
      level++;
    }
  }
  return true;
}

template <typename V> bool SkipList<V>::eraseNode(V value) {
  Node<V> *tempNode = head;
  std::vector<Node<V> *> tempNodeLevels(maxLevel, nullptr);

  // get all links for node that's to be erased
  for (level = maxLevel - 1; level >= 0; --level) {
    while (tempNode->forward.at(level)->value < value &&
           tempNode->forward.at(level) != nil) {
      tempNode = tempNode->forward.at(level);
    }
    tempNodeLevels.at(level) = tempNode;
  }

  tempNode = tempNodeLevels.at(0)->forward.at(0);
  // remove node
  if ((tempNode->value == value) && (tempNode != nil)) {
    for (size_t i = 0; i < tempNodeLevels.size(); ++i) {
      if (tempNodeLevels.at(i)->forward.at(i) == tempNode)
        tempNodeLevels.at(i)->forward.at(i) = tempNode->forward.at(i);
    }
    delete tempNode;
    return true;
  }
  return false;
}

template <typename V> const void SkipList<V>::print() const {
  Node<V> *addedNode = head->forward.at(0);
  std::cout << std::endl;
  while (addedNode != nil) {
    std::cout << "level : " << addedNode->forward.size()
              << ", value : " << addedNode->value;
    addedNode = addedNode->forward.at(0);
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename V> const bool SkipList<V>::searchNode(V value) {
  Node<V> *searchNode = head;

  for (level = maxLevel - 1; level >= 0; --level) {
    while (searchNode->forward.at(level)->value < value &&
           searchNode->forward.at(level) != nil) {
      searchNode = searchNode->forward.at(level);
    }
  }

  searchNode = searchNode->forward.at(0);

  if (searchNode->value == value && searchNode != nil)
    return true;
  else
    return false;
}

template <typename V> int SkipList<V>::getRandomLevel() const {
  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
  rng.seed(ss);
  // initialize a uniform distribution between 0 and 1
  std::uniform_real_distribution<double> unif(0, 1);
  // set default level to 1
  int level = 1;
  //	probabilty if the level will rise or not is the same, if it's rising,
  // limit rise
  // till maxLevel
  while (unif(rng) < 0.5 && level < maxLevel) {
    level++;
  }
  return level;
}
