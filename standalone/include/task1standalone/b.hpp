#ifndef TASK1_TASK1STANDALONE_B_HPP
#define TASK1_TASK1STANDALONE_B_HPP
#include <algorithm>

#include "fmtlog/fmtlog.h"

#include "QFile"
#include "QString"
#include "QTextStream"

#include "task1/b.hpp"
#include "task1/config.hpp"

namespace task1standalone
{

  inline int partb(std::string const &vowelset, std::string const &inputPath,
                   std::string const &outputPath)
  {
    QFile inputFile(QString::fromStdString(inputPath));
    QFile outputFile(QString::fromStdString(outputPath));

    if (inputFile.open(QIODevice::ReadOnly) && outputFile.open(QIODevice::WriteOnly))
      {
        QTextStream fin(&inputFile);
        QTextStream fout(&outputFile);

        while (!fin.atEnd())
          {
            QString line = fin.readLine();
            QStringList columns = line.split(",");

            if (!std::all_of(columns.constBegin(), columns.constEnd(),
                             [&vowelset](auto const &character) {
                               return task1::startsWithVowel(character, vowelset);
                             }))
              {
#pragma unroll task1::Config::default_columns
                for (QString &record : columns)
                  {
                    record = task1::replaceOddDigits(record);
                  }
                fout << columns.join(",") << "\n";
              }
          }
        inputFile.close();
        outputFile.close();
      }
    else
      {
        loge(
            "Either the program couldn't open {} in read mode or open {} in write "
            "mode",
            inputPath, outputPath);
        return 1;
      }
    return 0;
  }

}  // namespace task1standalone

#endif /* TASK1_TASK1STANDALONE_B_HPP */
