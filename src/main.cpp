#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <shader.hpp>

void glfwErrorCallback(int errorCode, const char *description)
{
	std::cout << "\nAn error occured. errorCode =" << errorCode << " description: " << *description << std::endl;
}

int main(int argc, char *argv[])
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwSetErrorCallback(glfwErrorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1000, 1000, "Labo 3", NULL, NULL);
	if (window == NULL)
	{
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "could not initialised glad" << std::endl;
		return -1;
	}

	float vertices[] = {
			-1.0f,
			-1.0f,
			0.0f,
			1.0f,
			0.0f,
			1.0f,
			1.0f,
			-1.0f,
	};

	unsigned int vbo, vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	std::vector<shader::shader> shaders{
			shader::shader{0, 0, "bin/shaders/line.vert", "", GL_VERTEX_SHADER},
			shader::shader{0, 0, "bin/shaders/line.frag", "", GL_FRAGMENT_SHADER},
	};

	auto programId = shader::buildProgram(shaders);
	glUseProgram(programId);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 8);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}