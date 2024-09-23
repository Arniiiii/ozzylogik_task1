#ifndef TASK1_CONFIG_CMD_HPP
#define TASK1_CONFIG_CMD_HPP

#include <type_traits>

#include "fmt/ranges.h"
#include "fmtlog/fmtlog.h"

#include "constexpr-to-string/to_string.hpp"
#include "cxxopts.hpp"
#include "magic_enum.hpp"

#include "task1/config.hpp"
#include "task1/fmtlog_verbosity_level.hpp"
#include "task1standalone/version.h"

inline int setConfigViaCmd(task1::Config &config, int argc, char **argv, char ** /*envp*/)
{
  cxxopts::Options options(
      "Task1",
      R"(Task1 program is expected to do some stuff that Ozzylogik company asked me to do as a test of my knowledge.
А. Generate a csv file with 1024 records of 6 columns each, filled with strings of random
characters (numbers and Latin letters) of 8 characters each.
B. Read the contents of the file, replace odd digits with #, delete the records in which
each of the six lines begins with a vowel letter, save the edited file with a different name.
the edited file with a different name.
С. Read the contents of the file from point A, create a sqlite database in the program, save all
data in a table.
Using sql tools, delete the records in which the first character in the second column is a number.

    Translated from Ukrainian via deepl.com
  )");
  options.add_options()(
      "r,rows", "How many rows    in csv",
      cxxopts::value<uint64_t>()->default_value(to_string<task1::Config::default_rows>.data()))(
      "c,columns", "How many columns in csv",
      cxxopts::value<uint64_t>()->default_value(to_string<task1::Config::default_columns>.data()))(

      "s,record-size", "How many symbols in record-size",
      cxxopts::value<uint64_t>()->default_value(
          to_string<task1::Config::default_record_size>.data()))(
      "charset", "Set of symbols which will be generated into csv file",
      cxxopts::value<std::string>()->default_value(task1::Config::default_charset.data()))(
      "vowelset", "Set of symbols which are considered vowels.",
      cxxopts::value<std::string>()->default_value(task1::Config::default_vowelset.data()))(
      "o,output-file", "File name where csv will be written",
      cxxopts::value<std::string>()->default_value(task1::Config::default_output_file.data()))(
      "O,output-file-b", "File name where changed csv (result of B.) will be written",
      cxxopts::value<std::string>()->default_value(task1::Config::default_output_file_b.data()))(
      "S,sqlite", "File where SQLite database exists",
      cxxopts::value<std::string>()->default_value(
          task1::Config::default_sqlite_database_path.data()))(
      "v,verbosity-level",
      "Verbosity level of logs.\n"
      "  Levels: DBG 4 \n"
      "          INF 3 \n"
      "          WRN 2 \n"
      "          ERR 1 \n"
      "          OFF 0 \n",
      cxxopts::value<std::underlying_type_t<task1::E_verbosityLevel>>()->default_value(
          std::to_string(magic_enum::enum_integer(task1::Config::default_verbosity_level))))(
      "h,help", "Get some help")(
      "V,version", fmt::format("Get version. Current version: {}", TASK1STANDALONE_VERSION));

  auto result = options.parse(argc, argv);

  config.verbosity_level = static_cast<task1::E_verbosityLevel>(
      result["verbosity-level"].as<std::underlying_type_t<task1::E_verbosityLevel>>());
  fmtlog::setLogLevel(verbosityLevelMap(task1::E_verbosityLevel(config.verbosity_level)));

  if ((result.arguments().empty() && result.unmatched().empty()))
    {
      logd("No arguments changed. OK, we'll live with defaults...");
    }

  if (result.count("help") != 0U)
    {
      fmt::println("{}", options.help());
      return 1;
    }

  if (result.count("version") != 0U)
    {
      fmt::println("Task1 {}", TASK1STANDALONE_VERSION);
      return 1;
    }

  if (!result.unmatched().empty())
    {
      loge("There's unmatched arguments : {}\n", result.unmatched());
      fmt::println("{}", options.help());
      return std::make_error_code(std::errc::argument_out_of_domain).value();
    };

  config.rows = result["rows"].as<std::uint64_t>();
  config.columns = result["columns"].as<std::uint64_t>();
  config.record_size = result["record-size"].as<std::uint64_t>();
  config.charset = result["charset"].as<std::string>();
  config.vowelset = result["vowelset"].as<std::string>();
  config.output_file = result["output-file"].as<std::string>();
  config.output_file_b = result["output-file-b"].as<std::string>();
  config.sqlite_database_path = result["sqlite"].as<std::string>();

  return 0;
}

#endif /* TASK1_CONFIG_CMD_HPP */
