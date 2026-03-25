#ifndef TOP_IT_VECTOR_ITER_HPP
#define TOP_IT_VECTOR_ITER_HPP
#include <cstddef>
namespace topit
{
  using signed_size_t = long long;
  template < class T > class Vector;
  template < class T > class LIter
  {
    friend class Vector< T >;
    Vector< T > *vec_;
    size_t idx_;

  public:
    LIter();
    LIter(Vector< T > *p, size_t idx);
    T &operator*() const;
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
  template < class T > class LCIter
  {
    friend class Vector< T >;
    const Vector< T > *vec_;
    size_t idx_;

  public:
    LCIter();
    LCIter(const Vector< T > *p, size_t idx);
    LCIter(const LIter< T > &other);
    const T &operator*() const;
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

template < class T >
topit::LIter< T >::LIter():
  vec_(nullptr),
  idx_(0)
{}

template < class T >
topit::LIter< T >::LIter(topit::Vector< T > *p, size_t idx):
  vec_(p),
  idx_(idx)
{}

template < class T > T &topit::LIter< T >::operator*() const
{
  return vec_->data_[idx_];
}

template < class T > T &topit::LIter< T >::operator[](topit::signed_size_t n) const
{
  signed_size_t new_idx = static_cast< signed_size_t >(idx_) + n;
  return vec_->data_[static_cast< size_t >(new_idx)];
}

template < class T > topit::LIter< T > &topit::LIter< T >::operator++()
{
  ++idx_;
  return *this;
}

template < class T > topit::LIter< T > topit::LIter< T >::operator++(int)
{
  LIter tmp = *this;
  ++(*this);
  return tmp;
}

template < class T > topit::LIter< T > &topit::LIter< T >::operator--()
{
  --idx_;
  return *this;
}

template < class T > topit::LIter< T > topit::LIter< T >::operator--(int)
{
  LIter tmp = *this;
  --(*this);
  return tmp;
}

template < class T > topit::LIter< T > &topit::LIter< T >::operator+=(topit::signed_size_t n)
{
  idx_ = static_cast< size_t >(static_cast< signed_size_t >(idx_) + n);
  return *this;
}

template < class T > topit::LIter< T > &topit::LIter< T >::operator-=(topit::signed_size_t n)
{
  idx_ = static_cast< size_t >(static_cast< signed_size_t >(idx_) - n);
  return *this;
}

template < class T > topit::LIter< T > topit::LIter< T >::operator+(topit::signed_size_t n) const
{
  LIter tmp = *this;
  return tmp += n;
}

template < class T > topit::LIter< T > topit::LIter< T >::operator-(topit::signed_size_t n) const
{
  LIter tmp = *this;
  return tmp -= n;
}

template < class T > topit::signed_size_t topit::LIter< T >::operator-(const LIter &other) const
{
  return static_cast< signed_size_t >(idx_) - static_cast< signed_size_t >(other.idx_);
}

template < class T > bool topit::LIter< T >::operator==(const LIter &other) const
{
  return vec_ == other.vec_ && idx_ == other.idx_;
}

template < class T > bool topit::LIter< T >::operator!=(const LIter &other) const
{
  return !(*this == other);
}

template < class T > bool topit::LIter< T >::operator<(const LIter &other) const
{
  return idx_ < other.idx_;
}

template < class T > bool topit::LIter< T >::operator>(const LIter &other) const
{
  return other < *this;
}

template < class T > bool topit::LIter< T >::operator<=(const LIter &other) const
{
  return !(other < *this);
}

template < class T > bool topit::LIter< T >::operator>=(const LIter &other) const
{
  return !(*this < other);
}

template < class T >
topit::LCIter< T >::LCIter():
  vec_(nullptr),
  idx_(0)
{}

template < class T >
topit::LCIter< T >::LCIter(const topit::Vector< T > *p, size_t idx):
  vec_(p),
  idx_(idx)
{}

template < class T >
topit::LCIter< T >::LCIter(const topit::LIter< T > &other):
  vec_(other.vec_),
  idx_(other.idx_)
{}

template < class T > const T &topit::LCIter< T >::operator*() const
{
  return vec_->data_[idx_];
}

template < class T > const T &topit::LCIter< T >::operator[](topit::signed_size_t n) const
{
  signed_size_t new_idx = static_cast< signed_size_t >(idx_) + n;
  return vec_->data_[static_cast< size_t >(new_idx)];
}

template < class T > topit::LCIter< T > &topit::LCIter< T >::operator++()
{
  ++idx_;
  return *this;
}

template < class T > topit::LCIter< T > topit::LCIter< T >::operator++(int)
{
  LCIter tmp = *this;
  ++(*this);
  return tmp;
}

template < class T > topit::LCIter< T > &topit::LCIter< T >::operator--()
{
  --idx_;
  return *this;
}

template < class T > topit::LCIter< T > topit::LCIter< T >::operator--(int)
{
  LCIter tmp = *this;
  --(*this);
  return tmp;
}

template < class T > topit::LCIter< T > &topit::LCIter< T >::operator+=(topit::signed_size_t n)
{
  idx_ = static_cast< size_t >(static_cast< signed_size_t >(idx_) + n);
  return *this;
}

template < class T > topit::LCIter< T > &topit::LCIter< T >::operator-=(topit::signed_size_t n)
{
  idx_ = static_cast< size_t >(static_cast< signed_size_t >(idx_) - n);
  return *this;
}

template < class T > topit::LCIter< T > topit::LCIter< T >::operator+(topit::signed_size_t n) const
{
  LCIter tmp = *this;
  return tmp += n;
}

template < class T > topit::LCIter< T > topit::LCIter< T >::operator-(topit::signed_size_t n) const
{
  LCIter tmp = *this;
  return tmp -= n;
}

template < class T > topit::signed_size_t topit::LCIter< T >::operator-(const LCIter &other) const
{
  return static_cast< signed_size_t >(idx_) - static_cast< signed_size_t >(other.idx_);
}

template < class T > bool topit::LCIter< T >::operator==(const LCIter &other) const
{
  return vec_ == other.vec_ && idx_ == other.idx_;
}

template < class T > bool topit::LCIter< T >::operator!=(const LCIter &other) const
{
  return !(*this == other);
}

template < class T > bool topit::LCIter< T >::operator<(const LCIter &other) const
{
  return idx_ < other.idx_;
}

template < class T > bool topit::LCIter< T >::operator>(const LCIter &other) const
{
  return other < *this;
}

template < class T > bool topit::LCIter< T >::operator<=(const LCIter &other) const
{
  return !(other < *this);
}

template < class T > bool topit::LCIter< T >::operator>=(const LCIter &other) const
{
  return !(*this < other);
}

template < class T > topit::LIter< T > topit::operator+(topit::signed_size_t n, const LIter< T > &it)
{
  return it + n;
}

template < class T > topit::LCIter< T > topit::operator+(topit::signed_size_t n, const LCIter< T > &it)
{
  return it + n;
}
#endif
