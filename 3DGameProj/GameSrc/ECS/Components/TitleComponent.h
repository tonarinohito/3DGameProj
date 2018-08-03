#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class TitleComponent : public Component
{
private:
	UIData logodata;
	UIData textdata;
	Sprite sprite;
	Sprite logo;
	Text text;
	bool isPlay;
public:

	TitleComponent();
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;

	//ゲームを開始するか返す
	const GameState GetState();
};