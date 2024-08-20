#include "ShaderProgram.h"

namespace Renderer {
	ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader) {
		GLuint vertexShaderID;
		if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
			cerr << "VERTEX SHADER compile time error" << endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			cerr << "FRAGMENT SHADER compile time error" << endl;
			glDeleteShader(vertexShaderID);
			return;
		}
		_ID = glCreateProgram();
		glAttachShader(_ID, vertexShaderID);
		glAttachShader(_ID, fragmentShaderID);
		glLinkProgram(_ID);

		GLint success;
		glGetProgramiv(_ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
			cerr << "ERROR::SHADER: Link time error:\n" << infoLog << endl;
			return;
		}
		_isCompiled = true;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	bool ShaderProgram::CreateShader(const string& source, const GLuint shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr,infoLog);
			cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << endl;
			return false;
		}
		return true;
	}
	void ShaderProgram::Use() const {
		glUseProgram(_ID);
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(_ID);
		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;
	}
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(_ID);
	}
}