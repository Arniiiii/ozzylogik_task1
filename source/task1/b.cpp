#include "task1/b.hpp"

#include "QFile"
#include "QString"
#include "QTextStream"

#include "task1/config.hpp"

namespace task1
{

  bool startsWithVowel(const QString &str, std::string const &vowels_set)
  {
    QChar first = str.at(0).toUpper();
    return vowels_set.cend() != std::find(vowels_set.cbegin(), vowels_set.cend(), first);
  }

  QString replaceOddDigits(const QString &str)
  {
    QString result = str;
#pragma unroll task1::Config::default_record_size
    for (int i = 0; i < str.length(); ++i)
      {
        if (str[i].isDigit() && (str[i].digitValue() % 2 != 0))
          {
            result[i] = '#';
          }
      }
    return result;
  }

}  // namespace task1
