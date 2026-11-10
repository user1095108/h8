#include <iostream>

#include "h8-fast.hpp"

using namespace h8::literals;

int main()
{
  enum : h8::hash_t
  {
    AAA = "AAA"_h8,
    BB = "BB"_h8,
    TEST = "1234567890123456"_h8,
  };

  std::cout << h8::to_string_view(AAA) << std::endl;
  std::cout << h8::to_string_view(BB) << std::endl;
  std::cout << h8::to_string_view(TEST) << std::endl;

  return 0;
}
