#include <iostream>

#include "h8.hpp"

using namespace h8::literals;

int main()
{
  enum : h8::hash_t
  {
    AAA = "AAA"_h8,
    BB = "BB"_h8,
  };

  std::cout << h8::to_string(AAA) << std::endl;
  std::cout << h8::to_string(BB) << std::endl;

  //
  std::cout << "AAA"_h8 << std::endl;
  std::cout << "BB"_h8 << std::endl;

  return 0;
}
