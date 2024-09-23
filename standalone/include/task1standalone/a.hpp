#ifndef TASK1_TASK1STANDALONE_A_HPP
#define TASK1_TASK1STANDALONE_A_HPP

#include <fstream>
#include <string>

#include "fmtlog/fmtlog.h"

#include "task1/a.hpp"

namespace task1standalone
{

  inline int a(std::string const& charset, uint64_t columns, uint64_t rows, uint64_t record_size,
               std::string const& output_file)
  {
    std::string csv_string = task1::generate_random_csv_string(charset, columns, rows, record_size);
    logi("Got csv-like string. Saving it to a file at {}", output_file);
    fmtlog::poll();

    std::ofstream csv_fout;

    csv_fout.open(output_file);

    if (!csv_fout.is_open())
      {
        loge("Error opening {}", output_file);

        if (csv_fout.bad())
          {
            loge("Fatal error: badbit is set.");
          }
        if (csv_fout.fail())
          {
            loge("Error details: {}", strerror(errno));
          }
        fmtlog::poll();

        // Handle the error or exit the program
        return errno;
      }

    csv_fout.write(csv_string.data(), static_cast<std::ptrdiff_t>(csv_string.size()));
    csv_fout.close();
    return 0;
  }
}  // namespace task1standalone
#endif /* TASK1_TASK1STANDALONE_A_HPP */
