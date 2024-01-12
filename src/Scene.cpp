#include "Scene.hpp"

void	Scene::init_window(int width, int height)
{
	if (!glfwInit())
        exit(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(width, height, "Canodis", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
        std::cout << "Window can't create !\n";
		exit(1);
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void	Scene::init_uniforms()
{
	shaderProgram->addUniform("mtxTransform");
    shaderProgram->addUniform("textureSampler");
    shaderProgram->addUniform("viewMatrix");
}