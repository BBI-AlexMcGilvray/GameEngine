
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
			const AssetName<Rendering::SimpleModelData> MI_0 = AssetName<Rendering::SimpleModelData>(Hash(1740916818));
		};
		const SimpleModels spmdl;
		struct StaticModels
		{
			const AssetName<Rendering::StaticModelData> MI_0 = AssetName<Rendering::StaticModelData>(Hash(1740916818));
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
			const AssetName<Rendering::AnimatedModelData> Woman_0 = AssetName<Rendering::AnimatedModelData>(Hash(3593970672));
		};
		const AnimatedModels amdl;
		struct SimpleMeshes
		{
			const AssetName<Rendering::SimpleMeshData> MI_0 = AssetName<Rendering::SimpleMeshData>(Hash(1740916818));
		};
		const SimpleMeshes spmsh;
		struct StaticMeshes
		{
			const AssetName<Rendering::StaticMeshData> MI_0 = AssetName<Rendering::StaticMeshData>(Hash(1740916818));
		};
		const StaticMeshes smsh;
		struct AnimatedMeshes
		{
			const AssetName<Rendering::AnimatedMeshData> Woman_0 = AssetName<Rendering::AnimatedMeshData>(Hash(3593970672));
		};
		const AnimatedMeshes amsh;
		struct Materials
		{
			const AssetName<Rendering::MaterialData> MI_0 = AssetName<Rendering::MaterialData>(Hash(1740916818));
			const AssetName<Rendering::MaterialData> Woman_0 = AssetName<Rendering::MaterialData>(Hash(3593970672));
		};
		const Materials mat;
		struct Skeletons
		{
			const AssetName<Rendering::SkeletonData> Woman_0 = AssetName<Rendering::SkeletonData>(Hash(3593970672));
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Death = AssetName<Rendering::SkeletonAnimationData>(Hash(4259411171));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Idle = AssetName<Rendering::SkeletonAnimationData>(Hash(4140853032));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump = AssetName<Rendering::SkeletonAnimationData>(Hash(2420364265));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump2 = AssetName<Rendering::SkeletonAnimationData>(Hash(2348057118));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_PickUp = AssetName<Rendering::SkeletonAnimationData>(Hash(2634831132));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Punch = AssetName<Rendering::SkeletonAnimationData>(Hash(2816760887));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Running = AssetName<Rendering::SkeletonAnimationData>(Hash(127888874));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_SitIdle = AssetName<Rendering::SkeletonAnimationData>(Hash(2289128976));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Sitting = AssetName<Rendering::SkeletonAnimationData>(Hash(437013649));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Walking = AssetName<Rendering::SkeletonAnimationData>(Hash(460649925));
		};
		const SkeletonAnimations sanim;

	};
	const Assets Ast;
	}
