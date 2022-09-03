
#pragma once

#include <array>

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

#include "Data/AssetTypes/EntityData.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"
#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/ShaderData.h"
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
			const AssetName<Rendering::SimpleModelData> MI_0 = AssetName<Rendering::SimpleModelData>(AsHash(1740916818));
			const AssetName<Rendering::SimpleModelData> Monk_0 = AssetName<Rendering::SimpleModelData>(AsHash(2841434648));
		};
		const SimpleModels spmdl;
		struct StaticModels
		{
			const AssetName<Rendering::StaticModelData> MI_0 = AssetName<Rendering::StaticModelData>(AsHash(1740916818));
			const AssetName<Rendering::StaticModelData> Monk_0 = AssetName<Rendering::StaticModelData>(AsHash(2841434648));
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
			const AssetName<Rendering::AnimatedModelData> Monk_1 = AssetName<Rendering::AnimatedModelData>(AsHash(2848250392));
		};
		const AnimatedModels amdl;
		struct SimpleMeshes
		{
			const AssetName<Rendering::SimpleMeshData> MI_0 = AssetName<Rendering::SimpleMeshData>(AsHash(1740916818));
			const AssetName<Rendering::SimpleMeshData> Monk_0 = AssetName<Rendering::SimpleMeshData>(AsHash(2841434648));
		};
		const SimpleMeshes spmsh;
		struct StaticMeshes
		{
			const AssetName<Rendering::StaticMeshData> MI_0 = AssetName<Rendering::StaticMeshData>(AsHash(1740916818));
			const AssetName<Rendering::StaticMeshData> Monk_0 = AssetName<Rendering::StaticMeshData>(AsHash(2841434648));
		};
		const StaticMeshes smsh;
		struct AnimatedMeshes
		{
			const AssetName<Rendering::AnimatedMeshData> Monk_1 = AssetName<Rendering::AnimatedMeshData>(AsHash(2848250392));
		};
		const AnimatedMeshes amsh;
		struct Materials
		{
			const AssetName<Rendering::MaterialData> MI_0 = AssetName<Rendering::MaterialData>(AsHash(1740916818));
			const AssetName<Rendering::MaterialData> Monk_0 = AssetName<Rendering::MaterialData>(AsHash(2841434648));
			const AssetName<Rendering::MaterialData> Monk_1 = AssetName<Rendering::MaterialData>(AsHash(2848250392));
		};
		const Materials mat;
		struct Skeletons
		{
			const AssetName<Rendering::SkeletonData> Monk_1 = AssetName<Rendering::SkeletonData>(AsHash(2848250392));
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Attack = AssetName<Rendering::SkeletonAnimationData>(AsHash(2942862197));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Attack2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(282426180));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Death = AssetName<Rendering::SkeletonAnimationData>(AsHash(3032097419));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(3157081844));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Idle_Attacking = AssetName<Rendering::SkeletonAnimationData>(AsHash(1013453903));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_PickUp = AssetName<Rendering::SkeletonAnimationData>(AsHash(575569872));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_RecieveHit = AssetName<Rendering::SkeletonAnimationData>(AsHash(1217261808));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_RecieveHit_Attacking = AssetName<Rendering::SkeletonAnimationData>(AsHash(2017475260));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Roll = AssetName<Rendering::SkeletonAnimationData>(AsHash(1151184629));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Run = AssetName<Rendering::SkeletonAnimationData>(AsHash(3006183812));
			const AssetName<Rendering::SkeletonAnimationData> Monk_1_CharacterArmature_Walk = AssetName<Rendering::SkeletonAnimationData>(AsHash(3492306679));
		};
		const SkeletonAnimations sanim;
		struct Shaders
		{
			const AssetName<Rendering::ShaderData> Debug = AssetName<Rendering::ShaderData>(AsHash(1039867416));
			const AssetName<Rendering::ShaderData> Static = AssetName<Rendering::ShaderData>(AsHash(1817995711));
			const AssetName<Rendering::ShaderData> Skinned = AssetName<Rendering::ShaderData>(AsHash(3797269510));

			const std::array<AssetName<Rendering::ShaderData>, 3> All = {
				Debug,
				Static,
				Skinned};

		};
		const Shaders shd;

		// manually added to test - also need a way to these out!
		struct Entities
		{
			const AssetName<EntityData> Test = AssetName<EntityData>(AsHash(1));
		};
		const Entities ent;
	};
	const Assets Ast;
	}
