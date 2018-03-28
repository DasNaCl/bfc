#include "parser.hpp"
#include "lexer.hpp"
#include <stdexcept>
#include <cassert>

parser::parser(lexer& lex) noexcept
  : lex(lex)
{  }

statement::ptr parser::parse()
{
  auto statements = std::make_unique<statement_seq>();

  std::vector<loop*> loops;
  token tok = lex.next();
  while(tok != token::Unknown)
  {
    switch(tok.kind)
    {
    case token::Dot:
    case token::Comma:
    {
      auto x = std::make_unique<serialization>(tok.kind);
      if(loops.empty())
        statements->add(std::move(x));
      else
        loops.back()->add(std::move(x));
    } break;

    case token::Plus:
    case token::Minus:
    case token::L_Shift:
    case token::R_Shift:
    {
      auto x = std::make_unique<arithmetic>(tok.kind);
      if(loops.empty())
        statements->add(std::move(x));
      else
        loops.back()->add(std::move(x));
    } break;

    case token::L_Square:
    case token::R_Square:
    {
      if(tok == token::R_Square && loops.empty())
      {
        throw std::invalid_argument("Pre-Closed loop");
      }
      else if(tok == token::R_Square)
      {
        loops.pop_back();
      }
      else
      {
        auto x = std::make_unique<loop>(tok.kind);
        if(loops.empty())
        {
          statements->add(std::move(x));
          auto* p = static_cast<loop*>(statements->get_last().get());
          loops.emplace_back(p);
        }
        else
        {
          loops.back()->add(std::move(x));
          auto* p = static_cast<loop*>(loops.back()->get_last().get());
          loops.emplace_back(p);
        }
      }
    } break;

    default:
      assert(false && "Logic error: Tokenizer did not filter unknown tokens");
    }
    tok = lex.next();
  }
  return std::move(statements);
}
