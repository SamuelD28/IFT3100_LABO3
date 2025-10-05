#include <array>
#include <shape.hpp>

float *shape::triangle::getVertices()
{
	auto vertices = new float[6];
	vertices[0] = first.x;
	vertices[1] = first.y;
	vertices[2] = second.x;
	vertices[3] = second.y;
	vertices[4] = third.x;
	vertices[5] = third.y;
	return vertices;
}

// public:
// 	float *getIndices()
// 	{
// 		float *indices = new float[3];
// 		indices[0] = 0;
// 		indices[1] = 1;
// 		indices[2] = 2;
// 		return indices;
// 	}
// };

// public:
// 	float *getVertices()
// 	{
// 		float *vertices = new float[8];
// 		vertices[0] = lowerLeft.x;
// 		vertices[1] = lowerLeft.y;
// 		vertices[2] = lowerRight.x;
// 		vertices[3] = lowerRight.y;
// 		vertices[4] = upperLeft.x;
// 		vertices[5] = upperLeft.y;
// 		vertices[6] = upperRight.x;
// 		vertices[7] = upperLeft.x;
// 		return vertices;
// 	}

// public:
// 	float *getIndices()
// 	{
// 		float *indices = new float[6];
// 		indices[0] = 0;
// 		indices[1] = 1;
// 		indices[2] = 2;
// 		indices[3] = 2;
// 		indices[4] = 3;
// 		indices[5] = 1;
// 		return indices;
// 	}
