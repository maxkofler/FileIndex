#include <gtest/gtest.h>

#include <fstream>

#include "random.h"
#include "log.h"

int glob_argc;
char** glob_argv;

#include <fstream>

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  glob_argc = argc;
  glob_argv = argv;
  testing::InitGoogleTest(&argc, argv);

  srand(time(0));

  hlog = new Log::Log(Log::MEM);
  hlog->setFeature(Log::FEATURE_PRINTFUNNAMES, false);
  hlog->setFeature(Log::FEATURE_PROFILE, true);
<<<<<<< HEAD:fileindex/tests/test_main/main.cpp
  FUN();

  std::ofstream* outFile = new std::ofstream();
  outFile->open("profile.json");
  hlog->setProfileStream(outFile);

  LOGU("Starting tests...");
=======

  std::ofstream outFile;
  outFile.open("trace.json", std::ios::out);
  hlog->setProfileStream(&outFile);
>>>>>>> bb16c1d (Added profiling support from Log submodule):tests/test_main/main.cpp

  int res = 0;

  {
    FUN();

    LOGU("Starting tests...");

    try {
      res = RUN_ALL_TESTS();
    } catch (...) {
      LOGUE("Other error");
    }
  }

  delete hlog;

<<<<<<< HEAD:fileindex/tests/test_main/main.cpp
  outFile->flush();
  outFile->close();
=======
  outFile.flush();
  outFile.close();
>>>>>>> bb16c1d (Added profiling support from Log submodule):tests/test_main/main.cpp

  return res;
}
