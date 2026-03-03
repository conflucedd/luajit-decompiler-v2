/*
Requirements:
  C++20
  Default char is unsigned (-funsigned-char)
*/

// Check if char is unsigned
#ifdef __CHAR_UNSIGNED__
#define _CHAR_UNSIGNED
#endif

#ifndef _CHAR_UNSIGNED
#warning Default char is not unsigned! Compile with -funsigned-char or equivalent.
#endif

#include <bit>
#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>

// Linux headers
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>

// Platform-specific type aliases
using HANDLE = int;
constexpr HANDLE INVALID_HANDLE_VALUE = -1;

// Platform abstraction functions
inline HANDLE platform_open(const char* path, bool write) {
    int fd = open(path, write ? (O_WRONLY | O_CREAT | O_TRUNC) : O_RDONLY, 0666);
    return fd;
}
inline void platform_close(HANDLE handle) {
    close(handle);
}
inline bool platform_read(HANDLE handle, void* buffer, uint32_t size, uint32_t* bytesRead) {
    ssize_t result = read(handle, buffer, size);
    if (result < 0) return false;
    *bytesRead = result;
    return true;
}
inline bool platform_write(HANDLE handle, const void* buffer, uint32_t size, uint32_t* bytesWritten) {
    ssize_t result = write(handle, buffer, size);
    if (result < 0) return false;
    *bytesWritten = result;
    return true;
}
inline uint64_t platform_get_file_size(HANDLE handle) {
    struct stat st;
    if (fstat(handle, &st) == -1) return 0;
    return st.st_size;
}

#define DEBUG_INFO __FUNCTION__, __FILE__, __LINE__

constexpr char PROGRAM_NAME[] = "LuaJIT Decompiler v2";
constexpr uint64_t DOUBLE_SIGN = 0x8000000000000000;
constexpr uint64_t DOUBLE_EXPONENT = 0x7FF0000000000000;
constexpr uint64_t DOUBLE_FRACTION = 0x000FFFFFFFFFFFFF;
constexpr uint64_t DOUBLE_SPECIAL = DOUBLE_EXPONENT;
constexpr uint64_t DOUBLE_NEGATIVE_ZERO = DOUBLE_SIGN;

void print(const std::string& message);
//std::string input();
void print_progress_bar(const double& progress = 0, const double& total = 100);
void erase_progress_bar();
void assert(const bool& assertion, const std::string& message, const std::string& filePath, const std::string& function, const std::string& source, const uint32_t& line);
std::string byte_to_string(const uint8_t& byte);

class Bytecode;
class Ast;
class Lua;

#include "bytecode/bytecode.h"
#include "ast/ast.h"
#include "lua/lua.h"