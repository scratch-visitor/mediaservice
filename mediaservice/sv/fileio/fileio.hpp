#ifndef __SV_FILEIO_HPP__
#define __SV_FILEIO_HPP__

#include "sv/base/processor.hpp"
#include "sv/base/data.hpp"

#include <fstream>

namespace sv
{
namespace fileio
{

struct core : public base::processor
{
  std::string category() const override final;
};

struct file : public core
{
  using pointer_type = file*;

  virtual void execute(base::data::ptr _arg) override;

  std::fstream m_file;
};

struct use_file : public base::data
{
  virtual void execute(file::pointer_type _ctx) = 0;
  virtual std::string category() const override;
};

namespace command
{

struct open_file : public use_file
{
  open_file(std::string const& _path);

  void execute(file::pointer_type _ctx) override final;

private:
  std::string m_path;
};

struct read_file : public use_file
{
  void execute(file::pointer_type _ctx) override final;
};

struct parse_ini : public use_file
{
  parse_ini() {}
  void execute(file::pointer_type _ctx) override final;
};

struct close_file : public use_file
{
  void execute(file::pointer_type _ctx) override final;
};
} // namespace sv::fileio::command

} // namespace sv::fileio
} // namespace sv

#endif // __SV_FILEIO_HPP__