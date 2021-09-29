#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "linkedList.h"
#include "skipList.h"
#include <catch.hpp>

// SkipList test for integer values
TEST_CASE("Skip List Check if all inserted") {
  list::SkipList<int> sList;
  for (int i = 0; i < 1000; ++i) {
    sList.insertNode(i);
  }
  // 222 is already inserted, no duplicates
  REQUIRE(sList.insertNode(222) == false);
  for (int i = 0; i < 1000; ++i) {
    REQUIRE(sList.searchNode(i) == true);
  }
  sList.insertNode(1000);
  REQUIRE(sList.searchNode(1000) == true);
  REQUIRE(sList.insertNode(2000) == true);
  REQUIRE(sList.searchNode(2100) == false);
  REQUIRE(sList.searchNode(1) == true);
  REQUIRE(sList.eraseNode(1) == true);
  REQUIRE(sList.eraseNode(2) == true);
  REQUIRE(sList.eraseNode(2222) == false);
  REQUIRE(sList.eraseNode(-20) == false);
  REQUIRE(sList.eraseNode(333) == true);
}

// SkipList test for float values
TEST_CASE("Skip List Float") {
  list::SkipList<float> sList;
  float a = 1.0;
  float b = 22.3;
  float c = 36.83;
  REQUIRE(sList.insertNode(a) == true);
  REQUIRE(sList.insertNode(b) == true);
  REQUIRE(sList.insertNode(c) == true);
  REQUIRE(sList.insertNode(c) == false);
  REQUIRE(sList.searchNode(a) == true);
  REQUIRE(sList.searchNode(b) == true);
  REQUIRE(sList.searchNode(c) == true);
  REQUIRE(sList.searchNode(0) == false);
  REQUIRE(sList.eraseNode(c) == true);
  REQUIRE(sList.searchNode(c) == false);
}

// SkipList test for TestStringObject, this tests concepts defined in SkipList
// class
TEST_CASE("Skip List Insert TestStringObject") {
  struct TestStringObject {
    std::string value;
    std::string to_string() { return value; }
  };

  list::SkipList<TestStringObject> sList;
  struct TestStringObject a = {"Ana"};
  REQUIRE(sList.insertNode(a) == true);
  struct TestStringObject b = {"Bob"};
  REQUIRE(sList.insertNode(b) == true);
  struct TestStringObject j = {"Joe"};
  REQUIRE(sList.insertNode(j) == true);
  REQUIRE(sList.insertNode(j) == false);
  REQUIRE(sList.searchNode(a) == true);
  REQUIRE(sList.searchNode(b) == true);
  REQUIRE(sList.searchNode(j) == true);
  REQUIRE(sList.eraseNode(j) == true);
  REQUIRE(sList.searchNode(j) == false);
  REQUIRE(sList.insertNode(j) == true);
}

// SkipList test for TestIntegerObject, this tests concepts defined in SkipList
// class
TEST_CASE("Skip List Insert TestIntegerObject") {
  struct TestIntegerObject {
    int value;
    std::string to_string() { return std::to_string(value); }
  };
  list::SkipList<TestIntegerObject> sList;
  struct TestIntegerObject a = {1};
  REQUIRE(sList.insertNode(a) == true);
  struct TestIntegerObject b = {2};
  REQUIRE(sList.insertNode(b) == true);
  struct TestIntegerObject j = {3};
  REQUIRE(sList.insertNode(j) == true);
  REQUIRE(sList.insertNode(j) == false);
  REQUIRE(sList.searchNode(a) == true);
  REQUIRE(sList.searchNode(b) == true);
  REQUIRE(sList.searchNode(j) == true);
  REQUIRE(sList.eraseNode(j) == true);
  REQUIRE(sList.searchNode(j) == false);
  REQUIRE(sList.insertNode(j) == true);
}

// SkipList test for TestPersonObject, this tests concepts defined in SkipList
// class
TEST_CASE("Skip List Insert TestPersonObject") {
  struct TestPersonObject {
    std::string value;
    int age;
    std::string to_string() { return value + ", " + std::to_string(age); }
  };
  list::SkipList<TestPersonObject> sList;
  struct TestPersonObject a = {"Ana", 25};
  REQUIRE(sList.insertNode(a) == true);
  struct TestPersonObject b = {"Bob", 35};
  REQUIRE(sList.insertNode(b) == true);
  struct TestPersonObject j = {"Joe", 33};
  REQUIRE(sList.insertNode(j) == true);
  REQUIRE(sList.insertNode(j) == false);
  REQUIRE(sList.searchNode(a) == true);
  REQUIRE(sList.searchNode(b) == true);
  REQUIRE(sList.searchNode(j) == true);
  REQUIRE(sList.eraseNode(j) == true);
  REQUIRE(sList.searchNode(j) == false);
  REQUIRE(sList.insertNode(j) == true);
}

// SkipList test for TestFailConceptClass, this tests concepts defined in
// SkipList class
TEST_CASE("Skip List Insert TestClass") {
  struct TestFailConceptClass {
    int key;
    float value;
  };
  list::SkipList<TestFailConceptClass> sList;
  struct TestFailConceptClass a = {1, 2};
  REQUIRE(sList.insertNode(a) == true);
  // This line is commented, because the compile will faile, since TestClass
  // does not have to_string() member function which is a requirement for
  // SearchNode concept
  //  REQUIRE(sList.searchNode(a) == true);
}

TEST_CASE("Insert into linked list, search and erase nodes") {
  list::LinkedList<int> lList;
  for (int i = 0; i < 1000; ++i) {
    lList.insertNode(i);
  }
  for (int i = 0; i < 1000; ++i) {
    REQUIRE(lList.searchNode(i) == true);
  }
  lList.insertNode(1000);

  REQUIRE(lList.searchNode(1000) == true);
  REQUIRE(lList.searchNode(2100) == false);
  REQUIRE(lList.searchNode(1) == true);
  lList.eraseNode(1);
  lList.eraseNode(2);
  lList.eraseNode(2222);
  lList.eraseNode(-20);
  lList.eraseNode(333);

  REQUIRE(lList.searchNode(1000) == true);
  REQUIRE(lList.searchNode(1) == false);
  REQUIRE(lList.searchNode(2) == false);
  REQUIRE(lList.searchNode(333) == false);
}

// SkipList and LinkedList benchmark comparison for insert of 100 elements
TEST_CASE("Benchmark - insert of elements in linked and skip list ") {
  list::SkipList<int> sList;

  BENCHMARK("Insert 100 element in skip list") {
    for (int i = 0; i < 100; ++i) {
      sList.insertNode(i);
    }
  };

  list::LinkedList<int> lList;
  BENCHMARK("Insert 100 element in linked list") {
    for (int i = 0; i < 100; ++i) {
      lList.insertNode(i);
    }
  };
}

// SkipList and LinkedList benchmark comparison for insert search and erase of
// element in lists of 100000 elements
TEST_CASE("Benchmark - search and erase of element in linked and skip list ") {
  list::SkipList<int> sList;

  for (int i = 0; i < 100000; ++i) {
    sList.insertNode(i);
  }

  list::LinkedList<int> lList;
  for (int i = 0; i < 100000; ++i) {
    lList.insertNode(i);
  }

  int element = 85317;

  BENCHMARK("Search one element in skip list of 100000 elements") {
    return sList.searchNode(element);
  };

  BENCHMARK("Search one element in linked list of 100000 element") {
    return lList.searchNode(element);
  };

  BENCHMARK("Erase of one element in skip list of 100000 elements") {
    return sList.eraseNode(element);
  };

  BENCHMARK("Erase of one element in linked list of 100000 element") {
    return lList.eraseNode(element);
  };
}
