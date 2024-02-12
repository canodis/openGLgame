#pragma once

class Scene;

#include "VertexArrayObjectManager.hpp"
#include "ShaderProgram.hpp"
#include "TextureManager.hpp"
#include "GameObjectManager.hpp"
#include "Camera2D.hpp"
#include "Player.hpp"
#include <glad.h>
#include <glfw3.h>
#include <vector>
#include "GameObject.hpp"
#include "Timer.hpp"
#include "TextRenderer.hpp"
#include "BoxCollision2dController.hpp"
#define WIDTH 800
#define HEIGHT 600


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Scene
{
public:
	static Scene &getInstance();
	Scene(Scene const &) = delete;
	void operator=(Scene const &) = delete;

public:
	VertexArrayObjectManager *vaoManager;
	ShaderProgram *shaderProgram;
	TextureManager *textureManager;
	GLFWwindow *window;
	GameObjectManager *gameObjectManager;
	Timer *timer;
	Player *player;
	TextRenderer *textRenderer;
	BoxCollision2dController *boxCollision2dController;
	std::vector<GameObject *> gameObjects;
	glm::vec3 playerPosition;
	int windowWidth;
	int windowHeight;
	bool debug;
	void DrawGameObjects(float deltaTime);
	void handleSizeChange(int width, int height);
	glm::vec2 getWindowSize() const;
	float deltaTime = 0;
private:
	Scene();
	~Scene();

	void init_window(int width, int height);
	void init_uniforms();
	void keycallback();
};

