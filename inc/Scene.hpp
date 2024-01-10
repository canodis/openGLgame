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
	std::vector<GameObject *> gameObjects;

private:
	Scene(int width, int height)
	{
		init_window(width, height);
		vaoManager = new VertexArrayObjectManager();
		shaderProgram = new ShaderProgram();
		textureManager = new TextureManager();
		gameObjectManager = new GameObjectManager(vaoManager);
		timer = new Timer();
	}
	~Scene() {}

	void init_window(int width, int height);
};

// Kullanımı:
// Scene& myScene = Scene::getInstance(1024, 768);
