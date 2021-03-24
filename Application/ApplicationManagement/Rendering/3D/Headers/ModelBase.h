#pragma once

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleModelData.h"

namespace Application
{
	namespace Rendering
	{
		class SimpleMeshBase;

		// holds the mesh, texture(s), and shader that a model uses
		struct ModelBase : public Geometric::ContentBase
		{
			Data::AssetData<Data::Rendering::SimpleModelData> Data;
			//Material Material;
			//SimpleMeshBase Mesh;

			// this should be loading up the model data instead of the mesh data
			ModelBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleModelData> asset);

			//Core::size GetVertexCount() const override;

			void Initialize() override;
			void Start() override;
			void Update(Core::Second dt) override;
			void End() override;
			void CleanUp() override;

		protected:
			//ObjectShader& Shader;

			//void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const override;
			//void CleanUp() const override;

		private:
			// do we need this?
			Core::Ptr<Core::Geometric::Transform> _transform;

			ComponentPtr<MaterialComponent> _materialComponent;
			ComponentPtr<Render> _renderComponent;
		};
	}
}