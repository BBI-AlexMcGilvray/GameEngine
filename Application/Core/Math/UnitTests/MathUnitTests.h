#pragma once

#include "VectorTests.h"
#include "MatrixTests.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace Math
	{
		bool RunMathUnitTests()
		{
			std::cout << "Starting unit tests..." << std::endl;

			bool vectorTests = VERIFY(Math::RunVectorTests());

			bool matrixTests = VERIFY(Math::RunMatrixTests());

			std::cout << "Finished unit tests..." << std::endl;

			return (vectorTests && matrixTests);
		}
	}
}