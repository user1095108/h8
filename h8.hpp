#ifndef H8_HPP
# define H8_HPP
# pragma once

#include <climits>
#include <cstdint>
#include <array>
#include <string>
#include <utility> // std::index_sequence

namespace h8
{

#if defined(__SIZEOF_INT128__) && (__SIZEOF_LONG_LONG__ < __SIZEOF_INT128__)
using hash_t = unsigned __int128;
#else
using hash_t = std::uintmax_t;
#endif // __SIZEOF_INT128__

constexpr auto to_array(auto const h) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
    {
      return std::array<char const, sizeof(h) + 1>{
        char(h >> I * CHAR_BIT)...};
    }(std::make_index_sequence<sizeof(h)>());
}

constexpr std::string to_string(auto const h) { return to_array(h).data(); }

template <typename T = hash_t>
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

constexpr auto operator""_h8(char const* const s,
  std::size_t const N) noexcept
{
  return hash(s, N);
}

}

}

#endif // H8_HPP
