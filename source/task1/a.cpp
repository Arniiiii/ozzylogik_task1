#include "task1/a.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory_resource>

#include "internal/csv_writer.hpp"

#include "task1/config.hpp"
#include "task1/randomgenerator.hpp"
namespace task1
{

  constexpr std::size_t to_be_safe_size_mem_pool = 50;

  std::string generate_random_csv_string(std::string const &charset, uint64_t columns,
                                         uint64_t rows, uint64_t record_size)
  {
    std::array<std::byte,
               sizeof(std::pmr::string) + Config::default_charset.size() + to_be_safe_size_mem_pool>
        buf_charset{};
    std::pmr::monotonic_buffer_resource pool_charset{buf_charset.data(), buf_charset.size()};
    RandomGenerator random_gen(std::pmr::string{charset}, &pool_charset);

    std::array<std::byte, sizeof(std::pmr::vector<std::pmr::string>)
                              + (sizeof(std::pmr::string) + Config::default_record_size)
                                    * Config::default_columns
                              + to_be_safe_size_mem_pool>
        buf1{};
    std::pmr::monotonic_buffer_resource pool1{buf1.data(), buf1.size()};
    std::pmr::vector<std::pmr::string> temp_vec(columns, &pool1);

    std::stringstream strs;
    auto csv_writer = csv::make_csv_writer_buffered(strs);
    for (std::uint64_t i = 0; i < rows; ++i)
      {
        std::for_each_n(temp_vec.begin(), columns,
                        [&random_gen, &record_size = record_size](std::pmr::string &a_str) {
                          a_str = random_gen.generate(record_size);
                        });
        csv_writer << temp_vec;
      }
    csv_writer.flush();
    return strs.str();
  };
}  // namespace task1
