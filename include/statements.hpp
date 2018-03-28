#pragma once

#include "token.hpp"
#include "bf_machine.hpp"
#include <memory>
#include <vector>

class statement;
class statement_seq;
class arithmetic;
class serialization;
class loop;

class statement_optimizer
{
public:
  virtual void visit_statement(statement& stat);
  virtual void visit_seq(statement_seq& seq);
  virtual void visit_arithmetic(arithmetic& ari);
  virtual void visit_serialization(serialization& seri);
  virtual void visit_loop(loop& lo);
};



class statement
{
private:
  friend class statement_seq;
public:
  using ptr = std::unique_ptr<statement>;
public:
  explicit statement(token_kind tok) noexcept;
  virtual ~statement() noexcept;

  virtual void interpret(bf_machine& m) noexcept = 0;
  virtual void print_c(std::ostream& os) = 0;
  virtual void optimize(statement_optimizer& visitor);

  token_kind kind() const;
  int len() const;

  virtual void inc_len(int l);
protected:
  token_kind tok;
  int length;
};

class statement_seq : public statement
{
public:
  using iterator = std::vector<statement::ptr>::iterator;
public:
  explicit statement_seq();
  virtual ~statement_seq() noexcept;

  virtual void interpret(bf_machine& m) noexcept override;
  virtual void print_c(std::ostream& os) override;
  virtual void optimize(statement_optimizer& visitor) override;

  void add(statement::ptr&& ptr);
  statement::ptr& get_last();

  iterator begin();
  iterator end();

  iterator erase(iterator it);
protected:
  std::vector<statement::ptr> statements;
};

class arithmetic : public statement
{
public:
  explicit arithmetic(token_kind tok) noexcept;

  void interpret(bf_machine& m) noexcept override;
  void print_c(std::ostream& os) override;
  void optimize(statement_optimizer& visitor) override;

  void inc_len(int l) override;
};

class serialization : public statement
{
public:
  explicit serialization(token_kind tok) noexcept;

  void interpret(bf_machine& m) noexcept override;
  void print_c(std::ostream& os) override;
  void optimize(statement_optimizer& visitor) override;
};

class loop : public statement_seq
{
public:
  explicit loop(token_kind tok);

  void interpret(bf_machine& m) noexcept override;
  void print_c(std::ostream& os) override;
  void optimize(statement_optimizer& visitor) override;
};
