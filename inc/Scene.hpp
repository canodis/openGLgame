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

class Scene
{
public:
	static Scene &getInstance(int width = 800, int height = 600)
	{
		static Scene instance(width, height);
		return instance;
	}
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

	bool debug;
private:
	Scene(int width, int height)
	{
		init_window(width, height);
		vaoManager = new VertexArrayObjectManager();
		shaderProgram = new ShaderProgram();
		textureManager = new TextureManager();
		gameObjectManager = new GameObjectManager(vaoManager);
		timer = new Timer();
		textRenderer = new TextRenderer();
		boxCollision2dController = new BoxCollision2dController();
		debug = false;
		init_uniforms();
		keycallback();
	}
	~Scene();

	void init_window(int width, int height);
	void init_uniforms();
	void keycallback();
};
