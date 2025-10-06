#include <array>
#include <shape.hpp>
#include <glad.h>

std::array<float, 12> shape::triangle::getVertices()
{
	auto vertices = std::array<float, 12>();
	// Line 1
	vertices[0] = first.x;
	vertices[1] = first.y;
	vertices[2] = second.x;
	vertices[3] = second.y;
	// Line 2
	vertices[4] = second.x;
	vertices[5] = second.y;
	vertices[6] = third.x;
	vertices[7] = third.y;
	// Line 3
	vertices[8] = third.x;
	vertices[9] = third.y;
	vertices[10] = first.x;
	vertices[11] = first.y;
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