#pragma once

#include <vector>

struct bf_machine
{
  /*implicit*/ bf_machine(std::size_t size = 30000U);
  
  std::vector<unsigned char> mem;
  std::size_t position;
};
