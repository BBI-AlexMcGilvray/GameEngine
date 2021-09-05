
#pragma once

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/SimpleModelData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/StaticModelData.h"
#include "Data/Rendering/Headers/TextureData.h"

namespace Data
{
	/*
		This file has been auto-generated

		DO NOT CHANGE
	*/
	struct Assets
	{
		struct SimpleModels
		{
		};
		const SimpleModels spmdl;
		struct StaticModels
		{
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
		};
		const AnimatedModels amdl;
		struct SimpleMeshes
		{
		};
		const SimpleMeshes spmsh;
		struct StaticMeshes
		{
		};
		const StaticMeshes smsh;
		struct AnimatedMeshes
		{
		};
		const AnimatedMeshes amsh;
		struct Materials
		{
		};
		const Materials mat;
		struct Skeletons
		{
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
		};
		const SkeletonAnimations sanim;

	};
	const Assets Ast;
	}
