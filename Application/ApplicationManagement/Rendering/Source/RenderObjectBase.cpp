#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(RenderManager& manager, Ptr<const Transform> renderTransform, Color color)
			: ObjectColor(color)
			, Manager(manager)
			, RenderTransform(renderTransform)
		{
		}

		RenderObjectBase::~RenderObjectBase()
		{

		}

		void RenderObjectBase::Update(Second dt)
		{
			// this will be used to handle animations and the like
		}

		void RenderObjectBase::Render(const Float4x4& mvp, const Color& color) const
		{
			auto renderMVP = mvp * RenderTransform->GetTransformationMatrix();

			// debug
			/*
			Color dummyColor = BLACK;
			Manager.ObjectShaderManager.DefaultShader.Prepare(renderMVP, dummyColor);
			DebugVao.Bind();

			Manager.ObjectRenderer.DrawTriangles(DebugVertices.size());

			DebugVao.Unbind();
			Manager.ObjectShaderManager.DefaultShader.CleanUp();

			Color dummyColor2 = WHITE;
			Manager.ObjectShaderManager.DefaultShader.Prepare(renderMVP, dummyColor2);
			DebugVao.Bind();

			Manager.ObjectRenderer.DrawLines(DebugVertices.size());

			DebugVao.Unbind();
			Manager.ObjectShaderManager.DefaultShader.CleanUp();
			*/
			// end of debug
			
			Prepare(renderMVP, color);
			Draw();
			CleanUp();
		}

		void RenderObjectBase::Draw() const
		{
			Manager.ObjectRenderer.Draw(this);
		}
	}
}