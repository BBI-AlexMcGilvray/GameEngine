#include <cstdint>

namespace Core {
namespace {
  constexpr uint32_t INVALID_ID = 0;
  static uint32_t next_id = 1;

  template <typename ID_TYPE>
  ID_TYPE GetNewId()
  {
      static ID_TYPE current_ID = 0;
      return ++current_ID;
  }
}// namespace

template<typename T, typename ID_TYPE = size_t>
struct instanceId
{
  constexpr instanceId()
  : _id(GetNewId<ID_TYPE>())
  {}

  constexpr instanceId(const instanceId &rhs)
    : _id(rhs._id)
  {}

  constexpr instanceId &operator=(const instanceId &rhs)
  {
    _id = rhs._id;
    return *this;
  }

  constexpr bool operator==(const runtimeId &other)
  {
    return _id == other._id;
  }

  constexpr bool operator!=(const runtimeId &other)
  {
    return _id == other._id;
  }

private:
  ID_TYPE _id;
};
}// namespace Core