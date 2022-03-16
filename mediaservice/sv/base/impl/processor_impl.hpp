#ifndef __SV_BASE_IMPL_PROCESSOR_IMPL_HPP__
#define __SV_BASE_IMPL_PROCESSOR_IMPL_HPP__

#include "sv/base/data.hpp"
#include "sv/base/operation.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

namespace sv
{
namespace base
{
namespace impl
{

struct processor_impl
{
  processor_impl(operation* _parent);
  ~processor_impl();

  void start();
  void stop();
  void wait();

  void push(data::ptr _input);

private:
  void _loop();
  void _process(bool _all);

private:
  std::thread m_worker;
  std::mutex m_mu;
  std::condition_variable m_cv;
  bool m_need_to_stop;

  std::list<data::ptr> m_queue;

  operation* m_parent;
};

} // namespace sv::base::impl
} // namespace sv::base
} // namespace sv

#endif // __SV_BASE_IMPL_PROCESSOR_IMPL_HPP__