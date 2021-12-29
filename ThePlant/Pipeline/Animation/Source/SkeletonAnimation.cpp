#pragma once

#include <array>
#include <vector>

#include "Pipeline/Animation/Headers/ChannelTypes.h"
#include "Pipeline/Animation/Headers/AnimationTargets.h"
#include "Pipeline/Animation/Headers/SkeletonAnimation.h"

namespace Application {
namespace Animation {
    std::array<AnimationCurve, 3> CreatePositionAnimationCurves(const std::vector<Data::Rendering::PositionFrameData>& positionFrames)
    {
        std::array<std::vector<Keyframe>, 3> keyframes;

        for (const auto& frame : positionFrames)
        {
            keyframes[0].push_back(Keyframe(frame.time, frame.position.X));
            keyframes[1].push_back(Keyframe(frame.time, frame.position.Y));
            keyframes[2].push_back(Keyframe(frame.time, frame.position.Z));
        }

        std::array<AnimationCurve, 3> curves = { keyframes[0], keyframes[1], keyframes[2] };

        return curves;
    }

    void AddPositionChannels(Animation& skeletonAnimation, const Core::Hash& target, const std::vector<Data::Rendering::PositionFrameData>& positionFrames)
    {
        std::array<AnimationCurve, 3> positionCurves = CreatePositionAnimationCurves(positionFrames);

        Channel_Float3 positionX(&Core::Math::Float3::X, positionCurves[0]);
        Channel_Float3 positionY(&Core::Math::Float3::Y, positionCurves[1]);
        Channel_Float3 positionZ(&Core::Math::Float3::Z, positionCurves[2]);

        skeletonAnimation.AddObjectChannel<Core::Math::Float3, TargetAttribute::Position>(target, { positionX, positionY, positionZ });
    }

    std::array<AnimationCurve, 3> CreateScaleAnimationCurves(const std::vector<Data::Rendering::ScaleFrameData>& scaleFrames)
    {
        std::array<std::vector<Keyframe>, 3> keyframes;

        for (const auto& frame : scaleFrames)
        {
            keyframes[0].push_back(Keyframe(frame.time, frame.scale.X));
            keyframes[1].push_back(Keyframe(frame.time, frame.scale.Y));
            keyframes[2].push_back(Keyframe(frame.time, frame.scale.Z));
        }

        std::array<AnimationCurve, 3> curves = { keyframes[0], keyframes[1], keyframes[2] };

        return curves;
    }

    void AddScaleChannels(Animation& skeletonAnimation, const Core::Hash& target, const std::vector<Data::Rendering::PositionFrameData>& scaleFrames)
    {
        std::array<AnimationCurve, 3> scaleCurves = CreateScaleAnimationCurves(scaleFrames);

        Channel_Float3 scaleX(&Core::Math::Float3::X, scaleCurves[0]);
        Channel_Float3 scaleY(&Core::Math::Float3::Y, scaleCurves[1]);
        Channel_Float3 scaleZ(&Core::Math::Float3::Z, scaleCurves[2]);

        skeletonAnimation.AddObjectChannel<Core::Math::Float3, TargetAttribute::Scale>(target, { scaleX, scaleY, scaleZ });
    }

    std::array<AnimationCurve, 4> CreateRotationAnimationCurves(const std::vector<Data::Rendering::RotationFrameData>& rotationFrames)
    {
        std::array<std::vector<Keyframe>, 4> keyframes;

        for (const auto& frame : rotationFrames)
        {
            keyframes[0].push_back(Keyframe(frame.time, frame.rotation.X));
            keyframes[1].push_back(Keyframe(frame.time, frame.rotation.Y));
            keyframes[2].push_back(Keyframe(frame.time, frame.rotation.Z));
            keyframes[3].push_back(Keyframe(frame.time, frame.rotation.Z));
        }

        std::array<AnimationCurve, 4> curves = { keyframes[0], keyframes[1], keyframes[2], keyframe[3] };

        return curves;
    }

    void AddRotationChannels(Animation& skeletonAnimation, const Core::Hash& target, const std::vector<Data::Rendering::PositionFrameData>& rotationFrames)
    {
        std::array<AnimationCurve, 4> rotationCurves = CreateRotationAnimationCurves(rotationFrames);

        Channel_FQuat rotationX(&Core::Math::FQuaternion::X, rotationCurves[0]);
        Channel_FQuat rotationY(&Core::Math::FQuaternion::Y, rotationCurves[1]);
        Channel_FQuat rotationZ(&Core::Math::FQuaternion::Z, rotationCurves[2]);
        Channel_FQuat rotationW(&Core::Math::FQuaternion::W, rotationCurves[3]);

        skeletonAnimation.AddObjectChannel<Core::Math::FQuaternion, TargetAttribute::Rotation>(target, { rotationX, rotationY, rotationZ, rotationW });
    }

    Animation CreateAnimation(Data::AssetManager& assetManager, const Data::AssetName<Data::Rendering::SkeletonAnimationData>& asset)
    {
        Data::AssetData<Data::Rendering::SkeletonAnimationData> assetData = assetManager.getAssetData(asset);

        Animation skeletonAnimation(Core::HashValue(assetData->name), assetData->duration);

        for (const auto& boneAnimationData : assetData->boneAnimations)
        {
            // not using preBehaviour or postBehaviour - should later
            AddPositionChannels(skeletonAnimation, Core::HashValue(boneAnimationData->name), assetData->positionChannel);
            AddScaleChannels(skeletonAnimation, Core::HashValue(boneAnimationData->name), assetData->scaleChannel);
            AddRotationChannels(skeletonAnimation, Core::HashValue(boneAnimationData->name), assetData->rotationChannel);
        }

        return skeletonAnimation;
    }
}// namespace Animation
}// namespace Application