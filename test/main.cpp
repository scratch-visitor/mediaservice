#include <iostream>
#include <string>
#include <memory>
#include <deque>
#include <mutex>
#include <functional>
#include <unordered_map>

namespace err
{
enum : int
{
  none = 0,
  not_implemented_yet,
  abnormal_argument,
};
}

template<class T>
struct operation_base
{
  using ptr = std::shared_ptr<operation_base<T>>;
  using return_type = T;

  virtual return_type execute() = 0;
  virtual std::string name() const = 0;
};

using basic_operation = operation_base<int>;

template<class T>
struct processor
{
  using operation = operation_base<T>;

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void wait() = 0;
  virtual void post(typename operation::ptr _obj) = 0;
};

template<class R, class T = operation_base<R>, class Cont = std::deque<std::shared_ptr<T>>>
struct basic_processor : processor<R>
{
  using operation_type = T;
  using operation_ptr = std::shared_ptr<operation_type>;
  using container = Cont;

  basic_processor()
  {
  }
  virtual ~basic_processor()
  {
  }

  virtual void start() override
  {
  }
  virtual void stop() override
  {
  }
  virtual void wait() override
  {
  }
  virtual void post(operation_ptr _op) override
  {
  }
private:
  std::mutex m_mu;
  container m_depot;
};

struct demuxer : basic_operation
{
  virtual int execute() override
  {
    return err::not_implemented_yet;
  }
  virtual std::string name() const override
  {
    return std::string("demuxer");
  }
  static int generate_id()
  {
    static int s_id = 0;
    return s_id++;
  }
};

using demuxer_ctor_t = std::function<demuxer::ptr()>;
struct demuxer_maker
{
  static demuxer_maker& get()
  {
    static demuxer_maker instance;
    return instance;
  }
  void register_creator(int _type, demuxer_ctor_t _ctor)
  {
    m_depot[_type] = _ctor;
  }
  demuxer::ptr create(int _type)
  {
    auto ctor = m_depot.find(_type);
    if (ctor == m_depot.end())
    {
      return nullptr;
    }

    return ctor->second();
  }

private:
  demuxer_maker() {}
private:
  std::unordered_map<int, demuxer_ctor_t> m_depot;
};
template<class T>
int register_demuxer()
{
  demuxer_maker::get().register_creator(T::id, T::create);
  return 1;
}
#define PREPARE_REG(cls) public:\
static const int id;\
static const int registered

#define DEFINITION_REG(cls) const int cls::id = demuxer::generate_id();\
const int cls::registered = register_demuxer<cls>()

struct rtsp : demuxer
{
  static demuxer::ptr create()
  {
    return std::dynamic_pointer_cast<demuxer>(std::make_shared<rtsp>());
  }
  virtual std::string name() const override final
  {
    return std::string("rtsp");
  }
  rtsp() {}

  PREPARE_REG(rtsp);
};
DEFINITION_REG(rtsp);

struct hls : demuxer
{
  static demuxer::ptr create()
  {
    return std::dynamic_pointer_cast<demuxer>(std::make_shared<hls>());
  }
  virtual std::string name() const override final
  {
    return std::string("hls");
  }
  hls() {}

  PREPARE_REG(hls);
};
DEFINITION_REG(hls);

struct webrtc : demuxer
{
  static demuxer::ptr create()
  {
    return std::dynamic_pointer_cast<demuxer>(std::make_shared<webrtc>());
  }
  virtual std::string name() const override final
  {
    return std::string("webrtc");
  }
  webrtc() {}

  PREPARE_REG(webrtc);
};
DEFINITION_REG(webrtc);

struct decoder : basic_operation
{
  virtual int execute() override
  {
    return err::not_implemented_yet;
  }
};

struct h264 : decoder {};
struct h265 : decoder {};
struct av1 : decoder {};

int main()
{
  demuxer::ptr demuxer = nullptr;
  demuxer = demuxer_maker::get().create(rtsp::id);
  std::cout << "demuxer: " << demuxer->name() << std::endl;
  demuxer = demuxer_maker::get().create(hls::id);
  std::cout << "demuxer: " << demuxer->name() << std::endl;
  demuxer = demuxer_maker::get().create(webrtc::id);
  std::cout << "demuxer: " << demuxer->name() << std::endl;

  return 0;
}