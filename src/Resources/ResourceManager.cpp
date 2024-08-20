#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const string& executablePath) {
	size_t found = executablePath.find_last_of("/\\");
	_path = executablePath.substr(0, found);
}
shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath)
{
	string vertexString = GetFileString(vertexPath);
	if (vertexString.empty()) {
		cerr << "No vertex shader" << endl;
		return nullptr;
	}
	string fragmentString = GetFileString(fragmentPath);
	if (fragmentString.empty()) {
		cerr << "No fragment shader" << endl;
		return nullptr;
	}

	shared_ptr<Renderer::ShaderProgram>& shaderProgram = _shaderPrograms.emplace(shaderName, make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (shaderProgram->IsCompiled()) {
		return shaderProgram;
	}
	cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << endl;
	return nullptr;
}
shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const string& shaderName)
{
	ShaderProgramMap::const_iterator it = _shaderPrograms.find(shaderName);
	if (it != _shaderPrograms.end()) {
		return it->second;
	}
	cerr << "Can't find the shader program: " << shaderName << endl;
	return nullptr;
}
string ResourceManager::GetFileString(const string& relativeFilePath) {
	ifstream f;
	f.open(_path + "/" + relativeFilePath.c_str(), ios::in | ios::binary);
	if (!f.is_open()) {
		cerr << "Failed to open file: " << relativeFilePath << endl;
		return "";
	}
	stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}