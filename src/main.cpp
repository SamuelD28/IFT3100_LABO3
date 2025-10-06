#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <shader.hpp>
#include <shape.hpp>

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

	GLFWwindow *window = glfwCreateWindow(900, 900, "Labo 3", NULL, NULL);
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

	std::vector<float> vertices{};
	std::vector<unsigned int> indices{};

	shape::triangle triangle(
			0,
			std::array<float, 4>{1.0f, 0.0f, 0.0f, 0.0f},
			shape::point(-0.5f, -0.5f),
			shape::point(0.0f, 0.5f),
			shape::point(0.5f, -0.5f));
	auto triangleVertices = triangle.getVertices();
	auto triangleIndices = triangle.getIndices(0);

	for (auto vertice : triangleVertices)
	{
		vertices.insert(vertices.end(), vertice);
	}

	for (auto indice : triangleIndices)
	{
		indices.insert(indices.end(), indice);
	}

	shape::triangle triangle_two(
			0,
			std::array<float, 4>{0.0f, 1.0f, 0.0f, 0.0f},
			shape::point(-0.75f, -0.75f),
			shape::point(0.0f, 0.75f),
			shape::point(0.75f, -0.75f));
	auto triangleTwoVertices = triangle_two.getVertices();
	auto triangleTwoIndices = triangle_two.getIndices(3);

	for (auto vertice : triangleTwoVertices)
	{
		vertices.insert(vertices.end(), vertice);
	}

	for (auto indice : triangleTwoIndices)
	{
		indices.insert(indices.end(), indice);
	}

	for (auto indice : indices)
	{
		std::cout << indice << "\n";
	}
	std::cout << "------\n";

	for (auto vertice : vertices)
	{
		std::cout << vertice << "\n";
	}

	unsigned int vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indices.size(), indices.data(), GL_STATIC_DRAW);

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

		triangle_two.draw(programId);
		glDrawArrays(GL_LINES, 0, vertices.size() / 2);
		
		triangle.draw(programId);
		glDrawArrays(GL_LINES, vertices.size() / 2, vertices.size() / 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}