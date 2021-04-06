#include "ApplicationManagement/Animation/Headers/Animatable.h"


namespace Application
{
	namespace Animation
	{
		Animatable::Animatable()
		{}

		Core::Ptr<AnimationnMixer> Animatable::GetMixer()
		{
			if (_mixer == nullptr)
			{
				CreateMixer();
			}

			return _mixer.get();
		}
	}
}