#include "VectorTests.h"

#include "../../Debugging/Headers/Macros.h"

#include "../Headers/Vector.h"
#include "../Headers/Vector2.h"
#include "../Headers/Vector3.h"
#include "../Headers/Vector4.h"

#define GLOBAL_EXPLICIT 1

namespace Math
{
	bool RunVectorTests()
	{
		std::cout << "Starting vector tests..." << std::endl;

		std::cout << "Starting SIMPLE tests..." << std::endl;
		bool simple = VERIFY(SimpleVectorTests());

		std::cout << "Starting STANDARD tests..." << std::endl;
		bool standard = VERIFY(StandardVectorTests());

		std::cout << "Starting DIFFICULT tests..." << std::endl;
		bool difficult = VERIFY(DifficultVectorTests());

		return VERIFY(simple && standard && difficult);
	}

	bool SimpleVectorTests()
	{
		auto float2_single = Float2(1.0f);
		auto float2_double = Float2(1.0f, 2.0f);
		auto float2_float2(float2_double);
		auto float2_copy = float2_float2;

		return true;
	}

	bool StandardVectorTests()
	{
		auto float3_double = Float3(1.0f, 2.0f, 3.0f);

		auto xEqual = VERIFY(float3_double.X == 1.0f);
		auto yEqual = VERIFY(float3_double.Y == 2.0f);
		auto zEqual = VERIFY(float3_double.Z == 3.0f);

		auto axisX = float3_double[X{}];
		auto i0 = float3_double[0];
		auto accessorsEqual = VERIFY(axisX == i0);

		auto float2_fromfloat3 = float3_double.XY;

		auto equalityTest = VERIFY(float2_fromfloat3 == float3_double.XY);

		return true;
	}

	bool DifficultVectorTests()
	{
		return true;
	}
};