#pragma once
#include "iostream"
#include "string"
#include <glad/glad.h>
using namespace std;
namespace Renderer {
	class ShaderProgram {
		public:
			ShaderProgram(const string& vertexShader, const string& fragmentShader);
			bool IsCompiled() const { return _isCompiled; }
			void Use() const;

			ShaderProgram() = delete;
			ShaderProgram(ShaderProgram&) = delete;
			ShaderProgram& operator=(const ShaderProgram&) = delete;
			ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
			ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
			~ShaderProgram();
		private:
			bool CreateShader(const string& source, const GLuint shaderType, GLuint& shaderID);
			bool _isCompiled = false;
			GLuint _ID = 0;
	};
}