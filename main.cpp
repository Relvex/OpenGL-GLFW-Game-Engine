#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "RawModel.h"
#include "Loader.h"

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

void setup(GLFWwindow* &window)
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

	Loader* loader = new Loader();

	std::vector<float> vertices = {
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	RawModel model = loader->loadToVAO(vertices);

	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(model.getVaoID());
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	loader->~Loader();
	glfwDestroyWindow(window);
	glfwTerminate();
}