#include "Factory/Rendering/Headers/ShaderExport.h"

#include "Core/Headers/Hash.h"

#include "Core/Logging/Logger.h"

#include "Core/IO/Headers/Folder.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"
#include "Data/Rendering/Headers/ShaderData.h"

#include "Factory/Headers/ExportData.h"

namespace Data
{
	namespace DataExport
	{
		namespace
		{
			const std::string SHADER_EXPORT = "Shader Export";
		}
        
        void DirectShaders(Core::Ptr<Core::IO::File> directAssets, const std::vector<std::string>& shaders)
		{
			ExportDirectReference_Open("Shaders", "shd", directAssets);

			for (auto& shader : shaders)
			{
                directAssets->Write("\t\t\tconst AssetName<Rendering::ShaderData> " + shader + " = AssetName<Rendering::ShaderData>(AsHash(" + to_string(HashValue(shader)) + "));");
                directAssets->CreateNewLine();
			}

			directAssets->CreateNewLine();
			directAssets->Write("\t\t\tconst std::array<AssetName<Rendering::ShaderData>, " + std::to_string(shaders.size()) + "> All = {");
			directAssets->CreateNewLine();
			int index = 0;
			for (auto& shader : shaders)
			{
                directAssets->Write("\t\t\t\t" + shader + (index < shaders.size() - 1 ? "," : "};"));
                directAssets->CreateNewLine();
				++index;
			}
			directAssets->CreateNewLine();

			ExportDirectReference_Close("Shaders", "shd", directAssets);
		}
        
        template <typename SHADER_TYPE>
        void CreateShader(Core::Ptr<Core::IO::File> importFile, Core::Ptr<Core::IO::File> exportFile)
        {
            SHADER_TYPE shaderData;

			shaderData.shaderCode = importFile->GetFullText();

			auto shaderAsJSON = Core::Serialize<Core::Serialization::Format::JSON>(shaderData);

			if (!exportFile->FileStream.is_open())
			{
				CORE_LOG(SHADER_EXPORT, "Could not open file <<" + exportFile->GetFullPath() + ">>");
				return;
			}

			exportFile->Write(shaderAsJSON.ToString(Core::Serialization::Format::Style::Readable));
        }

		void CreateShader(Config& config, Core::Ptr<Core::IO::File> directAssets, const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
        {
            // Vertex
            FilePath vertexImportPath = FilePath{ GetCWD() + config.getValue("importPath") + config.getValue("shadersImportPath") + config.getValue("vertexShadersImportPath"), vertexShader + ".vshd" };
            File vertexImport = File(vertexImportPath, std::ios::in);
            vertexImport.Open();

            Core::Hash vertexHash = HashValue(vertexShader);
			FilePath vertexExportPath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath") + config.getValue("vertexShadersExportPath"), to_string(vertexHash) + ".vshd" };
			File vertexExport = File(vertexExportPath, std::ios::out);
			vertexExport.Open();

            CreateShader<Data::Rendering::VertexShaderData>(&vertexImport, &vertexExport);
            vertexImport.Close();
            vertexExport.Close();
            
            // Fragment
            FilePath fragmentImportPath = FilePath{ GetCWD() + config.getValue("importPath") + config.getValue("shadersImportPath") + config.getValue("fragmentShadersImportPath"), fragmentShader + ".fshd" };
            File fragmentImport = File(fragmentImportPath, std::ios::in);
            fragmentImport.Open();

            Core::Hash fragmentHash = HashValue(fragmentShader);
			FilePath fragmentExportPath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath") + config.getValue("fragmentShadersExportPath"), to_string(fragmentHash) + ".fshd" };
			File fragmentExport = File(fragmentExportPath, std::ios::out);
			fragmentExport.Open();

            CreateShader<Data::Rendering::FragmentShaderData>(&fragmentImport, &fragmentExport);
            fragmentImport.Close();
            fragmentExport.Close();

            // Combination
            Core::Hash shaderHash = HashValue(name);
            FilePath shaderExportPath = FilePath{ GetCWD() + config.getValue("exportPath") + config.getValue("shadersExportPath"), to_string(shaderHash) + ".shd" };
            File shaderExport = File(shaderExportPath, std::ios::out);
            shaderExport.Open();

            Data::Rendering::ShaderData shader;
            shader.name = name;
            shader.vertexShader = vertexHash;
            shader.fragmentShader = fragmentHash;

			auto shaderAsJSON = Core::Serialize<Core::Serialization::Format::JSON>(shader);
			shaderExport.Write(shaderAsJSON.ToString(Core::Serialization::Format::Style::Readable));
            shaderExport.Close();
        }

        void ExportShadersInFolder(Config& config, Core::Ptr<Core::IO::File> directAssets, std::string folder)
        {
			std::vector<std::string> shaders;

			// in the future, this should likely also reference a database that is used to get specific file locations
			Core::IO::FilePath listPath = Core::IO::FilePath{ folder, config.getValue("shadersFile") };
			Core::IO::File listFile = Core::IO::File(listPath, std::ios::in);
			listFile.Open();

			try
			{
				std::string line = listFile.GetLine();

				Core::IO::IOSStreamChar lineStream(line);

				int numShaders;
				lineStream >> numShaders;

				int shadersCreated = 0;
				while (shadersCreated < numShaders)
				{
					std::string line = listFile.GetLine();

					Core::IO::IOSStreamChar lineStream(line);

					std::string name;
					std::string vertex;
					std::string fragment;

					lineStream >> name;
					lineStream >> vertex;
					lineStream >> fragment;

                    shaders.push_back(name);
					CreateShader(config, directAssets, name, vertex, fragment);

					shadersCreated++;
				}

                DirectShaders(directAssets, shaders);
			}
			catch (Core::Exception& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			listFile.Close();
        }
	}
}