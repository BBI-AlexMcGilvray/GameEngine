#pragma once

namespace Application {
namespace Time {
  struct TimeSettings
  {
      double timeScale = 1.0;
      double maxTimeStep =  0.0167; // 1 frame if we do 60 frames per second (or 167 milliseconds);
      bool fixedTimeStep = true;
  };

  constexpr TimeSettings FIXED_60FPS = { 1.0, 0.0167, true };
  constexpr TimeSettings FIXED_30FPS = { 1.0, 0.0334, true };
  constexpr TimeSettings UNCAPPED = { 1.0, 0.0, false };
}// namespace Time
}// namespace Application