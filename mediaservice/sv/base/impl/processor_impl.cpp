#include "sv/base/impl/processor_impl.hpp"

namespace sv
{
namespace base
{
namespace impl
{

processor_impl::processor_impl(operation* _parent)
  : m_parent(_parent)
  , m_need_to_stop(false)
{}
processor_impl::~processor_impl()
{}

void processor_impl::start()
{
  m_worker = std::thread(&processor_impl::_loop, this);
}
void processor_impl::stop()
{
  {
    std::lock_guard<std::mutex> locker(m_mu);
    m_need_to_stop = true;
  }
  m_cv.notify_all();

  if (m_worker.joinable())
    m_worker.join();
}
void processor_impl::wait()
{
  {
    std::lock_guard<std::mutex> locker(m_mu);
    m_need_to_stop = true;
  }
  m_cv.notify_all();

  _process(true);

  if (m_worker.joinable())
    m_worker.join();
}

void processor_impl::push(data::ptr _input)
{
  std::lock_guard<std::mutex> locker(m_mu);
  if (m_need_to_stop) return;

  m_queue.push_back(_input);
}

void processor_impl::_loop()
{
  while (true)
  {
    std::unique_lock<std::mutex> locker(m_mu);
    if (m_cv.wait_for(locker, std::chrono::microseconds(1),
                      [=]() { return m_need_to_stop; }))
    {
      break;
    }
    locker.unlock();

    _process(false);
  }
}
void processor_impl::_process(bool _all)
{
  do
  {
    data::ptr item = nullptr;
    {
      std::lock_guard<std::mutex> locker(m_mu);
      if (m_queue.empty()) break;

      item = m_queue.front();
      m_queue.pop_front();
    }

    m_parent->execute(item);

  } while (_all);
}

} // namespace sv::base::impl
} // namespace sv::base
} // namespace sv