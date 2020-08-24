#pragma once

#include "Core/Headers/MapDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Functionality/Headers/Function.h"

#include "Core/Headers/Property.h"

namespace Core
{
	namespace Networking
	{
		enum RemoteType
		{
			Procedure,
			Data
		};

		class NetworkMap
		{
			// map of all remote procedure calls and their Ids
			Map<Hash, Functionality::VoidFunction<Ptr<void>>> _rpcs;

			// map of all remote data synchronization type and their Ids
			Map<Hash, IProperty> _rdss;

		public:
			template <typename ...Ts>
			void Execute(RemoteType type, Hash hash, Ts... args)
			{
				switch (type)
				{
					case RemoteType::Procedure:
					{
						return ExecuteFunction(hash, args...);
					}
					case RemoteType::Data:
					{
						return SynchronizeData(hash, args...);
					}
					default:
					{
						throw exception("Unhandled RemoteType");
					}
				}
			}

		private:
			template <typename ...Ts>
			void ExecuteFunction(Hash hash, Ts... args)
			{
				if (In(_rpcs, hash))
				{
					return _rpcs[hash](args...);
				}

				throw exception("Hash does not exist in _rpcs");
			}

			template <typename ...Ts>
			void SynchronizeData(Hash hash, Ts... args)
			{
				if (In(_rdss, hash))
				{
					return _rdss.SetData(args...);
				}

				throw exception("Hash does not exist in _rdss");
			}
		};
	}
}