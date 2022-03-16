#include "sv/fileio/fileio.hpp"

namespace sv
{
namespace fileio
{

void file::execute(base::data::ptr _arg)
{
  std::dynamic_pointer_cast<use_file>(_arg)->execute(this);
}

std::string use_file::category() const
{
  return std::string("file-command");
}

namespace command
{

open_file::open_file(std::string const& _path)
  : m_path(_path)
{}
void open_file::execute(file::pointer_type _ctx)
{
  _ctx->m_file.open(m_path);
}
void read_file::execute(file::pointer_type _ctx)
{
  const size_t length = 1024;
  char buffer[length];

  _ctx->m_file.read(buffer, length);
}
void close_file::execute(file::pointer_type _ctx)
{
  _ctx->m_file.close();
}
void parse_ini::execute(file::pointer_type _ctx)
{

}

} // namespace sv::fileio::command
} // namespace sv::fileio
} // namespace sv