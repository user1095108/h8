#ifndef H8_HPP
# define H8_HPP
# pragma once

#include <climits>
#include <cstdint>
#include <array>
#include <concepts> // std::unsigned_integral
#include <string>
#include <utility> // std::index_sequence

namespace h8
{

using hash_t = std::uintmax_t;

constexpr auto to_array(std::unsigned_integral auto const h) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
    {
      return std::array<char const, sizeof(h) + 1>{
        char(h >> I * CHAR_BIT)...};
    }(std::make_index_sequence<sizeof(h)>());
}

constexpr std::string to_string(std::unsigned_integral auto const h)
{
  return {to_array(h).data()};
}

template <std::unsigned_integral T = hash_t>
constexpr T hash(char const* const s, std::size_t const N) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
    {
      return ((hash_t(I < N ? s[I] : 0) << I * CHAR_BIT) | ...);
    }(std::make_index_sequence<sizeof(T)>());
}

template <typename T = hash_t, std::size_t N>
constexpr auto hash(char const(&s)[N]) noexcept
{
  return hash<T>(s, N - 1);
}

template <typename T = hash_t>
constexpr auto hash(std::string_view const& s) noexcept
{
  return hash<T>(s.data(), s.size());
}

namespace literals
{

constexpr auto operator"" _h8(char const* const s,
  std::size_t const N) noexcept
{
  return hash(s, N);
}

}

}

#endif // H8_HPP
