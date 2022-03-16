#ifndef __SV_DEMUXER_HPP__
#define __SV_DEMUXER_HPP__

#include "sv/base/processor.hpp"
#include "sv/base/data.hpp"

namespace sv
{
namespace demuxer
{

struct core : public base::processor
{
  std::string category() const override final;
};

struct rtsp : public core
{
  virtual void execute(base::data::ptr _arg) override;
};

struct open_rtsp : public base::data
{
};

struct close_rtsp : public base::data
{
};

} // namespace sv::demuxer
} // namespace sv::demuxer

#endif // __SV_DEMUXER_HPP__