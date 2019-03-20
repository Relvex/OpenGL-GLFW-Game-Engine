#include "pch.h"
#include <GL/glew.h>
#include "RawModel.h"
#include "Loader.h"
#include <vector>

int Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttribute(int attributeNumber, std::vector<float> data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

RawModel Loader::loadToVAO(std::vector<float> positions)
{
	int vaoID = createVAO();
	storeDataInAttribute(0, positions);
	unbindVAO();
	RawModel rawModel(vaoID, positions.size());
	return rawModel;
}