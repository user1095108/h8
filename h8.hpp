#ifndef H8_HPP
# define H8_HPP
# pragma once

#include <climits> // CHAR_BIT
#include <cstdint>
#include <array>
#include <string>
#include <utility> // std::index_sequence

namespace h8
{

#if defined(__SIZEOF_INT128__) && defined(__SIZEOF_LONG_LONG__) &&\
  (__SIZEOF_INT128__ > __SIZEOF_LONG_LONG__)
using hash_t = unsigned __int128;
#else
using hash_t = std::uintmax_t;
#endif // __SIZEOF_INT128__

template <typename T, std::size_t ...I>
constexpr auto to_array_impl(T const h, std::index_sequence<I...>) noexcept
{
  return std::array<char const, sizeof(T) + 1>{char(h >> I * CHAR_BIT)..., 0};
}

template <typename T>
constexpr auto to_array(T const h) noexcept
{
  return to_array_impl(h, std::make_index_sequence<sizeof(T)>{});
}

template <typename T>
std::string to_string(T const h) { return to_array(h).data(); }

template <typename T = hash_t, std::size_t... I>
constexpr T hash_impl(const char* const s, std::size_t const N,
  std::index_sequence<I...>) noexcept
{
  return ((T(I < N ? (unsigned char)(s[I]) : 0) << I * CHAR_BIT) | ...);
}

template <typename T = hash_t>
constexpr T hash(const char* s, std::size_t N) noexcept
{
  return hash_impl<T>(s, N, std::make_index_sequence<sizeof(T)>{});
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
