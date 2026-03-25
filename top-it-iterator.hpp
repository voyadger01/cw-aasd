#ifndef TOP_IT_VECTOR_ITER_HPP
#define TOP_IT_VECTOR_ITER_HPP
#include <cstddef>
namespace topit {
  using signed_size_t = long long;
  template < class T > class Vector;
  template < class T > class LIter {
    friend class Vector< T >;
    friend LIter operator+(signed_size_t, const LIter &);
    Vector< T > *vec_;
    size_t idx_;
  public:
    LIter();
    LIter(Vector< T > *p, size_t idx);
    T &operator*() const;
    T *operator->() const;
    T &operator[](signed_size_t n) const;
    LIter &operator++();
    LIter operator++(int);
    LIter &operator--();
    LIter operator--(int);
    LIter &operator+=(signed_size_t n);
    LIter &operator-=(signed_size_t n);
    LIter operator+(signed_size_t n) const;
    LIter operator-(signed_size_t n) const;
    signed_size_t operator-(const LIter &other) const;
    bool operator==(const LIter &other) const;
    bool operator!=(const LIter &other) const;
    bool operator<(const LIter &other) const;
    bool operator>(const LIter &other) const;
    bool operator<=(const LIter &other) const;
    bool operator>=(const LIter &other) const;
  };
  template < class T > class LCIter {
    friend class Vector< T >;
    friend LCIter operator+(signed_size_t, const LCIter &);
    const Vector< T > *vec_;
    size_t idx_;
  public:
    LCIter();
    LCIter(const Vector< T > *p, size_t idx);
    LCIter(const LIter< T > &other);
    const T &operator*() const;
    const T *operator->() const;
    const T &operator[](signed_size_t n) const;
    LCIter &operator++();
    LCIter operator++(int);
    LCIter &operator--();
    LCIter operator--(int);
    LCIter &operator+=(signed_size_t n);
    LCIter &operator-=(signed_size_t n);
    LCIter operator+(signed_size_t n) const;
    LCIter operator-(signed_size_t n) const;
    signed_size_t operator-(const LCIter &other) const;
    bool operator==(const LCIter &other) const;
    bool operator!=(const LCIter &other) const;
    bool operator<(const LCIter &other) const;
    bool operator>(const LCIter &other) const;
    bool operator<=(const LCIter &other) const;
    bool operator>=(const LCIter &other) const;
  };
  template < class T > LIter< T > operator+(signed_size_t, const LIter< T > &);
  template < class T > LCIter< T > operator+(signed_size_t, const LCIter< T > &);
}
#endif