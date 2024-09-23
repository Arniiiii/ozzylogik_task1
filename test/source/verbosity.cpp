#include "gtest/gtest.h"

#include "task1/fmtlog_verbosity_level.hpp"

TEST(FmtlogRelatedLoglevelMap, int_to_enum)
{
  EXPECT_EQ(task1::E_verbosityLevel::OFF, 0);
  EXPECT_EQ(task1::E_verbosityLevel::ERR, 1);
  EXPECT_EQ(task1::E_verbosityLevel::WRN, 2);
  EXPECT_EQ(task1::E_verbosityLevel::INF, 3);
  EXPECT_EQ(task1::E_verbosityLevel::DBG, 4);
}

TEST(FmtlogRelatedLoglevelMap, int_to_fmtlog_enum)
{
  EXPECT_EQ(fmtlog::LogLevel::OFF, task1::verbosityLevelMap(task1::E_verbosityLevel(0)));
  EXPECT_EQ(fmtlog::LogLevel::ERR, task1::verbosityLevelMap(task1::E_verbosityLevel(1)));
  EXPECT_EQ(fmtlog::LogLevel::WRN, task1::verbosityLevelMap(task1::E_verbosityLevel(2)));
  EXPECT_EQ(fmtlog::LogLevel::INF, task1::verbosityLevelMap(task1::E_verbosityLevel(3)));
  EXPECT_EQ(fmtlog::LogLevel::DBG, task1::verbosityLevelMap(task1::E_verbosityLevel(4)));
}

TEST(FmtlogRelatedLoglevelMap, enum_to_fmtlog_enum)
{
  EXPECT_EQ(fmtlog::LogLevel::OFF, task1::verbosityLevelMap(task1::E_verbosityLevel::OFF));
  EXPECT_EQ(fmtlog::LogLevel::ERR, task1::verbosityLevelMap(task1::E_verbosityLevel::ERR));
  EXPECT_EQ(fmtlog::LogLevel::WRN, task1::verbosityLevelMap(task1::E_verbosityLevel::WRN));
  EXPECT_EQ(fmtlog::LogLevel::INF, task1::verbosityLevelMap(task1::E_verbosityLevel::INF));
  EXPECT_EQ(fmtlog::LogLevel::DBG, task1::verbosityLevelMap(task1::E_verbosityLevel::DBG));
}
