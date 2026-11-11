#ifndef H8_FAST_HPP
# define H8_FAST_HPP
# pragma once

#include <bit>     // std::bit_cast()
#include <cstddef> // std::size_t
#include <cstdint> // std::uintmax_t
#include <array>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility> // std::index_sequence<>

namespace h8
{ // this is fast, but is c++20 and loses endianess neutrality

#if defined(__SIZEOF_INT128__) && defined(__SIZEOF_LONG_LONG__) &&\
  (__SIZEOF_INT128__ > __SIZEOF_LONG_LONG__)
using hash_t = unsigned __int128;
#else
using hash_t = std::uintmax_t;
#endif // __SIZEOF_INT128__

template <typename T> requires(!std::is_same_v<T, bool>)
constexpr auto to_array(T const h) noexcept
{
  return []<auto ...I>(auto const& in, std::index_sequence<I...>) noexcept
  {
    return std::array<char const, sizeof(T) + 1>{in[I]..., '\0'};
  }(std::bit_cast<std::array<char const, sizeof(T)>>(h),
    std::make_index_sequence<sizeof(T)>{});
}

template <typename T> requires(!std::is_same_v<T, bool>)
constexpr std::string to_string(T const h)
{
  return std::string(to_array(h).data());
}

template <typename T> requires(!std::is_same_v<T, bool>)
std::string_view to_string_view(T const& h) noexcept
{
  return std::string_view(reinterpret_cast<char const*>(&h), sizeof(T));
}

template <typename T = hash_t> requires(!std::is_same_v<T, bool>)
constexpr T hash(char const* const s, std::size_t const N) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
    {
      return std::bit_cast<T>(
          std::array<char const, sizeof(T)>{(I < N ? s[I] : '\0')...}
        );
    }(std::make_index_sequence<sizeof(T)>{});
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

#endif // H8_FAST_HPP
