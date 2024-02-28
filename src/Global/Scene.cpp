#include "Scene.hpp"

Scene &Scene::getInstance()
{
	static Scene instance;
	return instance;
}

Scene::Scene()
{
	init_window(WIDTH, HEIGHT);
	vaoManager = new VertexArrayObjectManager();
	shaderProgram = new ShaderProgram();
	textureManager = new TextureManager();
	gameObjectManager = new GameObjectManager(vaoManager);
	timer = new Timer();
	textRenderer = new TextRenderer();
	boxCollision2dController = new BoxCollision2dController();
	debug = false;
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	init_uniforms();
	keycallback();
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glfwSwapInterval(0);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
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
	shaderProgram->addUniform("lightPosition");
	shaderProgram->addUniform("lightInstensity");
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
	shaderProgram->use();
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