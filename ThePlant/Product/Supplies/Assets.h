
#pragma once

#include <array>

#include "Data/Headers/AssetType.h"
#include "Data/Headers/AssetName.h"

#include "CustomAssets.h"

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
		};
		const SimpleModels spmdl;
		struct StaticModels
		{
			const AssetName<Rendering::StaticModelData> MI_0 = AssetName<Rendering::StaticModelData>(AsHash(1740916818));
		};
		const StaticModels smdl;
		struct AnimatedModels
		{
			const AssetName<Rendering::AnimatedModelData> Woman_0 = AssetName<Rendering::AnimatedModelData>(AsHash(3593970672));
			const AssetName<Rendering::AnimatedModelData> Chicken_0 = AssetName<Rendering::AnimatedModelData>(AsHash(4037262318));
			const AssetName<Rendering::AnimatedModelData> Chicken_1 = AssetName<Rendering::AnimatedModelData>(AsHash(4034640878));
			const AssetName<Rendering::AnimatedModelData> Chicken_2 = AssetName<Rendering::AnimatedModelData>(AsHash(3908287470));
			const AssetName<Rendering::AnimatedModelData> Eagle_0 = AssetName<Rendering::AnimatedModelData>(AsHash(590873103));
			const AssetName<Rendering::AnimatedModelData> Eagle_1 = AssetName<Rendering::AnimatedModelData>(AsHash(585105935));
			const AssetName<Rendering::AnimatedModelData> Eagle_2 = AssetName<Rendering::AnimatedModelData>(AsHash(646447631));
			const AssetName<Rendering::AnimatedModelData> Eagle_3 = AssetName<Rendering::AnimatedModelData>(AsHash(640680463));
		};
		const AnimatedModels amdl;
		struct SimpleMeshes
		{
			const AssetName<Rendering::SimpleMeshData> MI_0 = AssetName<Rendering::SimpleMeshData>(AsHash(1740916818));
		};
		const SimpleMeshes spmsh;
		struct StaticMeshes
		{
			const AssetName<Rendering::StaticMeshData> MI_0 = AssetName<Rendering::StaticMeshData>(AsHash(1740916818));
		};
		const StaticMeshes smsh;
		struct AnimatedMeshes
		{
			const AssetName<Rendering::AnimatedMeshData> Woman_0 = AssetName<Rendering::AnimatedMeshData>(AsHash(3593970672));
			const AssetName<Rendering::AnimatedMeshData> Chicken_0 = AssetName<Rendering::AnimatedMeshData>(AsHash(4037262318));
			const AssetName<Rendering::AnimatedMeshData> Chicken_1 = AssetName<Rendering::AnimatedMeshData>(AsHash(4034640878));
			const AssetName<Rendering::AnimatedMeshData> Chicken_2 = AssetName<Rendering::AnimatedMeshData>(AsHash(3908287470));
			const AssetName<Rendering::AnimatedMeshData> Eagle_0 = AssetName<Rendering::AnimatedMeshData>(AsHash(590873103));
			const AssetName<Rendering::AnimatedMeshData> Eagle_1 = AssetName<Rendering::AnimatedMeshData>(AsHash(585105935));
			const AssetName<Rendering::AnimatedMeshData> Eagle_2 = AssetName<Rendering::AnimatedMeshData>(AsHash(646447631));
			const AssetName<Rendering::AnimatedMeshData> Eagle_3 = AssetName<Rendering::AnimatedMeshData>(AsHash(640680463));
		};
		const AnimatedMeshes amsh;
		struct Materials
		{
			const AssetName<Rendering::MaterialData> MI_0 = AssetName<Rendering::MaterialData>(AsHash(1740916818));
			const AssetName<Rendering::MaterialData> Woman_0 = AssetName<Rendering::MaterialData>(AsHash(3593970672));
			const AssetName<Rendering::MaterialData> Chicken_0 = AssetName<Rendering::MaterialData>(AsHash(4037262318));
			const AssetName<Rendering::MaterialData> Chicken_1 = AssetName<Rendering::MaterialData>(AsHash(4034640878));
			const AssetName<Rendering::MaterialData> Chicken_2 = AssetName<Rendering::MaterialData>(AsHash(3908287470));
			const AssetName<Rendering::MaterialData> Eagle_0 = AssetName<Rendering::MaterialData>(AsHash(590873103));
			const AssetName<Rendering::MaterialData> Eagle_1 = AssetName<Rendering::MaterialData>(AsHash(585105935));
			const AssetName<Rendering::MaterialData> Eagle_2 = AssetName<Rendering::MaterialData>(AsHash(646447631));
			const AssetName<Rendering::MaterialData> Eagle_3 = AssetName<Rendering::MaterialData>(AsHash(640680463));
		};
		const Materials mat;
		struct Skeletons
		{
			const AssetName<Rendering::SkeletonData> Woman_0 = AssetName<Rendering::SkeletonData>(AsHash(3593970672));
			const AssetName<Rendering::SkeletonData> Chicken_0 = AssetName<Rendering::SkeletonData>(AsHash(4037262318));
			const AssetName<Rendering::SkeletonData> Chicken_1 = AssetName<Rendering::SkeletonData>(AsHash(4034640878));
			const AssetName<Rendering::SkeletonData> Chicken_2 = AssetName<Rendering::SkeletonData>(AsHash(3908287470));
			const AssetName<Rendering::SkeletonData> Eagle_0 = AssetName<Rendering::SkeletonData>(AsHash(590873103));
			const AssetName<Rendering::SkeletonData> Eagle_1 = AssetName<Rendering::SkeletonData>(AsHash(585105935));
			const AssetName<Rendering::SkeletonData> Eagle_2 = AssetName<Rendering::SkeletonData>(AsHash(646447631));
			const AssetName<Rendering::SkeletonData> Eagle_3 = AssetName<Rendering::SkeletonData>(AsHash(640680463));
		};
		const Skeletons skl;
		struct SkeletonAnimations
		{
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Death = AssetName<Rendering::SkeletonAnimationData>(AsHash(4259411171));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(4140853032));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump = AssetName<Rendering::SkeletonAnimationData>(AsHash(2420364265));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Jump2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(2348057118));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_PickUp = AssetName<Rendering::SkeletonAnimationData>(AsHash(2634831132));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Punch = AssetName<Rendering::SkeletonAnimationData>(AsHash(2816760887));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Running = AssetName<Rendering::SkeletonAnimationData>(AsHash(127888874));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_SitIdle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2289128976));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Sitting = AssetName<Rendering::SkeletonAnimationData>(AsHash(437013649));
			const AssetName<Rendering::SkeletonAnimationData> Woman_0_Armature_Walking = AssetName<Rendering::SkeletonAnimationData>(AsHash(460649925));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(4146678407));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(3725065295));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2951178086));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(809336635));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_caminar = AssetName<Rendering::SkeletonAnimationData>(AsHash(577146784));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(2222574469));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2609178041));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(980737063));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(4131041682));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_0_Esqueleto_PoseLib = AssetName<Rendering::SkeletonAnimationData>(AsHash(1508527250));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(4146980487));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(3725054439));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2956683110));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(809337307));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_caminar = AssetName<Rendering::SkeletonAnimationData>(AsHash(576350624));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(2221127119));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2657215929));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(980742927));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(2251993102));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_1_Esqueleto_PoseLib = AssetName<Rendering::SkeletonAnimationData>(AsHash(1510553234));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(4148241031));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(3725014207));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(3154077542));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(809361403));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_caminar = AssetName<Rendering::SkeletonAnimationData>(AsHash(574684064));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_EsqueletoAction = AssetName<Rendering::SkeletonAnimationData>(AsHash(2221128945));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2189616569));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_idle2 = AssetName<Rendering::SkeletonAnimationData>(AsHash(980685847));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_picotear = AssetName<Rendering::SkeletonAnimationData>(AsHash(1446687298));
			const AssetName<Rendering::SkeletonAnimationData> Chicken_2_Esqueleto_PoseLib = AssetName<Rendering::SkeletonAnimationData>(AsHash(1509982354));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_0_EagleArmature_Flying = AssetName<Rendering::SkeletonAnimationData>(AsHash(3753696111));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_0_EagleArmature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(3984293124));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_0_Eagle_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2338519011));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_1_EagleArmature_Flying = AssetName<Rendering::SkeletonAnimationData>(AsHash(3753695547));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_1_EagleArmature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(3178986783));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_1_Eagle_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2338519603));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_2_EagleArmature_Flying = AssetName<Rendering::SkeletonAnimationData>(AsHash(3753685415));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_2_EagleArmature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(3447422205));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_2_Eagle_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2338516867));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_3_EagleArmature_Flying = AssetName<Rendering::SkeletonAnimationData>(AsHash(3753684691));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_3_EagleArmature_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(494632183));
			const AssetName<Rendering::SkeletonAnimationData> Eagle_3_Eagle_Idle = AssetName<Rendering::SkeletonAnimationData>(AsHash(2338517459));
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

	};
	const Assets Ast;
	}
