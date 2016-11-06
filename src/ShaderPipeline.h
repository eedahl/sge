#pragma once
#include <vector>

using GLint = int;
using GLuint = unsigned int;
using GLenum = unsigned int;

namespace sge {

	class Shader
	{
	public:
		Shader() = delete;
		Shader(std::string fileName, GLenum type);
		void setID(GLuint id) {this->id = id;};
		GLuint getID() const {return id;};
		void compile();

	private:
		GLuint id;
		std::string source;
		GLint compiled;
	};

	class Program
	{
	public:
		Program(std::string vertexShaderPath, std::string fragmentShaderPath);
		void attachAndLink();
		void use() const;
		void init();
		GLuint getID() const;

	private:
		GLuint id;
		std::vector<Shader> shaders;
		GLint linked;
	};
}