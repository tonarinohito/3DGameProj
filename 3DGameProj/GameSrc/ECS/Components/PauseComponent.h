#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"
class PauseComponent : public Component
{
private:
	UIData data;
	Sprite sprite;
	Text text;
public:
	PauseComponent();
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;
	//ゲームを開始するか返す
	const GameState GetState();
};