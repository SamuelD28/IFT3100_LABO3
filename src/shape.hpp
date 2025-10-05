namespace shape
{
	struct point
	{
	public:
		float x;

	public:
		float y;
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

		float *getVertices();
		float *getIndices();
	};
};