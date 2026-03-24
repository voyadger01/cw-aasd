#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
// итератор для вектора
// 3 insert/erase (iterator)
// еттсы
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
    Vector< T >(Vector< T >&&) noexcept;
    Vector< T >(const Vector< T > &);
    Vector< T > &operator=(const Vector< T > &rhs);
    Vector< T > &operator=(Vector< T >&&) noexcept;
    ~Vector< T >();

    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    bool isEmpty() const noexcept;
    void pushBack(const T &val);
    void pushFront(const T &val);
    void popBack() noexcept;
    void popFront();
    void swap(Vector< T > &rhs) noexcept;

    // стр гарант + тест
    void insert(size_t i, const T& val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);


    template< class VecIt, class FwdIt>
    void insert(VecIt pos, FwdIt beg, FwdIt end);
  };
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
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

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
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

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& ret = cthis->at(id);
  return const_cast< T& >(ret);
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");  
}

template < class T > T &topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;
  const T& ret = (*cthis)(id);
  return const_cast< T >(ret);
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
  delete[] data_;
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

#endif
