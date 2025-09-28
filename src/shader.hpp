#include <string>
#include <iostream>
#include <fstream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <cmath>
#include <FreeImage.h>

namespace shader
{
	class shader_error : std::exception
	{
	};
	struct shader
	{
		unsigned int programId;
		unsigned int id;
		std::string path;
		std::string source;
		unsigned int type;
	};

	std::string load(std::string location);
	unsigned int compile(std::string source, unsigned int type);
	unsigned int initProgram();
	bool attachProgram(unsigned int programId, unsigned int shaderId);
	unsigned int buildProgram(std::vector<shader> &shaders);
	unsigned int createTexture(std::vector<std::string> imagesPath);
}