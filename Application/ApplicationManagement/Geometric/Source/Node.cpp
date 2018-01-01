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
			Container::Update(dt);
			
			for (auto& child : Children)
			{
				child->Update(dt);
			}
		}

		void Node::Render(Renderer& renderer, Float4x4 transformationMatrix)
		{
			// pass down modified transformation matrix
			auto modifiedTransformationMatrix = Transformation.GetTransformationMatrix() * transformationMatrix;

			for (auto& child : Children)
			{
				child->Render(renderer, modifiedTransformationMatrix);
			}

			Container::Render(renderer, transformationMatrix);
		}

		void Node::AddChild(SharedPtr<Node> newChild)
		{
			if (newChild->Parent != nullptr && newChild->Parent != this)
			{
				newChild->Parent->RemoveChild(newChild);
			}

			if (newChild->Parent != this)
			{
				newChild->Parent = this;
				Push(Children, move(newChild));
			}
		}

		void Node::RemoveChild(SharedPtr<Node> oldChild)
		{
			Remove(Children, oldChild);
			oldChild->Parent = nullptr;
		}
	}
}