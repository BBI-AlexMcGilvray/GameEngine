#include "ApplicationManagement\Geometric\Headers\Node.h"

namespace Application
{
	namespace Geometric
	{
		Node::Node()
		{

		}

		Node::Node(Float3 position, FQuaternion rotation, Float3 scale)
			: Transformation(position, rotation, scale)
		{

		}

		Node::~Node()
		{

		}

		// generic functions that pass calls down to children and contents
		void Node::Update(Second dt)
		{
			ContainerBase::Update(dt);
			
			for (auto& child : Children)
			{
				child->Update(dt);
			}
		}

		void Node::AddChild(SharedPtr<Node> newChild)
		{
			Push(Children, move(newChild));
		}

		void Node::RemoveChild(SharedPtr<Node> oldChild)
		{
			Remove(Children, move(oldChild));
		}
	}
}