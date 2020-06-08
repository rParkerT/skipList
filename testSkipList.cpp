// g++ -std=c++14 -o test-runner testSkipList.cpp catchMain.cpp
// ./test-runner
#include "catch.hpp"
#include "skipList.h"

TEST_CASE("Skip List Insert") {
  SkipList<int> sList;
  for (int i = 0; i < 1000; ++i) {
    sList.insertNode(i);
  }
  REQUIRE(true);
  REQUIRE(sList.insertNode(222) == false);
}

TEST_CASE("Skip List Erase") {
  SkipList<int> sList;
  sList.insertNode(1);
  sList.insertNode(2);
  sList.insertNode(3);
  REQUIRE(sList.eraseNode(1) == true);
  REQUIRE(sList.eraseNode(2) == true);
  REQUIRE(sList.eraseNode(20) == false);
  REQUIRE(sList.eraseNode(-20) == false);
  REQUIRE(sList.eraseNode(3) == true);
}

TEST_CASE("Skip List Search") {
  SkipList<int> sList;
  sList.insertNode(1);
  sList.insertNode(2);
  sList.insertNode(3);
  REQUIRE(sList.searchNode(1) == true);
  REQUIRE(sList.searchNode(2) == true);
  REQUIRE(sList.searchNode(0) == false);
  REQUIRE(sList.searchNode(200) == false);
  REQUIRE(sList.searchNode(3) == true);
}

TEST_CASE("Skip List Integer All") {
  SkipList<int> sList;
  for (int i = 0; i < 1000; ++i) {
    sList.insertNode(i);
  }
  REQUIRE(true);
  REQUIRE(sList.searchNode(200) == true);
  REQUIRE(sList.eraseNode(200) == true);
  REQUIRE(sList.insertNode(200) == true);
  REQUIRE(sList.eraseNode(999) == true);
  REQUIRE(sList.eraseNode(1000) == false);
  REQUIRE(sList.insertNode(2000) == true);
  REQUIRE(sList.searchNode(2100) == false);
  REQUIRE(sList.searchNode(1) == true);
}

TEST_CASE("Skip List Float All") {
  SkipList<float> sList;
  sList.insertNode(1.1);
  sList.insertNode(3.3);
  REQUIRE(sList.searchNode(1.1) == true);
  REQUIRE(sList.eraseNode(1.1) == true);
  REQUIRE(sList.insertNode(1.1) == true);
  REQUIRE(sList.eraseNode(3.3) == true);
  REQUIRE(sList.eraseNode(5.5) == false);
  REQUIRE(sList.insertNode(5.5) == true);
  REQUIRE(sList.insertNode(5.5) == false);
  REQUIRE(sList.searchNode(5.5) == true);
}

TEST_CASE("Skip List String All") {
  SkipList<std::string> sList;
  std::string a("a");
  std::string b("b");
  std::string c("c");
  sList.insertNode(a);
  sList.insertNode(b);
  REQUIRE(sList.searchNode(a) == true);
  REQUIRE(sList.eraseNode(a) == true);
  REQUIRE(sList.insertNode(a) == true);
  REQUIRE(sList.eraseNode(b) == true);
  REQUIRE(sList.eraseNode(c) == false);
  REQUIRE(sList.insertNode(c) == true);
  REQUIRE(sList.insertNode(c) == false);
  REQUIRE(sList.searchNode(c) == true);
}
