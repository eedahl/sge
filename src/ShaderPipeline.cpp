#include "ShaderPipeline.h"
#include <GL/glew.h>
#include <iostream>
#include <algorithm>
#include "Utilities.h"

namespace sge
{

Shader::Shader(std::string fileName, GLenum type)
    : source(util::load_text(fileName)),
	  id(glCreateShader(type))
{
    compile();
}

void Shader::compile()//
{
	const auto *c_str = source.c_str();
	glShaderSource(getID(), 1, &c_str, nullptr);
	glCompileShader(getID());
	glGetObjectParameterivARB(getID(), GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_TRUE)
	    std::cout << "Shader compiled successfully." << std::endl;
	else
	    std::cerr << "Failed to compile shader." << std::endl;

}

Program::Program(std::string vertexShaderPath, std::string fragmentShaderPath)
    : id{glCreateProgram()}
{
    shaders.emplace_back(vertexShaderPath, GL_VERTEX_SHADER);
    shaders.emplace_back(fragmentShaderPath, GL_FRAGMENT_SHADER);
}

void Program::attachAndLink()
{
    //std::for_each(std::begin(shaders),std::end(shaders),
    //[&](Shader& s){ glAttachShader(id, s.getID()); });
    
    for (auto &shader : shaders)
    {
       	glAttachShader(id, shader.getID());
    }

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE)
	std::cout << "Program linked successfully." << std::endl;
    else
	std::cout << "Failed to link program." << std::endl;
}

void Program::use() const
{
    std::cout << "Using program" << std::endl;
    glUseProgram(id);
}

void Program::init()
{
    std::cout << "Initializing program." << std::endl;
    attachAndLink();
}

GLuint Program::getID() const
{
    return id;
}
}