#ifndef __SV_BASE_PROCESSOR_HPP__
#define __SV_BASE_PROCESSOR_HPP__

#include "sv/base/operation.hpp"
#include "sv/base/data.hpp"

#include <memory>

namespace sv
{
namespace base
{
namespace impl
{
struct processor_impl; // forward
} // namespace sv::base::impl

struct processor : public operation
{
  void push(data::ptr _arg);

  virtual ~processor();

protected:
  processor();

private:
  std::unique_ptr<impl::processor_impl> impl;
};

} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_PROCESSOR_HPP__