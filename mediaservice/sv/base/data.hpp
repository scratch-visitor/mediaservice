#ifndef __SV_BASE_DATA_HPP__
#define __SV_BASE_DATA_HPP__

#include <memory>
#include <string>

#include "sv/base/id_holder.hpp"

namespace sv
{
namespace base
{

struct data : public id_holder<data>
{
  using ptr = std::shared_ptr<data>;

  virtual std::string category() const = 0;
};

} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_DATA_HPP__