#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
  private:
    T* data_;
    size_t size_, capacity_;
  public:
    Vector< T >();
    Vector< T >(const Vector< T >&) = delete;
    Vector< T >& operator=(const Vector< T >&) = delete;
    ~Vector< T >();

    bool isEmpty() const noexcept;
  };
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector<T>()
{
  delete [] data_;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return false;
}
#endif
