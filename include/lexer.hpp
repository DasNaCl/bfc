#pragma once

#include "token.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <map>

class lexer
{
public:
  explicit lexer(const std::string& filepath);

  token next();
private:
  void inc_col_or_row(char last, char ch) noexcept;
private:
  std::map<char, token_kind> lookup;
  std::fstream file;
  std::size_t col;
  std::size_t row;
};
