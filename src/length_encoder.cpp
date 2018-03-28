#include "length_encoder.hpp"

void length_encoder::visit_seq(statement_seq& seq)
{
  auto last_it = seq.begin();
  for(auto cur_it = seq.begin() + 1; cur_it != seq.end(); )
  {
    auto last = (*last_it)->kind();
    auto cur  = (*cur_it)->kind();

    const bool last_is_seq = last == token::Unknown || last == token::L_Square;

    if(compatible(cur, last) && !last_is_seq)
    {
      (*last_it)->inc_len((*cur_it)->len());
      cur_it = seq.erase(cur_it);
    }
    else
    {
      if(last_is_seq)
      {
        // recursive call to optimize in loops
	(*last_it)->optimize(*this);
      }
      ++last_it;
      ++cur_it;
    }
  }
}

bool length_encoder::compatible(token_kind lhs, token_kind rhs) noexcept
{
  return lhs == rhs
    || (lhs == token::Minus   && rhs == token::Plus)
    || (lhs == token::Plus    && rhs == token::Minus)
    || (lhs == token::L_Shift && rhs == token::R_Shift)
    || (lhs == token::R_Shift && rhs == token::L_Shift);
}
