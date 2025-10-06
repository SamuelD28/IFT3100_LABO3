#include <array>
#include <shape.hpp>
#include <glad.h>

float *shape::triangle::getVertices()
{
	auto vertices = new float[6];
	// Index 0
	vertices[0] = first.x;
	vertices[1] = first.y;
	// Index 1
	vertices[2] = second.x;
	vertices[3] = second.y;
	// Index 2
	vertices[4] = third.x;
	vertices[5] = third.y;
	return vertices;
}

unsigned int *shape::triangle::getIndices()
{
	unsigned int *indices = new unsigned int[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	return indices;
}

void shape::triangle::draw(unsigned int programId)
{
	auto uniformId = glGetUniformLocation(programId, "Color");
	if (uniformId == -1)
	{
		return;
	}

	glUniform4f(uniformId, 1.0f, 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
}

float *shape::plane::getVertices()
{
	auto vertices = new float[6];
	// Index 0
	vertices[0] = lowerLeft.x;
	vertices[1] = lowerLeft.y;
	// Index 1
	vertices[2] = lowerLeft.x;
	vertices[3] = lowerLeft.y;
	// Index 2
	vertices[4] = lowerLeft.x;
	vertices[5] = lowerLeft.y;
	return vertices;
}

unsigned int *shape::plane::getIndices()
{
	unsigned int *indices = new unsigned int[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	return indices;
}

void shape::plane::draw(unsigned int programId)
{
	auto uniformId = glGetUniformLocation(programId, "Color");
	if (uniformId == -1)
	{
		return;
	}

	glUniform4f(uniformId, 1.0f, 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
}