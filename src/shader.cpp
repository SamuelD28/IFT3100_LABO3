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
	// Shader stuff
	class shader_error : std::exception
	{
	public:
		std::string message = "";

	public:
		shader_error(std::string message)
		{
			this->message = message;
		}
	};

	struct shader
	{
		unsigned int programId = -1;
		unsigned int id = -1;
		std::string path = "";
		std::string source = "";
		unsigned int type = -1;
	};

	// Does the file gets freed if an error occurs?
	std::string load(std::string location)
	{
		auto file = std::ifstream{location};
		if (!file.is_open())
		{
			throw shader_error("could not open file at location: " + location);
		}

		std::string source{};
		while (file)
		{
			std::string line;
			std::getline(file, line);
			source = source.append(line) + "\n"; // need to keep return line for compilation
		}

		file.close();
		return source;
	}

	unsigned int compile(std::string source, unsigned int type)
	{
		const char *sourcePointer = source.c_str();

		if (sourcePointer == "")
		{
			throw new shader_error("source is empty. make sure to load the resource before compiling");
		}

		GLuint shaderId = glCreateShader(type);

		glShaderSource(shaderId, 1, &sourcePointer, NULL);
		glCompileShader(shaderId);

		// Look for cleaner way to handle errors
		GLint isCompiled{};
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength{};
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
			auto errorLog = std::vector<GLchar>(maxLength);
			glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(shaderId);

			auto errorMessage = std::string(errorLog.begin(), errorLog.end());
			throw shader_error(errorMessage);
		}

		return shaderId;
	}

	// Program stuff
	unsigned int initProgram()
	{
		return glCreateProgram();
	}

	bool attachProgram(unsigned int programId, unsigned int shaderId)
	{
		glAttachShader(programId, shaderId);
	}

	unsigned int buildProgram(std::vector<shader> &shaders)
	{
		unsigned int programId = initProgram();

		for (auto shader : shaders)
		{
			shader.source = load(shader.path);
			shader.id = compile(shader.source, shader.type);
			attachProgram(programId, shader.id);
			shader.programId = programId;
		}

		glLinkProgram(programId);

		GLint success{};
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			throw new shader_error(infoLog);
		}

		return programId;
	}

	// Texture stuff
	unsigned int createTexture(std::vector<std::string> imagesPath)
	{
		const unsigned int width = 512;
		const unsigned int height = 512;
		unsigned int textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);

		// Create a storage for the 3d texture
		glTexImage3D(GL_TEXTURE_2D_ARRAY,
								 0,																 // level
								 GL_RGB,													 // Internal format
								 width, height, imagesPath.size(), // width,height,depth
								 0,
								 GL_BGR,					 // format
								 GL_UNSIGNED_BYTE, // type
								 0								 // pointer to data
		);

		for (unsigned int i = 0; i < imagesPath.size(); i++)
		{
			auto imagePath = imagesPath[i];
			auto imagePointer = imagePath.c_str();
			auto type = FreeImage_GetFileType(imagePointer, 0);
			auto image = FreeImage_Load(type, imagePointer, 0);

			if (image == NULL)
			{
				throw shader_error("iamge could not be loaded");
			}

			auto rescaledImage = FreeImage_Rescale(image, width, height);
			auto bytes = FreeImage_GetBits(rescaledImage);

			// Assign a texture to depth 1
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_BGR, GL_UNSIGNED_BYTE, bytes);

			FreeImage_Unload(image);
		}

		// Really fucken necessary even if you dont use mipmap levels in texture3d
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return textureId;
	}
}