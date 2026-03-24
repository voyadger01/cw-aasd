#include "top-it-vector.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
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

bool testElementConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int >& rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testElementOutOfBoundCheckedAccess()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementInboundCheckedAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    int &val = v.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testElementOutOfBoundConstCheckedAccess()
{
  topit::Vector< int > v;
  const topit::Vector< int >& rv = v;
  try {
    rv.at(0);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementInboundConstCheckedAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int >& rv = v;
  try {
    const int &val = rv.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
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

bool testAfterPopFrontEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.popFront();
  return v.isEmpty();
}

bool testSizeAfterPopFront()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popFront();
  return v.getSize() == 1;
}

bool testSwap()
{
  topit::Vector< int > v;
  topit::Vector< int > zv;
  v.pushBack(1);
  zv.pushBack(2);
  v.swap(zv);
  return v[0] == 2 && zv[0] == 1;
}

bool testCapacity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v.getCapacity() == v.getSize() && v.getCapacity() == 2;
}

bool testCapacityAfterPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v.getCapacity() == 2;
}

bool testAssignmentOperator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > assign;
  assign = v;
  return assign.getSize() == 1 && assign[0] == 1;
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushFront(2);
  v.pushFront(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}


int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {{"Default vector is empty", testDefaultVector},
    {"Default vector is not empty", testVectorWithValue},
    {"Copy constructor works", testCopyConstructor},
    {"Elements must be equal", testElementAccess},
    {"Vector after pop back must be empty", testAfterPopEmpty},
    {"Vector after pop back must have size = 1", testSizeAfterPop},
    {"Vector after pop front must be empty", testAfterPopFrontEmpty},
    {"Vector after pop front must have size = 1", testSizeAfterPopFront},
    {"Vector must swap their values", testSwap},
    {"Vector must have cap == size", testCapacity},
    {"Capacity must not change after pop back", testCapacityAfterPopBack},
    {"Assignment operator works", testAssignmentOperator},
    {"Push front works", testPushFront}
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
