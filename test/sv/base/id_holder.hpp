#ifndef __SV_BASE_ID_HOLDER_HPP__
#define __SV_BASE_ID_HOLDER_HPP__

#include <cstdint>

namespace sv
{
namespace base
{

template<class T>
struct id_holder
{
  using id_type = std::uint64_t;

  id_type id() const { return m_id; }

protected:
  id_holder() : m_id(++s_id) {}

private:
  id_type m_id;
  static id_type s_id;
};
template<class T>
typename id_holder<T>::id_type id_holder<T>::s_id = 0ULL;


} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_ID_HOLDER_HPP__