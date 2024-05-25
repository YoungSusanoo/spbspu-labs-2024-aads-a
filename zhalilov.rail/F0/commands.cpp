#include "commands.hpp"

#include <iostream>

#include <calc/getInfix.hpp>
#include <calc/infixToPostfix.hpp>

void zhalilov::calc(const modulesMap &modules, std::ostream &historyOut, std::istream &in, std::ostream &out)
{
  std::string expr;
  std::getline(in, expr);
  Queue< InfixToken > infix;
  getInfixFromString(infix, expr);
  Queue< PostfixToken > postfix;
  infixToPostfix(infix, postfix);

}
