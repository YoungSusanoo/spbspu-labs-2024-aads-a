#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace zhalilov
{
  class Operand
  {
  public:
    Operand();
    explicit Operand(long long);
    long long getNum() const;

  private:
    long long num_;
  };
}

#endif
