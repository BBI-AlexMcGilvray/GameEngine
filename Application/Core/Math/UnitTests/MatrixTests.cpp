#include "MatrixTests.h"

#include "../../Debugging/Headers/Macros.h"

#include "../Headers/Matrix.h"
#include "../Headers/Matrix2x2.h"
#include "../Headers/Matrix3x3.h"
#include "../Headers/Matrix4x4.h"

#define GLOBAL_EXPLICIT 1

namespace Math
{
	bool RunMatrixTests()
	{
		std::cout << "Starting matrix tests..." << std::endl;

		std::cout << "Starting SIMPLE tests..." << std::endl;
		bool simple = VERIFY(SimpleMatrixTests());

		std::cout << "Starting STANDARD tests..." << std::endl;
		bool standard = VERIFY(StandardMatrixTests());

		std::cout << "Starting DIFFICULT tests..." << std::endl;
		bool difficult = VERIFY(DifficultMatrixTests());

		return VERIFY(simple && standard && difficult);
	}

	bool SimpleMatrixTests()
	{
		auto float2x2_single = Float2x2(Float2(1.0f), Float2(1.0f));
		auto float2x2_double = Float2x2(Float2(1.0f), Float2(2.0f));
		auto float2x2_float2(float2x2_double);
		auto float2x2_copy = float2x2_float2;

		return true;
	}

	bool StandardMatrixTests()
	{
		auto float3x3_double = Float3x3(Float3(1.0f), Float3(2.0f), Float3(3.0f));

		auto e1Equal = VERIFY(float3x3_double.E1 == Float3(1.0f));
		auto e2Equal = VERIFY(float3x3_double.E2 == Float3(2.0f));
		auto e3Equal = VERIFY(float3x3_double.E3 == Float3(3.0f));

		auto basisE1 = float3x3_double[E1{}];
		auto i0 = float3x3_double[0];
		auto accessorsEqual = VERIFY(basisE1 == i0);

		auto float2x2_fromfloat3x3 = float3x3_double.E1E2;

		auto equalityTest = VERIFY(float2x2_fromfloat3x3 == float3x3_double.E1E2);

		return true;
	}

	bool DifficultMatrixTests()
	{
		return true;
	}
};