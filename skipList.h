#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <random>
#include <chrono>

using namespace std;

template<typename V>
class SkipList {
private:
	// skip list consists of nodes
	template<typename T>
	struct Node {
		int key;
		T value;
		vector<Node<T>*> forward{};

		// each node carries a key, value and a forward vector carrying pointers to nodes of a different level
		Node(int k, T v, int level) :
			key(k), value(v), forward(level, nullptr) {}
	};

	// probability is the same to increase or not to increase level for entered node
	const float probability = 0.5;

	// fixes max level value for entire skip list
	static constexpr int maxLevel = 16;

	// used for loop of levels
	int level;

	// special nodes that handle if the list is empty and also configure edges, big enough that
	// the user entry keys will fall between
	Node<V>* head;
	Node<V>* nil;

	// insert node in skip list
	void insertNode(int newKey, V newValue);

	// calculates number of levels for node using rng
	int getRandomLevel() const;

	// adds node to skip list
	Node<V>* addNode(int key, V value, int level);

	chrono::time_point<chrono::system_clock> start, end;

public:
	SkipList();
	~SkipList();

	SkipList(const SkipList &rhs) = delete;
	SkipList& operator=(const SkipList &rhs) = delete;

	// parametar used to determine number of links between nodes in search
	int numberOfLinks = 0;

	// number of nodes created in list
	static int numberOfElements;

	// insert node in skip list, add info about time lapse if insertInLoop = false
	// if insertInLoop = true, time lapse info is done in main
	void insertNode(int newKey, V newValue, bool insertInLoop);

	// removes node from skip list
	void eraseNode(int key);

	// prints all nodes in skip list
	const void print() const;

	// searches node for given key
	const void searchNode(int key);

};

template<typename V>
int SkipList<V>::numberOfElements = 0;

template<typename V>
SkipList<V>::SkipList() {

	int min = numeric_limits<int>::min();
	V valueMin = numeric_limits<V>::min();
    head = new Node<V>(min, valueMin, maxLevel);

    int max = numeric_limits<int>::max();
	V valueMax = numeric_limits<V>::max();
    nil = new Node<V>(max, valueMax, maxLevel);

	// point head to nil node
	level = 0;
	while(level < maxLevel) {
		head->forward.at(level) = nil;
		level++;
	}
}

template<typename V>
SkipList<V>::~SkipList() {

	Node<V>* p = head;
    while (p) {
        head = p->forward.at(0);
		delete p;
	    p = head;
    }
}

template<typename V>
void SkipList<V>::insertNode(int newKey, V newValue, bool insertInLoop) {
	if (insertInLoop == true) {
		insertNode(newKey, newValue);
	}
	else {
		start = chrono::system_clock::now();
		insertNode(newKey, newValue);
    	end = chrono::system_clock::now();
    	chrono::duration<double> elapsed_seconds = end - start;

    	cout << "Elapsed time for inserting element in skip list: " << elapsed_seconds.count() << " s" << endl;
	}

}

template<typename V>
void SkipList<V>::insertNode(int newKey, V newValue) {

	Node<V>* tempNode = head;
	vector<Node<V>*> tempNodeLevels(maxLevel,nullptr);

	// get all links for node that's to be inserted
    for (level = maxLevel-1; level >= 0; --level) {
        while (tempNode->forward.at(level)->key < newKey && tempNode->forward.at(level)!=nil) {
            tempNode = tempNode->forward.at(level);
        }
        tempNodeLevels.at(level) = tempNode;
    }

	tempNode = tempNode->forward.at(0);

	// if the node with the key already exists, set it's value to new value
	if (tempNode != nil && tempNode->key == newKey){
    	tempNode->value = newValue;
    }
	else {
    	// create new node
    	const int newNodeLevel = getRandomLevel();
    	Node<V>* newNode = addNode(newKey, newValue, newNodeLevel);

    	// connect pointers of predecessors and new node to respective successors
		level = 0;
		while (level < newNodeLevel) {
        	newNode->forward.at(level) = tempNodeLevels.at(level)->forward.at(level);
        	tempNodeLevels.at(level)->forward.at(level) = newNode;
			level++;
    	}
	}
}

template<typename V>
void SkipList<V>::eraseNode(int key) {

	start = chrono::system_clock::now();
	Node<V>* tempNode = head;
	vector<Node<V>*> tempNodeLevels(maxLevel,nullptr);

	// get all links for node that's to be erased
    for (level = maxLevel-1; level >= 0; --level) {
        while (tempNode->forward.at(level)->key < key && tempNode->forward.at(level)!=nil) {
            tempNode = tempNode->forward.at(level);
        }
        tempNodeLevels.at(level) = tempNode;
    }

	tempNode = tempNodeLevels.at(0)->forward.at(0);
	// remove node
	if ((tempNode->key == key) && (tempNode != nil)) {
		for (size_t i = 0; i < tempNodeLevels.size(); ++i) {
			if(tempNodeLevels.at(i)->forward.at(i) == tempNode)
				tempNodeLevels.at(i)->forward.at(i) = tempNode->forward.at(0);
    	}
		delete tempNode;
	}

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Elapsed time for erasing element in skip list: " << elapsed_seconds.count() << " s" << endl;
}

template<typename V>
const void SkipList<V>::print() const {

	Node<V>* addedNode = head->forward.at(0);
    cout << endl;
    while (addedNode != nil) {
		cout << "level : " << addedNode->forward.size() << ", key : " << addedNode->key << ", value : " << addedNode->value;
        addedNode = addedNode->forward.at(0);
        cout << endl;
    }
    cout << endl;
}

template<typename V>
const void SkipList<V>::searchNode(int key) {

	start = chrono::system_clock::now();
    Node<V>* searchNode = head;
    for (level = maxLevel-1; level >= 0; --level) {
        while ( searchNode->forward.at(level)->key < key) {
            searchNode = searchNode->forward.at(level);
			numberOfLinks++;
		}
	}

	searchNode = searchNode->forward.at(0);

			if(searchNode->key == key && searchNode!=nil)
				cout << "Found a node with key : " << searchNode->key << " , with value: " << searchNode->value << endl;

			else
				cout << "Key : " << key << " not found" << endl;


    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Elapsed time for search of element in skip list: " << elapsed_seconds.count() << " s" << endl;


	cout << "Number of links in search is: " << numberOfLinks << endl;
	cout << "Number of elements in the list is: " << numberOfElements << endl;
	cout << "Ideal cost of search is log(n): " << log(numberOfElements) << endl;

	numberOfLinks = 0;
}

template<typename V>
typename SkipList<V>::template Node<V>* SkipList<V>::addNode(int key, V value, int level) {

	numberOfElements++;
	return new Node<V>(key, value, level);
}

template<typename V>
int SkipList<V>::getRandomLevel() const {

    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);
	// set default level to 1
	int level = 1;
	//	probabilty if the level will rise or not is the same, if it's rising, limit rise
	// till maxLevel
    while (unif(rng) < 0.5 && level < maxLevel) {
        level++;
    }

    return level;
}
