namespace shape
{

	struct point
	{
	public:
		float x = 0;

	public:
		float y = 0;
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

		float *getVertices()
		{
			float vertices[] = {
					lowerLeft.x,
					lowerLeft.y,
					lowerRight.x,
					lowerRight.y,
					upperLeft.x,
					upperLeft.y,
					upperRight.x,
					upperLeft.x,
			};
			return vertices;
		}

		float *getIndices()
		{
			float vertices[] = {
					0,
					1,
					2,
					2,
					3,
					1,
			};
			return vertices;
		}
	};

};