#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../src/inc/linkedList.h"
#include "../src/inc/skipList.h"
#include <catch.hpp>

TEST_CASE("Skip List Insert") {
  list::SkipList<int> sList;
  for (int i = 0; i < 1000; ++i) {
    sList.insertNode(i);
  }
  REQUIRE(sList.insertNode(222) == false);
}

TEST_CASE("Skip List Check if all inserted") {
  list::SkipList<int> sList;
  for (int i = 0; i < 1000; ++i) {
    sList.insertNode(i);
  }
  for (int i = 0; i < 1000; ++i) {
    REQUIRE(sList.searchNode(i) == true);
  }
  sList.insertNode(1000);
  REQUIRE(sList.searchNode(1000) == true);
}

TEST_CASE("Skip List Erase") {
  list::SkipList<int> sList;
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
  list::SkipList<int> sList;
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
  list::SkipList<int> sList;
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
  list::SkipList<float> sList;
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
  list::SkipList<std::string> sList;
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

TEST_CASE("Benchmark - insert and search of element in linked and skip list ") {
  list::SkipList<int> sList;

  BENCHMARK("Insert one element in skip list") { return sList.insertNode(-1); };

  list::LinkedList<int> lList;
  BENCHMARK("Insert one element in linked list") {
    return lList.insertNode(-1);
  };

  for (int i = 0; i < 100000; ++i) {
    sList.insertNode(i);
  }

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

TEST_CASE("Benchmark - search of one element in linked list ") {
  list::LinkedList<int> lList;
  int nThreads = 2;
  std::vector<std::thread> threads(nThreads);

  BENCHMARK("Insert of 1000 elements in linked list - 2 threads") {
    threads[0] = std::thread([&lList]() {
      for (int j = 0; j < 500; j++) {
        lList.insertNode(j);
      }
    });
    threads[1] = std::thread([&lList]() {
      for (int j = 500; j < 1000; j++) {
        lList.insertNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };

  for (int i = 0; i < 1000; ++i) {
    REQUIRE(lList.searchNode(i) == true);
  }

  BENCHMARK(
      "Search of 1000 element in linked list of 1000 elements - 2 threads") {
    threads[0] = std::thread([&lList]() {
      for (int j = 0; j < 500; j++) {
        lList.searchNode(j);
      }
    });
    threads[1] = std::thread([&lList]() {
      for (int j = 500; j < 1000; j++) {
        lList.searchNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };

  for (int i = 0; i < 1000; ++i) {
    REQUIRE(lList.searchNode(i) == true);
  }

  BENCHMARK("Erase of 1000 elements in linked list - 2 threads") {
    threads[0] = std::thread([&lList]() {
      for (int j = 0; j < 500; j++) {
        lList.eraseNode(j);
      }
    });
    threads[1] = std::thread([&lList]() {
      for (int j = 500; j < 1000; j++) {
        lList.eraseNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };
}

TEST_CASE("Benchmark - search of one element in skip list  - 2 threads") {
  list::SkipList<int> sList;
  int nThreads = 2;
  std::vector<std::thread> threads(nThreads);

  BENCHMARK("Insert of 1000 elements in skip list - 2 threads") {
    threads[0] = std::thread([&sList]() {
      for (int j = 0; j < 500; j++) {
        sList.insertNode(j);
      }
    });
    threads[1] = std::thread([&sList]() {
      for (int j = 500; j < 1000; j++) {
        sList.insertNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };

  for (int i = 0; i < 1000; ++i) {
    REQUIRE(sList.searchNode(i) == true);
  }

  BENCHMARK("Search of 1000 element in skip list of 1000 elements") {
    threads[0] = std::thread([&sList]() {
      for (int j = 0; j < 500; j++) {
        sList.searchNode(j);
      }
    });
    threads[1] = std::thread([&sList]() {
      for (int j = 500; j < 1000; j++) {
        sList.searchNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };

  BENCHMARK("Erase of 1000 elements in skip list - 2 threads") {
    threads[0] = std::thread([&sList]() {
      for (int j = 0; j < 500; j++) {
        sList.eraseNode(j);
      }
    });
    threads[1] = std::thread([&sList]() {
      for (int j = 500; j < 1000; j++) {
        sList.eraseNode(j);
      }
    });
    for (auto &thread : threads) {
      thread.join();
    }
  };
}

TEST_CASE("Insert, search and erase in linked list ") {
  list::LinkedList<int> lList;
  int nThreads = 3;
  std::vector<std::thread> threads(nThreads);

  threads[0] = std::thread([&lList]() {
    for (int j = 0; j < 10; j++) {
      sList.insertNode(j);
    }
  });
  threads[1] = std::thread([&lList]() {
    for (int j = 0; j < 10; j++) {
      sList.searchNode(j);
    }
  });
  threads[2] = std::thread([&lList]() {
    for (int j = 0; j < 10; j++) {
      sList.eraseNode(j);
    }
  });
  for (auto &thread : threads) {
    thread.join();
  }
}

TEST_CASE("Insert, search and erase in skip list ") {
  list::SkipList<int> sList;
  int nThreads = 3;
  std::vector<std::thread> threads(nThreads);

  threads[0] = std::thread([&sList]() {
    for (int j = 0; j < 10; j++) {
      sList.insertNode(j);
    }
  });
  threads[1] = std::thread([&sList]() {
    for (int j = 0; j < 10; j++) {
      sList.searchNode(j);
    }
  });
  threads[2] = std::thread([&sList]() {
    for (int j = 0; j < 10; j++) {
      sList.eraseNode(j);
    }
  });
  for (auto &thread : threads) {
    thread.join();
  }
}
