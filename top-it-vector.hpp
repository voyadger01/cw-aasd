#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <utility>
namespace topit
{
  template < class T > struct Vector
  {
  private:
    T *data_;
    size_t size_, capacity_;

    explicit Vector< T >(size_t k);

  public:
    Vector< T >();
    Vector< T >(const Vector< T > &);
    Vector< T > &operator=(const Vector< T > &rhs);
    ~Vector< T >();
    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    bool isEmpty() const noexcept;
    void pushBack(const T &val);
    void pushFront(const T &val);
    void pop_back();
    void swap(Vector< T > &rhs) noexcept;
  };
}

template < class T > void topit::Vector< T >::pushFront(const T &val)
{
  Vector< T > copy(getSize() + 1);
  copy[0] = val;
  for (size_t i = 0; i < getSize(); i++) {
    copy[i + 1] = (*this)[i];
  }
  swap(copy);
}

template < class T > void topit::Vector< T >::swap(Vector< T > &rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.capacity_, capacity_);
  std::swap(rhs.size_, size_);
}

template < class T > topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  Vector< T > copy(rhs);
  swap(copy);
  return *this;
}

template < class T > const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T > T &topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T > size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}
template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(new T[k]),
  size_(k),
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
  Vector< T > copy(getSize() + 1);
  copy[getSize()] = val;
  for (size_t i = 0; i < getSize(); i++) {
    copy[i] = (*this)[i];
  }
  swap(copy);
}

template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template < class T > topit::Vector< T >::~Vector< T >()
{
  delete[] data_;
}

template < class T > bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}
#endif
