#pragma once
#include "string"
#include "memory"
#include "map"
using namespace std;
namespace Renderer {
	class ShaderProgram;
}
class ResourceManager {
public:
	ResourceManager(const string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	shared_ptr<Renderer::ShaderProgram> LoadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath);
	shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const string& shaderName);
private:
	typedef map < const string, shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap _shaderPrograms;
	string _path;

	string GetFileString(const string& relativeFilePath);
};