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
			std::array<float, 4>{1.0f, 0.0f, 0.0f, 0.0f},
			shape::point(-0.5f, -0.5f),
			shape::point(0.0f, 0.5f),
			shape::point(0.5f, -0.5f));
	auto triangleVertices = triangle.getVertices();
	auto triangleIndices = triangle.getIndices(0);

	// Create iterator instead of two list
	vertices.insert(vertices.end(), triangleVertices.begin(), triangleVertices.end());
	indices.insert(indices.end(), triangleIndices.begin(), triangleIndices.end());

	shape::triangle triangle_two(
			std::array<float, 4>{0.0f, 1.0f, 0.0f, 0.0f},
			shape::point(-0.75f, -0.75f),
			shape::point(0.0f, 0.75f),
			shape::point(0.75f, -0.75f));
	auto triangleTwoVertices = triangle_two.getVertices();
	auto triangleTwoIndices = triangle_two.getIndices(3);

	// Create iterator instead of two list
	vertices.insert(vertices.end(), triangleTwoVertices.begin(), triangleTwoVertices.end());
	indices.insert(indices.end(), triangleTwoIndices.begin(), triangleTwoIndices.end());

	// for (auto indice : indices)
	// {
	// 	std::cout << indice << "\n";
	// }

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

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

		triangle.draw(programId);
		glDrawElements(GL_LINE_LOOP, indices.size() / 2, GL_UNSIGNED_INT, 0);
		
		triangle_two.draw(programId);
		glDrawElements(GL_LINE_LOOP, indices.size() / 2, GL_UNSIGNED_INT, (void *)(3 * sizeof(unsigned int)));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}