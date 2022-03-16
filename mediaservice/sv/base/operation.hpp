#ifndef __SV_BASE_OPERATION_HPP__
#define __SV_BASE_OPERATION_HPP__

#include <memory>
#include <string>

#include "sv/base/id_holder.hpp"
#include "sv/base/data.hpp"

namespace sv
{
namespace base
{

struct operation : public id_holder<operation>
{
  using ptr = std::shared_ptr<operation>;

  virtual std::string category() const = 0;
  virtual void execute(data::ptr _arg) = 0;
};

} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_OPERATION_HPP__