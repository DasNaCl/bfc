#include "lexer.hpp"
#include "parser.hpp"

#include "length_encoder.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
  std::vector<std::string> args;
  args.resize(argc - 1);

  for(int i = 1; i < argc; ++i)
    args[i - 1] = argv[i];
  if(argc < 2)
  {
    std::cerr << "No input data.\n";
    return 0;
  }

  // todo: argv[1] dude, really??
  lexer lex(argv[1]);
  parser par(lex);

  auto ptr = par.parse();

  bf_machine machine;

  if(argc == 2 || argc == 4)
  {
    if(argc > 3)
    {
      length_encoder opt;
      ptr->optimize(opt);
    }
    ptr->interpret(machine);
  }
  else
  {
    std::cout << "#include <stdio.h>\n"
              << "int main(int argc, char** argv) {\n"
              << "char array[30000] = {0}; char* ptr = array;\n";

    if(argc == 5)
    {
      length_encoder opt;
      ptr->optimize(opt);
    }
    ptr->print_c(std::cout);
    
    std::cout << "}\n";
  }
  
  return 0;
}
