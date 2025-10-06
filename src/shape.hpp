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
		point first;

	public:
		point second;

	public:
		point third;

	public:
		float *getVertices();

	public:
		unsigned int *getIndices();
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
		float *getVertices();

	public:
		float *getIndices();
	};
};