#include "pch.h"
#include <GL/glew.h>

#include "ShaderProgram.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

int ShaderProgram::loadShader(const char* path, int type) {
	std::string shaderStr;
	std::ifstream file(path, std::ios::in);

	if (!file.is_open()) {
		std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
	}

	std::string line = "";
	while (!file.eof()) {
		std::getline(file, line);
		shaderStr.append(line + "\n");
	}

	file.close();

	const char* shaderSrc = shaderStr.c_str();

	int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSrc, NULL);
	glCompileShader(shaderID);

	return shaderID;
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	this->vertexShaderID = ShaderProgram::loadShader(vertexPath, GL_VERTEX_SHADER);
	this->fragmentShaderID = ShaderProgram::loadShader(fragmentPath, GL_FRAGMENT_SHADER);
	this->programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);
	bindAttribute(0, "position");
}

void ShaderProgram::start(void) {
	glUseProgram(programID);
}

void ShaderProgram::stop(void) {
	glUseProgram(0);
}

void ShaderProgram::clean(void) {
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(int attribute, const char* variableName) {
	glBindAttribLocation(programID, attribute, variableName);
}