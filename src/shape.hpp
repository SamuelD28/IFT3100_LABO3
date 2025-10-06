#include <array>
#include <vector>

namespace shape
{
	struct point
	{
	public:
		float x = 0;

	public:
		float y = 0;
	};

	struct triangle
	{
	public:
		std::array<float, 4> color;

	public:
		point first;

	public:
		point second;

	public:
		point third;

	public:
		std::array<float, 6> getVertices();

	public:
		std::array<unsigned int, 3> getIndices(unsigned int offset);

	public:
		void draw(unsigned int programId);
	};

	struct plane
	{
	public:
		point lowerLeft;

	public:
		point upperLeft;

	public:
		point lowerRight;

	public:
		point upperRight;

	public:
		std::array<float, 8> getVertices();

	public:
		std::array<unsigned int, 6> getIndices();

	public:
		void draw(unsigned int programId);
	};
};