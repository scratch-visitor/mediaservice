#ifndef __SV_BASE_OPERATION_HPP__
#define __SV_BASE_OPERATION_HPP__

#include <memory>
#include <string>

#include "sv/base/id_holder.hpp"

namespace sv
{
namespace base
{

template<class T>
struct value_holder
{
  using value_type = T;
};
template<class T>
struct value_holder<const T>
{
  using value_type = T;
};
template<class T>
struct value_holder<T&>
{
  using value_type = T;
};
template<>
struct value_holder<char*>
{
  using value_type = std::string;
};
template<>
struct value_holder<wchar_t*>
{
  using value_type = std::wstring;
};

struct return_value
{
  return_value()
  {
  }
  template<class T>
  return_value(T const& v)
  {
    typename value_holder<T>::value_type value = v;
  }
};

struct operation : public id_holder<operation>
{
  virtual return_value execute() = 0;
};

template<class T>
struct operation_base : public operation
{
  using ptr = std::shared_ptr<operation_base<T>>;
  using return_type = T;

  virtual return_value execute() override final
  {
    return return_value(do_execute());
  }
  virtual std::string name() const = 0;

protected:
  virtual return_type do_execute() = 0;
};

using basic_operation = operation_base<int>;

} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_OPERATION_HPP__