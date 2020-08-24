#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"

namespace Core
{
	class IProperty
	{
	public:
		virtual void SetData(Ptr<void> data) = 0;
		virtual Ptr<void> GetData() = 0;
		virtual uint GetDataSize() = 0;
	};

	template <typename T>
	class Property : IProperty
	{
	private:
		T _data;

	public:
		override void SetData(Ptr<void> data)
		{
			SetData(*(Ptr<T>)data);
		}

		void SetData(T data)
		{
			_data = data;
		}

		override Ptr<void> GetData()
		{
			return &_data;
		}

		T GetData()
		{
			return _data;
		}

		override uint GetDataSize()
		{
			return sizeof(T);
		}
	};
}