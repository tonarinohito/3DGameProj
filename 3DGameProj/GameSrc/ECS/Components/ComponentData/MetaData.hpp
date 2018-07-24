#pragma once
#include "../../Engine.h"


struct TransForm
{
	Pos pos;				//座標
	Scale scale;			//大きさ
	Angles angles;		//姿勢
	Velocity velocity; 	//向きや移動量を格納
};

struct MetaData
{
	bool isActive;			//生きているか
	int lifeSpan;			//寿命
	float radius;			//Meshの半径
	Pos pos;				//座標
	Scale scale;			//大きさ
	Angles angles;		//姿勢
	Velocity velocity; 	//向きや移動量を格納
};