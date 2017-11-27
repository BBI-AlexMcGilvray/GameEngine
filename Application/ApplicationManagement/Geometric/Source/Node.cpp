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
			for (auto& child : Children)
			{
				child->Update(dt);
			}
		}

		void Node::Render(const Renderer& renderer, Float4x4 transformationMatrix)
		{
			// pass down modified transformation matrix
			auto modifiedTransformationMatrix = Transformation.GetTransformationMatrix() * transformationMatrix;

			for (auto& child : Children)
			{
				child->Render(renderer, modifiedTransformationMatrix);
			}
		}

		void Node::AddChild(Ptr<Node> newChild)
		{
			if (newChild->Parent != nullptr && newChild->Parent != this)
			{
				newChild->Parent->RemoveChild(newChild);
			}

			if (newChild->Parent != this)
			{
				newChild->Parent = this;
				Push(Children, newChild);
			}
		}

		void Node::RemoveChild(Ptr<Node> oldChild)
		{
			Remove(Children, oldChild);
			oldChild->Parent = nullptr;
		}
	}
}