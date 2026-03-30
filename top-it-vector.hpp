#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>
#include "top-it-iterator.hpp"
// 1. чтобы не требовался конструктор по умолчанию
namespace topit
{
  template < class T > struct Vector
  {
  private:
    T *data_;
    size_t size_, capacity_;
    friend class LIter< T >;
    friend class LCIter< T >;
    explicit Vector< T >(size_t k);
    // без проверки на капасити тоже классная
    void pushBackImpl(const T &);
    // классная(::operator new и тд)
    void reserve(size_t pos, size_t count);

  public:
    Vector< T >();
    Vector< T >(Vector< T > &&) noexcept;
    Vector< T >(const Vector< T > &);
    explicit Vector< T >(std::initializer_list< T >) noexcept;
    Vector< T > &operator=(const Vector< T > &rhs);
    Vector< T > &operator=(Vector< T > &&) noexcept;
    ~Vector< T >();

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    T &at(size_t id);
    const T &at(size_t id) const;

    LIter< T > begin() noexcept;
    LIter< T > end() noexcept;
    LCIter< T > begin() const noexcept;
    LCIter< T > end() const noexcept;

    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    bool isEmpty() const noexcept;
    void pushBack(const T &val);
    void pushFront(const T &val);
    void popBack() noexcept;
    void popFront();
    void swap(Vector< T > &rhs) noexcept;
    void reserve(size_t cap);
    void shrinkToFit();

    void erase(size_t i);
    void erase(size_t beg, size_t end);
    LIter< T > erase(LIter< T > pos);
    LIter< T > erase(LIter< T > first, LIter< T > last);
    LIter< T > erase(LCIter< T > pos);
    void insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end);
    void insert(size_t i, const T &val);
    template < class VecIt, class FwdIt > void insert(VecIt pos, FwdIt beg, FwdIt end);
    LIter< T > insert(LIter< T > pos, const T &val);
    LIter< T > insert(LIter< T > pos, const Vector< T > &other);
    LIter< T > insert(size_t i, const Vector< T > &other);
    template < class IT > size_t pushBackRange(IT begin, size_t k);
  };
}

template < class T > void topit::Vector< T >::reserve(size_t cap)
{
  if (capacity_ >= cap) {
    return;
  }
  size_t i = 0;
  T *d = static_cast< T * >(::operator new(sizeof(T) * cap));
  try {
    for (; i < getSize(); i++) {
      new (d + 1) T(std::move(data_[i]));
    }
  } catch (...) {
    for (size_t j = 0; j < i; ++j) {
      (d + i)->~T();
    }
    throw;
  }
  delete[] data_;
  data_ = d;
  capacity_ = cap;
}

template < class T > template < class IT > size_t topit::Vector< T >::pushBackRange(IT begin, size_t k)
{}

template < class T >
topit::Vector< T >::Vector(std::initializer_list< T > il) noexcept:
  Vector< T >(il.size())
{
  size_t i = 0;
  for (auto &&v : il) {
    data_[i++] = std::move(v);
  }
}

template < class T >
topit::Vector< T >::Vector(Vector< T > &&rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template < class T > size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template < class T > topit::Vector< T > &topit::Vector< T >::operator=(Vector< T > &&rhs) noexcept
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template < class T > void topit::Vector< T >::pushFront(const T &val)
{
  if (size_ == capacity_) {
    size_t new_cap = capacity_ ? capacity_ * 2 : 1;
    T *new_data = new T[new_cap];
    for (size_t i = 0; i < size_; i++) {
      new_data[i + 1] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  } else {
    for (size_t i = size_; i > 0; i++) {
      data_[i] = data_[i - 1];
    }
  }
  data_[0] = val;
  ++size_;
}

template < class T > void topit::Vector< T >::swap(Vector< T > &rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.capacity_, capacity_);
  std::swap(rhs.size_, size_);
}

template < class T > topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > copy(rhs);
  swap(copy);
  return *this;
}

template < class T > const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T > T &topit::Vector< T >::at(size_t id)
{
  const Vector< T > *cthis = this;
  const T &ret = cthis->at(id);
  return const_cast< T & >(ret);
}

template < class T > const T &topit::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template < class T > T &topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T > *cthis = this;
  const T &ret = (*cthis)[id];
  return const_cast< T & >(ret);
}

template < class T > size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}
template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(static_cast< T * >(::operator new(sizeof(T) * k))),
  size_(0),
  capacity_(k)
{}

template < class T >
topit::Vector< T >::Vector(const Vector< T > &rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); i++) {
    data_[i] = rhs[i];
  }
}

template < class T > void topit::Vector< T >::pushBack(const T &val)
{
  if (size_ == capacity_) {
    size_t new_cap = capacity_ ? capacity_ * 2 : 1;
    T *new_data = new T[new_cap];
    for (size_t i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
  data_[size_++] = val;
}

template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template < class T > topit::Vector< T >::~Vector< T >()
{
  for (size_t i = 0; i < size_; ++i) {
    data_[i].~T();
  }
  ::operator delete(data_);
}

template < class T > bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T > void topit::Vector< T >::popBack() noexcept
{
  assert(size_ > 0);
  data_[--size_].~T();
}

template < class T > void topit::Vector< T >::popFront()
{
  assert(size_ > 0);
  Vector< T > copy(getSize() - 1);
  for (size_t i = 1; i < getSize(); i++) {
    copy[i - 1] = (*this)[i];
  }
  swap(copy);
}

template < class T > void topit::Vector< T >::erase(size_t beg, size_t end)
{
  assert(beg <= end && end <= size_);
  if (beg == end) {
    return;
  }
  Vector< T > newVec(size_ - (end - beg));
  for (size_t i = 0; i < beg; ++i) {
    newVec.data_[i] = data_[i];
  }
  for (size_t i = end; i < size_; ++i) {
    newVec.data_[i - (end - beg)] = data_[i];
  }
  swap(newVec);
}

template < class T > void topit::Vector< T >::erase(size_t i)
{
  erase(i, i + 1);
}

template < class T > void topit::Vector< T >::insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end)
{
  assert(i <= size_ && beg <= end && end <= rhs.getSize());
  size_t count = end - beg;
  Vector< T > newVec(size_ + count);
  for (size_t k = 0; k < i; ++k) {
    newVec.data_[k] = data_[k];
  }
  for (size_t k = 0; k < count; ++k) {
    newVec.data_[i + k] = rhs.at(beg + k);
  }
  for (size_t k = i; k < size_; ++k) {
    newVec.data_[count + k] = data_[k];
  }
  swap(newVec);
}

template < class T > void topit::Vector< T >::insert(size_t i, const T &val)
{
  Vector< T > tmp;
  tmp.pushBack(val);
  insert(i, tmp, 0, 1);
}

template < class T > topit::LIter< T > topit::Vector< T >::begin() noexcept
{
  return LIter< T >(this, 0);
}

template < class T > topit::LIter< T > topit::Vector< T >::end() noexcept
{
  return LIter< T >(this, size_);
}

template < class T > topit::LCIter< T > topit::Vector< T >::begin() const noexcept
{
  return LCIter< T >(this, 0);
}

template < class T > topit::LCIter< T > topit::Vector< T >::end() const noexcept
{
  return LCIter< T >(this, size_);
}

template < class T >
template < class VecIt, class FwdIt >
void topit::Vector< T >::insert(VecIt pos, FwdIt beg, FwdIt end)
{
  Vector< T > tmp;
  for (FwdIt it = beg; it != end; ++it) {
    tmp.pushBack(*it);
  }
  insert(pos.idx_, tmp, 0, tmp.getSize());
}

template < class T > topit::LIter< T > topit::Vector< T >::insert(LIter< T > pos, const T &val)
{
  size_t idx = pos.idx_;
  insert(idx, val);
  return LIter< T >(this, idx);
}

template < class T > topit::LIter< T > topit::Vector< T >::insert(size_t i, const Vector< T > &other)
{
  insert(i, other, 0, other.getSize());
  return LIter< T >(this, i);
}

template < class T > topit::LIter< T > topit::Vector< T >::insert(LIter< T > pos, const Vector< T > &other)
{
  size_t idx = pos.idx_;
  insert(idx, other, 0, other.getSize());
  return LIter< T >(this, idx);
}

template < class T > topit::LIter< T > topit::Vector< T >::erase(LIter< T > pos)
{
  size_t idx = pos.idx_;
  erase(idx);
  return LIter< T >(this, idx);
}

template < class T > topit::LIter< T > topit::Vector< T >::erase(LIter< T > first, LIter< T > last)
{
  size_t beg = first.idx_;
  erase(beg, last.idx_);
  return LIter< T >(this, beg);
}

template < class T > topit::LIter< T > topit::Vector< T >::erase(LCIter< T > pos)
{
  size_t idx = pos.idx_;
  erase(idx);
  return LIter< T >(this, idx);
}

template < class T > void topit::Vector< T >::pushBackImpl(const T &val)
{
  new (data_ + size_) T(val);
  ++size_;
}

template < class T > void topit::Vector< T >::reserve(size_t pos, size_t count)
{
  assert(pos <= size_);
  if (count == 0) {
    return;
  }
  if (size_ + count > capacity_) {
    size_t new_cap = capacity_ ? capacity_ * 2 : 1;
    while (new_cap < size_ + count) {
      new_cap *= 2;
    }
    T *new_data = static_cast< T * >(::operator new(sizeof(T) * new_cap));
    size_t constructed = 0;
    try {
      for (; constructed < pos; ++constructed) {
        new (new_data + constructed) T(std::move(data_[constructed]));
      }
      for (size_t i = pos; i < size_; ++i, ++constructed) {
        new (new_data + constructed + count) T(std::move(data_[i]));
      }
    } catch (...) {
      for (size_t i = 0; i < constructed; ++i) {
        new_data[i].~T();
      }
      ::operator delete(new_data);
      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      data_[i].~T();
    }
    ::operator delete(data_);

    data_ = new_data;
    capacity_ = new_cap;
  } else {
    for (size_t i = size_; i > pos; --i) {
      new (data_ + i + count - 1) T(std::move(data_[i - 1]));
      data_[i - 1].~T();
    }
  }
  size_ += count;
}

#endif
