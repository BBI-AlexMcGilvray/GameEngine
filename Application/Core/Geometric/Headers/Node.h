#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/Geometric/Headers/Content.h"

namespace Core
{
	namespace Geometric
	{
		// a recursive struct to hold elements in a scene
		struct Node
		{
			// need generic functions such as...
			/*
			Node();
			virtual ~Node();
			virtual void Update(Second dt) = 0;
			virtual void Render(Renderer& renderer) = 0;
			*/

		protected:
			SharedPtr<Node> Parent;
			List<SharedPtr<Node>> Children;

			// all functions need to call the equivalent functions on the content, and then all of the children
			Ptr<Content> NodeContents;
		};
	}
}