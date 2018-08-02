#include "GameController.h"
#include "../ECS/Components/CameraComponent.h"
#include "../ECS/Components/InuputMoveComponent.h"
#include "../ECS/Components/InputShotComponent.h"
#include "../ECS/Components/SkyBoxComponent.h"
#include "../ECS/Components/FieldComponent.h"
#include "../ECS/Components/ThiefComponent.h"
#include "../ECS/Components/MiniMapComponent.h"
#include "../ECS/Components/TomatoComponent.h"
#include "../ECS/Components/CursorComponent.h"
#include "../ECS/Components/ScoreBoardComponent.h"
#include "../ECS/Components/GameStateComponent.h"
#include "../ECS/Components/PauseComponent.h"
#include "../ECS/Components/TitleComponent.h"
#include <iostream>

const void GameController::Title(const GameState& state)
{
	if (state == GameState::TITLE)
	{
		auto& titleScene(entityManager.GetGroup(TITLE));
		for (auto& it : titleScene)
		{
			it->UpDate();
		}
	}
}

const void GameController::Play(const GameState& state)
{
	if (state == GameState::PLAY)
	{
		auto& gameScene(entityManager.GetGroup(GAME));
		for (auto& it : gameScene)
		{
			it->UpDate();
		}
		//衝突した時のイベント処理
		CollisionEvent();
		//プレイヤーの位置と向きから発射する
		shot.GetComponent<InputShotComponent>().Shot(ComAssist::GetTransform(player));
		if (KeyBoard::Down(KeyBoard::Key::KEY_A))
		{
			enemy.GetComponent<ThiefComponent>().DeleteThis();
		}
		if (KeyBoard::Down(KeyBoard::Key::KEY_G))
		{
			enemy.AddComponent<ThiefComponent>();
		}
	}
}

const void GameController::Pause(const GameState& state)
{
	if (state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->UpDate();
		}
	}
}

const void GameController::End(const GameState& state)
{
	if (state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->UpDate();
		}
	}
}

const void GameController::Always()
{
	auto& always(entityManager.GetGroup(ALWAYS));
	for (auto& it : always)
	{
		it->UpDate();
	}
}

Particle& GameController::GetParticle()
{
	static std::unique_ptr<Particle> ef = std::make_unique<Particle>();
	return *ef;
}

GameController::GameController() :
	player(entityManager.AddEntity()),
	shot(entityManager.AddEntity()),
	skyBox(entityManager.AddEntity()),
	enemy(entityManager.AddEntity()),
	field(entityManager.AddEntity()),
	gameCanvas(entityManager.AddEntity()),
	topping(entityManager.AddEntity()),
	gameMaster(entityManager.AddEntity()),
	pauseCanvas(entityManager.AddEntity()),
	titleCanvas(entityManager.AddEntity())
{
	gameMaster.AddComponent<GameStateComponent>();
	player.AddComponent<TransformComponent>(Pos(0, 15, 0), Velocity(0.6f, 0.6f, 0.6f), Angles(0, 0, 0), Scale(1, 1, 1));
	player.AddComponent<InuputMoveComponent>(0.1f);
	player.AddComponent<CameraComponent>();
	player.AddComponent<CursorComponent>();
	shot.AddComponent<InputShotComponent>(40.0f, 20, 0.3f);


	skyBox.AddComponent<SkyBoxComponent>("Resource/Texture/sky2.png");
	field.AddComponent<FieldComponent>();
	enemy.AddComponent<ThiefComponent>();
	gameCanvas.AddComponent<MiniMapComponent>();
	gameCanvas.AddComponent<ScoreBoardComponent>();
	pauseCanvas.AddComponent<PauseComponent>();
	topping.AddComponent<TomatoComponent>();
	titleCanvas.AddComponent<TitleComponent>();
	//グループに登録
	titleCanvas.AddGroup(TITLE);
	gameMaster.AddGroup(ALWAYS);
	skyBox.AddGroup(ALWAYS);
	field.AddGroup(ALWAYS);
	gameCanvas.AddGroup(ALWAYS);
	topping.AddGroup(GAME);
	player.AddGroup(GAME);
	shot.AddGroup(GAME);
	enemy.AddGroup(GAME);
	pauseCanvas.AddGroup(PAUSE);

}

void GameController::CollisionEvent()
{
	enemy.GetComponent<ThiefComponent>().Damaged(shot);
	topping.GetComponent<TomatoComponent>().ToBeKidnapped(enemy);
}

void GameController::Initialize()
{
	entityManager.Initialize();
}

void GameController::UpDate()
{
	const auto&& state = ComAssist::GetGameState(gameMaster);
	if (state == GameState::RESET)
	{
		entityManager.Initialize();
	}

	//敵が死んだらスコアを増やす
	gameCanvas.GetComponent<ScoreBoardComponent>().SetEntity(enemy);
	Always();
	Title(state);
	Play(state);
	Pause(state);
	//Entityの状態の監視
	entityManager.Refresh();
	//果てが来てしまうのでプレイヤーと一緒に動かす
	skyBox.GetComponent<SkyBoxComponent>().SetPos(ComAssist::GetPos(player));
	//効果音のListenerをセットする。正しく聞こえないことがあるのでEntityの更新の後に呼ぶ
	enemy.GetComponent<ThiefComponent>().SetListenerPos(ComAssist::GetPos(player));
	//追跡対象をセットし対象を追跡する
	enemy.GetComponent<ThiefComponent>().SetTrackingTarget(topping);
	//ゲームエンドならスコアボードを動かす
	gameCanvas.GetComponent<ScoreBoardComponent>().CheckState(state);
	//マウスは常に画面中央
	Mouse::SetMousePos(0, 0);

}

void GameController::Draw3D()
{
	player.GetComponent<CameraComponent>().Project3D();
	entityManager.Draw3D();
	//すべてのparticleにカメラのビューとプロジェクションを渡す
	GetParticle().UpDate(Camera(player.GetComponent<CameraComponent>().GetCamera3D()));
}

void GameController::Draw2D()
{
	Mouse::DrawCursor(false);
	player.GetComponent<CameraComponent>().Project2D();

	const auto&& state = ComAssist::GetGameState(gameMaster);
	auto& always(entityManager.GetGroup(ALWAYS));
	auto& gameScene(entityManager.GetGroup(GAME));
	//後に処理したものが手前に描画される
	for (auto& it : always)
	{
		it->Draw2D();
	}
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(topping, player);
	gameCanvas.GetComponent<MiniMapComponent>().DrawEntityes(enemy, player);
	for (auto& it : gameScene)
	{
		it->Draw2D();
	}

	if (state == GameState::TITLE)
	{
		auto& title(entityManager.GetGroup(TITLE));
		for (auto& it : title)
		{
			it->Draw2D();
		}
	}
	if(state == GameState::PAUSE)
	{
		auto& pause(entityManager.GetGroup(PAUSE));
		for (auto& it : pause)
		{
			it->Draw2D();
		}
	}
	if(state == GameState::END)
	{
		auto& end(entityManager.GetGroup(END));
		for (auto& it : end)
		{
			it->Draw2D();
		}
	}

}

void GameController::Finalize()
{

}
