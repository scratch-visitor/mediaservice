#ifndef __SV_DECODER_HPP__
#define __SV_DECODER_HPP__

#include "sv/base/processor.hpp"

namespace sv
{
namespace decoder
{

struct core : public base::processor
{
  std::string category() const override final;
};

struct h264 : public core
{
  virtual void execute(base::data::ptr _arg) override;
};

} // namespace sv::decoder
} // namespace sv

#endif // __SV_DECODER_HPP__