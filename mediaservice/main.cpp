#include <iostream>
#include <string>
#include <memory>
#include <deque>
#include <mutex>
#include <functional>
#include <unordered_map>

#include "sv/sv.hpp"

int main()
{
  sv::demuxer::rtsp rev;

  std::cout << rev.category() << std::endl;

  sv::fileio::file fp;

  std::cout << fp.category() << std::endl;

  auto parser = std::make_shared<sv::fileio::command::parse_ini>();

  fp.execute(parser);

  return 0;
}