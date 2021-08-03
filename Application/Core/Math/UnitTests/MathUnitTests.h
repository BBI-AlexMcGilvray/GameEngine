#pragma once

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/UnitTests/MatrixTests.h"
#include "Core/Math/UnitTests/VectorTests.h"

namespace Core {
namespace Math {
  bool RunMathUnitTests()
  {
    std::cout << "Starting unit tests..." << std::endl;

    bool vectorTests = VERIFY(Math::RunVectorTests());

    bool matrixTests = VERIFY(Math::RunMatrixTests());

    std::cout << "Finished unit tests..." << std::endl;

    return (vectorTests && matrixTests);
  }
}// namespace Math
}// namespace Core