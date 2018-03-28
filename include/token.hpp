#pragma once

#include <ostream>

enum class token_kind : char
{
  Plus     = '+',
  Minus    = '-',
  L_Shift  = '<',
  R_Shift  = '>',

  L_Square = '[',
  R_Square = ']',

  Dot      = '.',
  Comma    = ',',

  Unknown  = 0
};

struct token
{
  static constexpr const token_kind Plus     = token_kind::Plus;
  static constexpr const token_kind Minus    = token_kind::Minus;
  static constexpr const token_kind L_Shift  = token_kind::L_Shift;
  static constexpr const token_kind R_Shift  = token_kind::R_Shift;
  static constexpr const token_kind L_Square = token_kind::L_Square;
  static constexpr const token_kind R_Square = token_kind::R_Square;
  static constexpr const token_kind Dot      = token_kind::Dot;
  static constexpr const token_kind Comma    = token_kind::Comma;
  static constexpr const token_kind Unknown  = token_kind::Unknown;
  
  
  token_kind kind { token_kind::Unknown };
  std::size_t column { 0U };
  std::size_t row { 0U };
};

extern bool operator!=(const token& tok, token_kind kind) noexcept;
extern bool operator!=(token_kind kind, const token& tok) noexcept;
extern bool operator==(const token& tok, token_kind kind) noexcept;
extern bool operator==(token_kind kind, const token& tok) noexcept;

extern std::ostream& operator<<(std::ostream& os, token_kind tok);
extern std::ostream& operator<<(std::ostream& os, const token& tok);
