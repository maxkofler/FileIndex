#include <gtest/gtest.h>

#include <fstream>

#include "random.h"
#include "log.h"

int glob_argc;
char** glob_argv;

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  glob_argc = argc;
  glob_argv = argv;
  testing::InitGoogleTest(&argc, argv);

  srand(time(0));

  hlog = new Log::Log(Log::MEM);
  hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
  hlog->setFeature(Log::FEATURE_PROFILE, true);
  FUN();

  std::ofstream* outFile = new std::ofstream();
  outFile->open("profile.json");
  hlog->setProfileStream(outFile);

  LOGU("Starting tests...");

  int res = 0;
  try {
    res = RUN_ALL_TESTS();
  } catch (...) {
    LOGUE("Other error");
  }

  delete hlog;

  outFile->flush();
  outFile->close();

  return res;
}
