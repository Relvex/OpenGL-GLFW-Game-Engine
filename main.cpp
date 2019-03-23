#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RawModel.h"
#include "GLUtils.h"
#include "ShaderProgram.h"

#include <iostream>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %i: %s\n", error, description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void setup(GLFWwindow*& window)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
}

int main()
{
	GLFWwindow* window;

	setup(*&window);

	glfwSwapInterval(0);

	std::vector<float> vertices = {
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f
	};

	std::vector<unsigned int> test = {
		0, 1, 3,
		3, 1, 2
	};

	RawModel rectangle = GLUtils::loadToVAO(vertices, test);

	ShaderProgram shader = ShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.85f, 0.9f, 1.0f, 1.0f);

		shader.start();

		glBindVertexArray(rectangle.getVaoID());
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, rectangle.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		shader.stop();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.clean();
	glfwDestroyWindow(window);
	glfwTerminate();
}