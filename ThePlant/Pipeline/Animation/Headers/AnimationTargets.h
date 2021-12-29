#pragma once



namespace Application {
namespace Animation {
    // this is how we differentiate between Float3's - by specifying what attribute they refer to
    enum class TargetAttribute
    {
        Position,
        Scale,
        Rotation,
    };
}// namespace Animation
}// namespace Application