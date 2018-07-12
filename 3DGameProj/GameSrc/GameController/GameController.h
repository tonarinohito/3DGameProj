#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"

//Entityの制御を行うクラスです
class GameController
{
private:
	EntityManager entityManager;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	//仮
	Entity& hoge;
	Particle ef;
	Texture t;
	Mesh ground;

	int handle;
	SoundEngine::SoundSource sound;
	//
public:
	GameController();
	~GameController();
	void CollisionEvent();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};