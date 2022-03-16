#include "sv/base/processor.hpp"
#include "sv/base/impl/processor_impl.hpp"

namespace sv
{
namespace base
{

processor::processor()
  : impl(new impl::processor_impl(this))
{
  impl->start();
}
processor::~processor()
{
  impl->wait();
}
void processor::push(data::ptr _arg)
{
  impl->push(_arg);
}

} // namespace sv::base
} // namespace sv