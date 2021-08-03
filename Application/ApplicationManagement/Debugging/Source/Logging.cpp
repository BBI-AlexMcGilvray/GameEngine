#include "ApplicationManagement\Debugging\Headers\Logging.h"

namespace Application {
void Log(const char *output)
{
  // open file
  // add output
  // close file
}

const char *ReadLog(int numCharacters)
{
  // open file
  if (numCharacters == 0) {
    // return whole log
  } else {
    // return < numCharacters > from the log, starting from the end
  }
  // close file

  // this is just to compile until this is flushed out
  return nullptr;
}
}// namespace Application