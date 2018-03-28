#include "statements.hpp"

#include <iostream>
#include <cassert>

statement::statement(token_kind tok) noexcept
  : tok(tok), length(1U)
{  }

statement::~statement() noexcept
{  }

void statement::optimize(statement_optimizer& visitor)
{
  visitor.visit_statement(*this);
}

token_kind statement::kind() const
{
  return tok;
}

int statement::len() const
{
  return length;
}

void statement::inc_len(int l)
{
  length += l;
}


statement_seq::statement_seq()
  : statement(token::Unknown), statements()
{  }

statement_seq::~statement_seq() noexcept
{  }

void statement_seq::interpret(bf_machine& m) noexcept
{
  for(auto& p : statements)
    p->interpret(m);
}

void statement_seq::print_c(std::ostream& os)
{
  for(auto& p : statements)
  {
    p->print_c(os);
    os << "\n";
  }
}

void statement_seq::optimize(statement_optimizer& visitor)
{
  statement::optimize(visitor);

  visitor.visit_seq(*this);
}

void statement_seq::add(statement::ptr&& ptr)
{
  statements.emplace_back(std::move(ptr));
}

statement::ptr& statement_seq::get_last()
{
  return statements.back();
}

statement_seq::iterator statement_seq::begin()
{
  return statements.begin();
}

statement_seq::iterator statement_seq::end()
{
  return statements.end();
}

statement_seq::iterator statement_seq::erase(statement_seq::iterator it)
{
  return statements.erase(it);
}


arithmetic::arithmetic(token_kind tok) noexcept
  : statement(tok)
{
  assert(tok == token::Plus    || tok == token::Minus
      || tok == token::L_Shift || tok == token::R_Shift);

  if(tok == token::Minus || tok == token::L_Shift)
    length *= -1;
}

void arithmetic::interpret(bf_machine& m) noexcept
{
  switch(tok)
  {
  default:
    assert(false); // Hard logic error

  case token::Plus:    
  case token::Minus:   { m.mem[m.position] += length; } break;

  case token::R_Shift: 
  case token::L_Shift: { m.position += length; } break;
  }
}

void arithmetic::print_c(std::ostream& os)
{
  switch(tok)
  {
  default:
    assert(false); // Hard logic error

  case token::Plus:    
  case token::Minus:   { os << "*ptr += " << length << ";"; } break;

  case token::R_Shift: 
  case token::L_Shift: { os << "ptr += " << length << ";"; } break;
  }
}

void arithmetic::optimize(statement_optimizer& visitor)
{
  statement::optimize(visitor);

  visitor.visit_arithmetic(*this);
}

void arithmetic::inc_len(int l)
{
  length += (tok == token::Minus || tok == token::L_Shift ? -l : l);
}


serialization::serialization(token_kind tok) noexcept
  : statement(tok)
{
  assert(tok == token::Dot || tok == token::Comma);
}

void serialization::interpret(bf_machine& m) noexcept
{
  if(tok == token::Comma)
  {
    for(std::size_t i = 0U; i < length; ++i)
      m.mem[m.position] = std::cin.get();
  }
  else
  {
    for(std::size_t i = 0U; i < length; ++i)
      std::cout.put(m.mem[m.position]);
  }
}

void serialization::print_c(std::ostream& os)
{
  os << "for(int i = 0; i < " << length
     << (tok == token::Dot
	 ?
	 "; ++i) putchar(*ptr);"
	 :
	 "; ++i) *ptr = getchar();");
}

void serialization::optimize(statement_optimizer& visitor)
{
  statement::optimize(visitor);

  visitor.visit_serialization(*this);
}


loop::loop(token_kind tok)
  : statement_seq()
{
  this->tok = tok;
  assert(tok == token::L_Square);
}

void loop::interpret(bf_machine& m) noexcept
{
  assert(length == 1U);
  
  while(m.mem[m.position])
    statement_seq::interpret(m);
}

void loop::print_c(std::ostream& os)
{
  assert(length == 1U);
  
  os << "while(*ptr) {\n";

  statement_seq::print_c(os);

  os << "}";
}

void loop::optimize(statement_optimizer& visitor)
{
  // statement::optimize is already called in statement_seq
  statement_seq::optimize(visitor);

  visitor.visit_loop(*this);
}




void statement_optimizer::visit_statement(statement& stat)
{

}

void statement_optimizer::visit_seq(statement_seq& seq)
{

}

void statement_optimizer::visit_arithmetic(arithmetic& ari)
{

}

void statement_optimizer::visit_serialization(serialization& seri)
{

}

void statement_optimizer::visit_loop(loop& lo)
{

}
