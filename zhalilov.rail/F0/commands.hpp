#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>

#include <tree/twoThreeTree.hpp>
#include <list/list.hpp>
#include <calc/expressionTokens.hpp>

namespace zhalilov
{
  using modulesMap = TwoThree< std::pair< std::string, List< PostfixToken > > >;

  void calc(const modulesMap &, std::ostream &historyOut, std::istream &, std::ostream &);

  void modulesshow(const modulesMap &, std::istream &, std::ostream &);
  void modulesadd(modulesMap &, std::istream &, std::ostream &);
  void moudlesdelete(modulesMap &, std::istream &, std::ostream &);
  void modulesvaradd(modulesMap &, std::istream &, std::ostream &);
  void modulesvardelete(modulesMap &, std::istream &, std::ostream &);
  void modulesimport(modulesMap &, std::istream &, std::ostream &);
  void modulesexport(const modulesMap &, std::istream &, std::ostream &);
}

#endif
