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
	enum class GameGroup : std::size_t
	{
		TITLE,
		GAME,
		END
	};

	EntityManager entityManager;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& thief;
	Entity& field;
	//仮
	SoundEngine::SoundSource sound;
	//
public:
	static Particle& GetParticle();
	
	GameController();
	~GameController();
	void CollisionEvent();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};