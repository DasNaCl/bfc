#pragma once

#include "statements.hpp"

class length_encoder : public statement_optimizer
{
public:
  void visit_seq(statement_seq& seq) override;
private:
  static bool compatible(token_kind lhs, token_kind rhs) noexcept;
};
