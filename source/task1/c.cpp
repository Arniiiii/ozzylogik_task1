#include "task1/c.hpp"

#include <qcontainerfwd.h>
#include <qsqldatabase.h>
#include <string>

#include "fmtlog/fmtlog.h"

#include "QFile"
#include "QSqlDatabase"
#include "QSqlError"
#include "QSqlQuery"
#include "QString"
#include "QTextStream"

namespace task1
{

  int createDatabase(QString const &csvFilePath, QSqlDatabase &database_connection)
  {
    QFile file(csvFilePath);
    if (file.open(QIODevice::ReadOnly))
      {
        QTextStream csv_in(&file);
        QString line = csv_in.readLine();
        QStringList columns = line.split(",");
        QSqlQuery query(database_connection);
        if (!query.exec([columns_size = columns.size()]() {
              QString query_string = "CREATE TABLE records (";
              for (std::size_t i = 0; i < columns_size; ++i)
                {
                  query_string += "col" + QString::number(i) + " TEXT, ";
                }
              query_string += "col" + QString::number(columns_size) + ")";
              logd("Construction query: {}", query_string.toStdString());
              fmtlog::poll();
              return query_string;
            }()))
          {
            loge("Database creation query failed: {}", query.lastError().text().toStdString());
            fmtlog::poll();
            return 1;
          };
        auto get_query_template = [columns_size = columns.size()]() {
          QString query_template = "INSERT INTO records (";
          for (std::size_t i = 0; i < (columns_size - 1); ++i)
            {
              query_template += "col" + QString::number(i) + ", ";
            }
          query_template += "col" + QString::number(columns_size) + ") VALUES (";
          for (std::size_t i = 0; i < (columns_size - 1); ++i)
            {
              query_template += "?,";
            }
          query_template += "?)";
          logd("Construction query: {}", query_template.toStdString());
          fmtlog::poll();
          return query_template;
        };
        database_connection.transaction();
        query.prepare(get_query_template());
        for (const auto &record : columns)
          {
            query.addBindValue(record);
          }
        while (!csv_in.atEnd())
          {
            line = csv_in.readLine();
            columns = line.split(",");
            query.prepare(get_query_template());
            for (const auto &record : columns)
              {
                query.addBindValue(record);
              }
            if (!query.exec())
              {
                {
                  loge("Insert query failed: {}", query.lastError().text().toStdString());
                  fmtlog::poll();
                  return 1;
                };
              };
          }
        database_connection.commit();
        file.close();
      }
    else
      {
        return 1;
      }
    return 0;
  }

  int deleteRowsWithNumberInSecondColumn(QSqlDatabase &database_connection)
  {
    QSqlQuery query(database_connection);
    QString deletion_query_text
        = "DELETE FROM records WHERE substr(col2, 1, 1) BETWEEN '0' AND '9'";
    logd("Executing deletion query: {}", deletion_query_text.toStdString());
    fmtlog::poll();
    if (!query.exec(deletion_query_text))
      {
        loge("Deletion query failed: {}", query.lastError().text().toStdString());
        fmtlog::poll();
        return 1;
      };
    return 0;
  }
}  // namespace task1
