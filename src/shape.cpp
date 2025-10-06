#include <array>
#include <shape.hpp>
#include <glad.h>

std::array<float, 6> shape::triangle::getVertices()
{
	auto vertices = std::array<float, 6>();
	// Line 1
	vertices[0] = first.x;
	vertices[1] = first.y;
	// Line 2
	vertices[2] = second.x;
	vertices[3] = second.y;
	// Line 3
	vertices[4] = third.x;
	vertices[5] = third.y;
	return vertices;
}

std::array<unsigned int, 3> shape::triangle::getIndices(unsigned int offset)
{
	auto indices = std::array<unsigned int, 3>();
	indices[0] = 0 + offset;
	indices[1] = 1 + offset;
	indices[2] = 2 + offset;
	return indices;
}

void shape::triangle::draw(unsigned int programId)
{
	auto uniformId = glGetUniformLocation(programId, "Color");
	if (uniformId == -1)
	{
		return;
	}

	glUniform4f(uniformId, this->color[0], this->color[1], this->color[2], this->color[3]);
}