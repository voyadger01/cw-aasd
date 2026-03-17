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
    ~Vector< T >();
    bool isEmpty() const noexcept;
    
  };
}

#endif
