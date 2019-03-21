#include "pch.h"
#include <GL/glew.h>

#include "RawModel.h"
#include "GLUtils.h"

#include <vector>

void GLUtils::bindIndicesVBO(std::vector<unsigned int> indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void GLUtils::bindPositionsVBO(std::vector<float> positions)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

RawModel GLUtils::loadToVAO(std::vector<float> positions, std::vector<unsigned int> indices)
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	bindIndicesVBO(indices);

	bindPositionsVBO(positions);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return RawModel(vaoID, indices.size());
}