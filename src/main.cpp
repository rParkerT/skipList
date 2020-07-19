#include "inc/linkedList.h"
#include "inc/menu.h"
#include "inc/skipList.h"
#include <iostream>

int main() {

  list::SkipList<int> sList;
  list::MenuSelection<int> menu;
  menu.select(sList);
  return 0;
}
