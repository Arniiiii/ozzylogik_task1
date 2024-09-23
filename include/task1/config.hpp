#ifndef TASK1_CONFIG_HPP
#define TASK1_CONFIG_HPP

#include <array>
#include <cstdint>
#include <string>

#include "task1/fmtlog_verbosity_level.hpp"

namespace task1
{

  struct Config
  {
    constexpr const static uint64_t default_rows = 1024;
    constexpr const static uint64_t default_columns = 6;
    constexpr const static uint64_t default_record_size = 8;
    constexpr const static task1::E_verbosityLevel default_verbosity_level
        = task1::E_verbosityLevel::INF;
    constexpr const static std::array default_charset
        = std::to_array("0123456790abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    constexpr const static std::array default_vowelset = std::to_array("aeiouyAEIOUY");
    constexpr const static std::array default_output_file = std::to_array("output.csv");
    constexpr const static std::array default_output_file_b
        = std::to_array("output_changed_after_b.csv");
    constexpr const static std::array default_sqlite_database_path
        = std::to_array("sqlite_database.db");

    uint64_t rows = default_rows;
    uint64_t columns = default_columns;
    uint64_t record_size = default_record_size;
    task1::E_verbosityLevel verbosity_level = default_verbosity_level;
    std::string charset = std::string(default_charset.data());
    std::string vowelset = std::string(default_vowelset.data());
    std::string output_file = std::string(default_output_file.data());
    std::string output_file_b = std::string(default_output_file.data());
    std::string sqlite_database_path = std::string(default_sqlite_database_path.data());
  } __attribute__((aligned(128)));  // clangd's proposal

}  // namespace task1

#endif /* TASK1_CONFIG_HPP */
