#ifndef TASK1_TASK1STANDALONE_C_HPP
#define TASK1_TASK1STANDALONE_C_HPP

#include <qcontainerfwd.h>
#include <qcoreapplication.h>
#include <qlist.h>
#include <qobject.h>
#include <qsqldatabase.h>
#include <string>

#include "fmt/ranges.h"
#include "fmtlog/fmtlog.h"

#include "task1/c.hpp"

namespace task1standalone
{
  inline int partc(std::string const& csv_file, std::string const& sqlite_path)
  {
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString::fromStdString(sqlite_path));
    if (database.open())
      {
        int errc = task1::createDatabase(QString::fromStdString(csv_file), database);
        if (errc != 0)
          {
            loge("Couldn't open csv_file.");
            fmtlog::poll();
            return errc;
          }
        errc = task1::deleteRowsWithNumberInSecondColumn(database);
        if (errc != 0)
          {
            loge("Couldn't open specified sqlite database.");
            fmtlog::poll();
            return errc;
          }
      }
    else
      {
        loge("Couldn't create specified sqlite database.");
        fmtlog::poll();
      }
    database.close();
    return 0;
  };
}  // namespace task1standalone

#endif /* TASK1_TASK1STANDALONE_C_HPP */
