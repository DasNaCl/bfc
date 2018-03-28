#include "bf_machine.hpp"

bf_machine::bf_machine(std::size_t size)
  : mem(), position(0U)
{
  mem.resize(size);
}
