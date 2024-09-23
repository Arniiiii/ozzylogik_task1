#include <cstddef>
#include <fstream>
#include <qcoreapplication.h>
#include <qobject.h>
#include <string>

#include "fmt/base.h"
#include "fmt/core.h"
#include "fmtlog/fmtlog.h"

#include "QByteArray"
#include "QCoreApplication"
#include "QSqlDatabase"
#include "QString"
#include "QThread"

#include "task1/a.hpp"
#include "task1/config.hpp"
#include "task1standalone/a.hpp"
#include "task1standalone/b.hpp"
#include "task1standalone/c.hpp"
#include "task1standalone/config_cmd.hpp"

int main(int argc, char **argv, char **envp)
{
  task1::Config config{};
  try
    {
      int errc = setConfigViaCmd(config, argc, argv, envp);
      if (errc != 0)
        {
          return errc;
        }
    }
  catch (cxxopts::exceptions::exception &e)
    {
      fmt::println("Got an exception at parsing cmdline arguments: {}", e.what());
      return 1;
    }
  {
    logi("Doing part A...");
    fmtlog::poll();
    int errc = task1standalone::a(config.charset, config.columns, config.rows, config.record_size,
                                  config.output_file);
    if (errc != 0)
      {
        return errc;
      }
    logi("Part A completed.");
  }
  {
    logi("Doing part B...");
    fmtlog::poll();
    int errc = task1standalone::partb(config.vowelset, config.output_file, config.output_file_b);
    if (errc != 0)
      {
        return errc;
      }
    logi("Part B completed.");
  }
  {
    logi("Doing part C...");
    fmtlog::poll();
    int fake_argc = 1;
    char *fake_argv[1] = {{argv[0]}};
    QCoreApplication qt_app(fake_argc, fake_argv);  // https://bugreports.qt.io/browse/QTBUG-117952

    // https://heavydeck.net/blog/minimal-qt-console-application/
    std::shared_ptr<QThread> main_qthread(QThread::create(
        [](std::string const &csvfile, std::string const &sqlite_database_path) {
          logd("Supported database drivers in the used Qt: {}",
               QSqlDatabase::drivers().join(",").toStdString());
          fmtlog::poll();
          int errc = task1standalone::partc(csvfile, sqlite_database_path);
          if (errc != 0)
            {
              QCoreApplication::exit(errc);
            }
          QCoreApplication::exit(0);
        },
        config.output_file, config.sqlite_database_path));
    main_qthread->start();
    int errc = qt_app.exec();
    main_qthread->wait();
    if (errc != 0)
      {
        return errc;
      }
    logi("Part C completed.");
    fmtlog::poll();
  }
  return 0;
}
