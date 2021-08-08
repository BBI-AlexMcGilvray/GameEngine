#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "Declarations.h"

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Headers/Macros.h"

namespace Application {
const char *logFileName = "";

void Log(const char *output);
const char *ReadLog(int numCharacters = 0);
}// namespace Application