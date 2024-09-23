#ifndef TASK1_TASK1_C_HPP
#define TASK1_TASK1_C_HPP

#include <qobject.h>
#include <qsqldatabase.h>
#include <string>

namespace task1
{

  int createDatabase(QString const &csvFilePath, QSqlDatabase &database_connection);

  int deleteRowsWithNumberInSecondColumn(QSqlDatabase &database_connection);

}  // namespace task1
#endif /* TASK1_TASK1_C_HPP */
