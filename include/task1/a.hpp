#ifndef TASK1_TASK1_A_HPP
#define TASK1_TASK1_A_HPP

#include <cstddef>
#include <cstdint>
#include <string>

namespace task1
{
  std::string generate_random_csv_string(std::string const& charset, uint64_t columns,
                                         uint64_t rows, uint64_t record_size);
}
#endif /* TASK1_TASK1_A_HPP */
