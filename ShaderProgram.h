#include <string>

#pragma once
class ShaderProgram
{
public:
	ShaderProgram(const char*, const char*);
	void start(void);
	void stop(void);
	void clean(void);
	void bindAttribute(int, const char*);
private:
	int loadShader(const char*, int);
	int programID;
	int vertexShaderID;
	int fragmentShaderID;
};

