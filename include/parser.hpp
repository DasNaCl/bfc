#pragma once

#include "statements.hpp"
#include <memory>

class lexer;

class parser
{
public:
  explicit parser(lexer& lex) noexcept;

  statement::ptr parse();
private:
  lexer& lex;
};
