#pragma once

#include <array>
#include <iterator>
#include <stdexcept>

// reference https://accu.org/journals/overload/10/50/goodliffe_389/
//      part 2: https://accu.org/journals/overload/10/51/goodliffe_383/
// and https://github.com/vinitjames/circularbuffer/blob/master/circular_buffer.h
template<typename T, int SIZE>
class CircularBuffer
{
public:
  // STL definitions
  typedef CircularBuffer<T, SIZE> self_type;

  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  template<typename BUFFER, typename ELEM_TYPE = typename BUFFER::value_type>
  class _iterator
  {
  public:
    // STL definitions
    typedef _iterator<BUFFER, ELEM_TYPE> self_type;
    typedef BUFFER buffer_type;
    typedef ELEM_TYPE value_type;
    typedef ELEM_TYPE *pointer;
    typedef const ELEM_TYPE *const_pointer;
    typedef ELEM_TYPE &reference;
    typedef const T &const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    _iterator(buffer_type *buffer, size_t startPos)
      : _buffer(buffer), _pos(startPos)
    {}

    _iterator(const self_type &other)
      : _buffer(other._buffer), _pos(other._pos)
    {}

    _iterator &operator=(const self_type &other)
    {
      _buffer = other._buffer;
      _pos = other._pos;
      return *this;
    }

    reference operator*() { return (*_buffer)[_pos]; }
    const_reference operator*() const { return (*_buffer)[_pos]; }

    pointer operator->() { return &(operator*()); }
    const_pointer operator->() const { return &(operator*()); }

    self_type &operator++()
    {
      ++_pos;
      return *this;
    }

    self_type operator++(int)
    {
      self_type temp(*this);
      ++(*this);
      return temp;
    }

    self_type operator+(difference_type n)
    {
      self_type temp(*this);
      temp += n;
      return temp;
    }

    self_type &operator+=(difference_type n)
    {
      _pos += n;
      return *this;
    }

    self_type &operator--()
    {
      --_pos;
      return *this;
    }

    self_type operator--(int)
    {
      self_type temp(*this);
      --(*this);
      return temp;
    }

    self_type operator-(difference_type n)
    {
      self_type temp(*this);
      temp -= n;
      return temp;
    }

    self_type &operator-=(difference_type n)
    {
      _pos -= n;
      return *this;
    }

    bool operator==(const self_type &other) const
    {
      if (_CanCompare(other)) {
        return _pos == other._pos;
      }
      return false;
    }

    bool operator!=(const self_type &other) const { return !(*this == other); }

    bool operator<(const self_type &other) const
    {
      if (_CanCompare(other)) {
        return _pos < other._pos;
      }
      return false;
    }

    bool operator>(const self_type &other) const { return other < *this; }
    bool operator<=(const self_type &other) const { return !(*this > other); }
    bool operator>=(const self_type &other) const { return !(*this < other); }

  private:
    buffer_type *_buffer;
    size_t _pos;

    bool _CanCompare(const self_type &other) const
    {
      return (_buffer == other._buffer);
    }
  };

  typedef _iterator<self_type> iterator;
  typedef _iterator<const self_type, const value_type> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  iterator begin() { return iterator(this, 0); }
  const_iterator begin() const { return const_iterator(this, 0); }
  const_iterator cbegin() const { return const_iterator(this, 0); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }

  iterator end() { return iterator(this, _contentsSize); }
  const_iterator end() const { return const_iterator(this, _contentsSize); }
  const_iterator cend() const { return const_iterator(this, _contentsSize); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
  const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

  CircularBuffer()
    : _head(0), _tail(0), _contentsSize(0)
  {}

  CircularBuffer(const CircularBuffer &other)
    : _buffer(other._buffer), _head(other._head), _tail(other._tail), _contentsSize(other._contentsSize)
  {}

  template<typename InputIterator>
  CircularBuffer(InputIterator from, InputIterator to)
    : _head(0), _tail(0), _contentsSize(0)
  {
    while (from != to) {
      PushBack(*from);
      ++from;
    }
  }

  CircularBuffer &operator=(const CircularBuffer &other)
  {
    Clear();
    _buffer = other._buffer;
    _head = other._head;
    _tail = other._tail;
    _contentsSize = other._contentsSize;
    return *this;
  }

  ~CircularBuffer() = default;

  size_t Size() const noexcept
  {
    return _contentsSize;
  }

  size_t Capacity() const noexcept
  {
    return SIZE;
  }

  static size_t MaxSize() noexcept
  {
    return size_t(-1) / sizeof(value_type);
  }

  bool Empty() const noexcept
  {
    return _contentsSize == 0;
  }

  reference Front() noexcept
  {
    return _buffer[_head];
  }
  const_reference Front() const noexcept
  {
    return _buffer[_head];
  }

  reference Back() noexcept
  {
    return _buffer[_tail - 1];
  }
  const_reference Back() const noexcept
  {
    return _buffer[_tail - 1];
  }

  void Clear() noexcept
  {
    _head = _tail = _contentsSize = 0;
  }

  // if the buffer is full, the longest-lived item is overwritten
  void PushBack(const value_type &item) noexcept
  {
    _buffer[_tail] = item;
    if (_contentsSize == SIZE) {
      _IncrementHead();
    }
    _IncrementTail();
  }

  void PopFront() noexcept
  {
    // precondition: _contentsSize > 0
    _IncrementHead();
  }

  reference At(size_t index) { return _buffer[_SafeIndexFromHead(index)]; }
  const_reference At(size_t index) const { return _buffer[_SafeIndexFromHead(index)]; }

  reference operator[](size_t index) noexcept { return _buffer[_IndexFromHead(index)]; }
  const_reference operator[](size_t index) const noexcept { return _buffer[_IndexFromHead(index)]; }

private:
  std::array<value_type, SIZE> _buffer;
  size_t _head;
  size_t _tail;
  size_t _contentsSize;
  // c = content
  // t = tail (IS NOT content)
  //      - though it could point to content due to overlap caused by the circular nature
  // h = head (IS content)
  // e = empty
  // [ccccteeeeehccc]

  void _IncrementTail() noexcept
  {
    ++_tail;
    ++_contentsSize;
    if (_tail == SIZE) {
      _tail = 0;
    }
  }

  void _IncrementHead() noexcept
  {
    // precondition: !empty()
    ++_head;
    --_contentsSize;
    if (_head == SIZE) {
      _head = 0;
    }
  }

  size_t _IndexFromHead(size_t index) const noexcept
  {
    return (_head + index) % SIZE;
  }

  size_t _SafeIndexFromHead(size_t index) const
  {
    size_t actualIndex = _IndexFromHead(index);
    if (actualIndex >= _tail) {
      throw std::out_of_range();
    }
    return actualIndex;
  }
};