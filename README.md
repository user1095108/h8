# h8

A header-only C++17 library for packing short strings into integers. It can be used for converting enums to strings and back.

## How It Works

`h8` packs up to `sizeof(hash_t)` characters of a string into an integer by placing each byte at a successive bit offset (`char[i]` → bits `i*CHAR_BIT`). The result is a lossless encoding for strings short enough to fit, and a cheap "hash" for longer ones.

On platforms with `__int128` support, `hash_t` is `unsigned __int128` (16 bytes / 16 characters). Otherwise it falls back to `std::uintmax_t` (typically 8 bytes / 8 characters).

## Requirements

- C++17 compiler

## Usage
### Hash a string
```c++
constexpr auto h = h8::hash("hello");        // from string literal
constexpr auto h = h8::hash(sv);             // from std::string_view
h8::hash(ptr, len);                          // from pointer + length
```

### User-defined literal
```c++
using namespace h8::literals;

constexpr auto h = "hello"_h8;
```

### Round-trip back to a string
```c++
constexpr auto h   = h8::hash("hi");
auto           arr = h8::to_array(h);   // std::array
std::string    s   = h8::to_string(h);  // std::string
```

### Converting enums to strings
```c++
using namespace h8::literals;

enum : h8::hash_t
{
    AAA = "AAA"_h8,
    BB = "BB"_h8,
};

std::cout << h8::to_string(AAA) << std::endl;
std::cout << h8::to_string(BB) << std::endl;
```
## API Reference

| Symbol | Description |
|---|---|
| `h8::hash_t` | Underlying integer type (`unsigned __int128` or `std::uintmax_t`) |
| `h8::hash(literal)` | `constexpr` hash of a string literal |
| `h8::hash(string_view)` | `constexpr` hash of a `std::string_view` |
| `h8::hash(ptr, len)` | `constexpr` hash from a pointer and length |
| `h8::to_array(h)` | Unpack a hash to a null-terminated `std::array<char const, N+1>` |
| `h8::to_string(h)` | Unpack a hash to a `std::string` |
| `"..."_h8` | User-defined literal (requires `using namespace h8::literals`) |

## Limitations

- This implementation is inappropriate for general-purpose hashing.
- Strings longer than `sizeof(hash_t)` are **truncated** — only the first N characters are encoded. Collisions are possible for longer strings.
- `to_string()` / `to_array()` only recover the original string if it was short enough to fit losslessly; otherwise, a **truncated** string is recovered.
