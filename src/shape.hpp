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
		unsigned int offset = 0;

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
		float *getVertices();

	public:
		unsigned int *getIndices();

	public:
		void draw(unsigned int programId);
	};
};