#include "top-it-iterator.hpp"
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
  const topit::Vector< int > &rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testElementOutOfBoundCheckedAccess()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &) {
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
  const topit::Vector< int > &rv = v;
  try {
    rv.at(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementInboundConstCheckedAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > &rv = v;
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

bool testMoveConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > moved(std::move(v));
  return moved.getSize() == 2 && moved[0] == 1 && moved[1] == 2;
}
bool testMoveAssignment()
{
  topit::Vector< int > v, dest;
  v.pushBack(1);
  dest = std::move(v);
  return dest[0] == 1;
}
bool testSelfAssignment()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v = v;
  return v[0] == 1 && v.getSize() == 1;
}
bool testNonConstModification()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v[0] = 2;
  return v[0] == 2;
}
bool testInsertSingle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}
bool testInsertRange()
{
  topit::Vector< int > v, src;
  v.pushBack(1);
  v.pushBack(4);
  src.pushBack(2);
  src.pushBack(3);
  v.insert(1, src, 0, 2);
  return v.getSize() == 4 && v[1] == 2 && v[2] == 3;
}
bool testEraseSingle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}
bool testEraseRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.erase(1, 3);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 4;
}
bool testInsertIteratorSingle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(v.begin(), 2);
  return v.getSize() == 3 && v[0] == 2 && v[1] == 1 && v[2] == 3;
}
bool testInsertIteratorVector()
{
  topit::Vector< int > v, src;
  v.pushBack(1);
  v.pushBack(4);
  src.pushBack(2);
  src.pushBack(3);
  v.insert(v.begin() + 1, src);
  return v.getSize() == 4 && v[1] == 2 && v[2] == 3;
}
bool testEraseIteratorSingle()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(v.begin() + 1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}
bool testEraseIteratorRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.erase(v.begin() + 1, v.begin() + 3);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 4;
}
bool testEraseConstIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  const topit::Vector< int > &cv = v;
  v.erase(cv.begin() + 1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}
bool testIteratorTraversal()
{
  topit::Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);
  int sum = 0;
  for (topit::LIter< int > it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  return sum == 60;
}
bool testTemplateInsertExternalIterators()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(4);
  int arr[] = {2, 3};
  v.insert(v.begin() + 1, arr, arr + 2);
  return v.getSize() == 4 && v[1] == 2 && v[2] == 3;
}

bool testInsertIndexVector()
{
  topit::Vector< int > v, src;
  v.pushBack(1);
  v.pushBack(5);
  src.pushBack(2);
  src.pushBack(3);
  src.pushBack(4);
  v.insert(1, src);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5;
}

bool testInitializerListConstruct()
{
  topit::Vector< int > v{1, 2};
  return v.getSize() == 2;
}

bool testPushBackRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  int arr[] = {2, 3, 4};
  v.pushBackRange(arr, 3);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool testShrinkToFit()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.popBack();
  v.popBack();
  v.shrinkToFit();
  return v.getSize() == 2 && v.getCapacity() == 2 && v[0] == 1 && v[1] == 2;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {
    {"Default vector is empty", testDefaultVector},
    {"Default vector is not empty", testVectorWithValue},
    {"Copy constructor works", testCopyConstructor},
    {"Elements must be equal", testElementAccess},
    {"Const elements must be equal", testElementConstAccess},
    {"Out of bound at throws", testElementOutOfBoundCheckedAccess},
    {"In bound at works", testElementInboundCheckedAccess},
    {"Const out of bound at throws", testElementOutOfBoundConstCheckedAccess},
    {"Const in bound at works", testElementInboundConstCheckedAccess},
    {"Vector after pop back must be empty", testAfterPopEmpty},
    {"Vector after pop back must have size = 1", testSizeAfterPop},
    {"Vector after pop front must be empty", testAfterPopFrontEmpty},
    {"Vector after pop front must have size = 1", testSizeAfterPopFront},
    {"Vector must swap their values", testSwap},
    {"Vector must have cap == size", testCapacity},
    {"Capacity must not change after pop back", testCapacityAfterPopBack},
    {"Assignment operator works", testAssignmentOperator},
    {"Push front works", testPushFront},
    {"Move constructor works", testMoveConstructor},
    {"Move assignment works", testMoveAssignment},
    {"Self assignment works", testSelfAssignment},
    {"Non-const modification works", testNonConstModification},
    {"Insert single works", testInsertSingle},
    {"Insert range works", testInsertRange},
    {"Erase single works", testEraseSingle},
    {"Erase range works", testEraseRange},
    {"Insert via iterator + single value", testInsertIteratorSingle},
    {"Insert via iterator + Vector", testInsertIteratorVector},
    {"Erase via iterator (single)", testEraseIteratorSingle},
    {"Erase via iterator range", testEraseIteratorRange},
    {"Erase via const iterator", testEraseConstIterator},
    {"Iterator traversal with begin/end", testIteratorTraversal},
    {"Insert by index + Vector", testInsertIndexVector},
    {"Template insert with external iterators", testTemplateInsertExternalIterators},
    {"Initializer list constructs properly", testInitializerListConstruct},
    {"PushBackRange works", testPushBackRange},
    {"ShrinkToFit works", testShrinkToFit}
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
