#include "top-it-vector.hpp"
#include <cstddef>
#include <ios>
#include <iostream>
#include <utility>

bool testDefaultVector()
{
  topit::Vector< int > v;
  bool c = v.isEmpty();
  return c;
}

bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yay = v;
  bool isAllEqual = v.getSize() == yay.getSize();
  for (size_t i = 0; i < v.getSize(); i++) {
    isAllEqual = isAllEqual && v[i] == yay[i];
  } 
  return isAllEqual;
}

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testAfterPopEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.popBack();
  return v.isEmpty();
}

bool testSizeAfterPop()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v.getSize() == 1;
}
int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair< const char*, test_t >;
  pair_t tests[] = {
    {"Default vector is empty", testDefaultVector},
    {"Default vector is not empty", testVectorWithValue},
    {"Inbound access elements", testCopyConstructor},
    {"Elements must be equal", testElementAccess},
    {"Vector after pop back must be empty", testAfterPopEmpty},
    {"Vector after pop back must have size = 1", testAfterPopEmpty}
  };
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; i++) {
    bool res = tests[i].second();
    std::cout << res << ": ";
    std::cout << tests[i].first << '\n';
    pass = pass && res;
  }
  std::cout << "Result: " << pass << '\n';
}
