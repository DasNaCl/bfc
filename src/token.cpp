#include "token.hpp"

bool operator!=(const token& tok, token_kind k) noexcept
{
  return tok.kind != k;
}

bool operator!=(token_kind kind, const token& tok) noexcept
{
  return tok != kind;
}

bool operator==(const token& tok, token_kind k) noexcept
{
  return tok.kind == k;
}

bool operator==(token_kind kind, const token& tok) noexcept
{
  return tok == kind;
}

std::ostream& operator<<(std::ostream& os, token_kind tok)
{
  switch(tok)
  {
  case token_kind::Plus:     return os << "Plus";
  case token_kind::Minus:    return os << "Minus";
  case token_kind::L_Shift:  return os << "L_Shift";
  case token_kind::R_Shift:  return os << "R_Shift";
  case token_kind::L_Square: return os << "L_Square";
  case token_kind::R_Square: return os << "R_Square";
  case token_kind::Dot:      return os << "Dot";
  case token_kind::Comma:    return os << "Comma";

  case token_kind::Unknown:  return os << "?";
  }
}

std::ostream& operator<<(std::ostream& os, const token& tok)
{
  return os << tok.row << ":" << tok.column << ": " << tok.kind;
}
