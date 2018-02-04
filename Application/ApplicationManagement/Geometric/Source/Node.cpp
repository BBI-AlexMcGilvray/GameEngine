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

		void Node::Render(Renderer& renderer, Float4x4 transformationMatrix) const
		{
			// pass down modified transformation matrix
			auto modifiedTransformationMatrix = Transformation.GetTransformationMatrix() * transformationMatrix;

			for (auto& child : Children)
			{
				child->Render(renderer, modifiedTransformationMatrix);
			}

			ContainerBase::Render(renderer, transformationMatrix);
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