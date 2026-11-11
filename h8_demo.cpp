#include "h8-fast.hpp"

#include <iostream>
#include <string>
#include <string_view>

using namespace h8;
using namespace h8::literals;

constexpr auto cmd_greet = "greet"_h8;
constexpr auto cmd_help  = "help"_h8;
constexpr auto cmd_quit  = "quit"_h8;

bool dispatch(std::string_view const cmd)
{
  switch (hash(cmd.data(), cmd.size()))
  {
    case cmd_greet:
      std::cout << "Hello, world!\n";
      return true;
    case cmd_help:
      std::cout << "commands: greet | help | quit\n";
      return true;
    case cmd_quit:
      std::cout << "Goodbye!\n";
      return false;
    default:
      std::cout << "unknown command: " << cmd << '\n'
                << "try 'help'\n";
      return true;
  }
}

int main()
{
  std::cout << "h8 demo — type 'help' for commands, 'quit' to exit\n";
  for (std::string line; std::cout << "> " && std::getline(std::cin, line); )
  {
    if (line.empty())
      continue;

    if (line.back() == '\r')
      line.pop_back();

    if (!dispatch(line))
      break;
  }
}
