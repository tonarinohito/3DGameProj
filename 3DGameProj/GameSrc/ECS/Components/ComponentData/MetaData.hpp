#pragma once
#include "../../Engine.h"
#include "AABB.hpp"
#include "Sphere.hpp"
#include "../../Utilitys/Easing.hpp"

struct TransForm
{
	Pos pos;				//座標
	Scale scale;			//大きさ
	Angles angles;			//姿勢
	Velocity velocity; 		//向きや移動量を格納
};

struct ShotData
{
	bool isActive;				//有効か
	int cnt;					//寿命
	TransForm trans;
};

struct EnemyData
{
	enum class State
	{
		TRACKING,	//追跡中
		GETAWAY,	//逃走中
		DEATH		//死亡
	};
	long long id;
	State state;
	int lifeSpan;			//寿命
	AABB aabb;				//コリジョンの形状
	Pos trackingTarget;		//追跡対象
	Easing upMove;
	TransForm trans;
};

struct ToppingData
{
	enum class State
	{
		EFFECTIVE,		//有効(追跡可能)
		INVALID,		//無効(追跡無効,攫われている)
		DEATH			//死亡
	};
	Easing sucked;
	long long id;
	State state;
	Sphere sphere;
	TransForm trans;
};

enum class GameState
{
	TITLE,		//タイトル
	PLAY,		//ゲーム中
	PAUSE,		//停止中
	RESET		//すべてのEntityの初期化処理を呼ぶ
};