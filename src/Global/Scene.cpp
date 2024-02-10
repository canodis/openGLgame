#include "Scene.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    Scene::getInstance().handleSizeChange(width, height);
}

void Scene::init_window(int width, int height)
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Scene::init_uniforms()
{
	shaderProgram->addUniform("mtxTransform");
	shaderProgram->addUniform("textureSampler");
	shaderProgram->addUniform("viewMatrix");
	shaderProgram->addUniform("objColor");
}

void Scene::keycallback()
{
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
					   {
        if (key == GLFW_KEY_K && action == GLFW_PRESS)
            Scene::getInstance().debug = !Scene::getInstance().debug; });
}

void Scene::DrawGameObjects(float deltaTime)
{
	for (auto &object : gameObjects)
		object->update(deltaTime);
}

Scene::~Scene()
{
	delete vaoManager;
	delete shaderProgram;
	delete textureManager;
	delete gameObjectManager;
	delete timer;
	delete textRenderer;
	delete boxCollision2dController;
	glfwTerminate();
}

glm::vec2 Scene::getWindowSize() const
{
	return glm::vec2(windowWidth, windowHeight);
}

void Scene::handleSizeChange(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}