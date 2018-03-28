#include "lexer.hpp"

lexer::lexer(const std::string& filepath)
  : lookup(), file(filepath, std::ios::in), col(1U), row(1U)
{
  lookup['.'] = token_kind::Dot;
  lookup[','] = token_kind::Comma;
  lookup['+'] = token_kind::Plus;
  lookup['-'] = token_kind::Minus;
  lookup['<'] = token_kind::L_Shift;
  lookup['>'] = token_kind::R_Shift;
  lookup['['] = token_kind::L_Square;
  lookup[']'] = token_kind::R_Square;
}

token lexer::next()
{
  char last = 0;
  char ch = 0;
  token t {token_kind::Unknown, col, row};
  if(!(file >> ch))
  {
    // EOF
    return token();
  }
  else
    inc_col_or_row(last, ch);

  auto it = lookup.find(ch);
  while(it == lookup.end())
  {
    last = ch;
    if(!(file >> ch))
    {
      // EOF
      return token();
    }
    else
      inc_col_or_row(last, ch);
    it = lookup.find(ch);
  }
  t.kind = it->second;

  return t;
}

void lexer::inc_col_or_row(char last, char ch) noexcept
{
  if(last == '\r' && ch == '\n')
  {
    // CRLF
    // -> do not increase row again
  }
  else if(ch == '\r' || ch == '\n')
    ++row;
  else
    ++col;
}
