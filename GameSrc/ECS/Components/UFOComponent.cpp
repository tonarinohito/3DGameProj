#include "UFOComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include "../Components/TomatoComponent.h"
#include "../../Utilitys/Randam.hpp"
#include <iterator>
#include <iostream>
#include <algorithm>

long long UFOComponent::id_ = 0;
std::unique_ptr<EnemyData> UFOComponent::AddEnemy()
{
	return std::make_unique<EnemyData>();
}

void UFOComponent::LifeCheck()
{
	for (auto& it : data)
	{
		if (it->lifeSpan <= 0)
		{
			it->state = EnemyData::State::DEATH;
		}
	}
}

void UFOComponent::Create(const float& theta)
{
	//有効なトマトがない場合は出現させない
	if (isNotFound)
	{
		return;
	}
	//生成されるたび移動力を増やす
	addedSpeed += 0.04f;
	data.emplace_back(AddEnemy());
	data.back()->state = EnemyData::State::TRACKING;
	//制限時間10秒前くらいからは体力を1にする
	if (pTimelimit->GetCurrentCount() <= 700)
	{
		data.back()->lifeSpan = 1;
	}
	else
	{
		data.back()->lifeSpan = 3;
	}
	data.back()->trans.velocity = 0.8f + addedSpeed;
	data.back()->trans.scale = RADIUS * 2;
	Random rand;
	constexpr float FIELD_RADIUS = 500;		//フィールドの半径
	data.back()->trans.pos.x = cosf(DirectX::XMConvertToRadians(theta)) * FIELD_RADIUS;
	data.back()->trans.pos.z = sinf(DirectX::XMConvertToRadians(theta)) * FIELD_RADIUS;
	data.back()->trans.pos.y = rand.GetRand(20.0f, 100.0f);
	data.back()->trackingTarget = Pos(0, 0, 0);
	data.back()->id = id_;
	efHandle = AsetManager::GetParticle().Play("app", Vec3(data.back()->trans.pos));
	AsetManager::GetParticle().SetAngles(efHandle, Vec3(90, 0, 0));
	AsetManager::GetParticle().SetScale(efHandle, Vec3(3, 3, 3));
	appSound.PlaySE(0, 10);
	++id_;
}

void UFOComponent::Refresh()
{
	//死亡かフィールド範囲外なら消滅
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const std::unique_ptr<EnemyData> &data)
	{
		return data->state == EnemyData::State::DEATH ||
			(abs(data->trans.pos.x) >= FieldOut || abs(data->trans.pos.z) >= FieldOut && data->state == EnemyData::State::GETAWAY);
	}),
		std::end(data));
}

const float UFOComponent::GetTheta() const
{
	//制限時間によって出現位置を変更する
	float THETA = 0;
	Random rand;
	if (pTimelimit->GetCurrentCount() <= 2200 && pTimelimit->GetCurrentCount() >= 1500)
	{
		THETA = rand.GetRand(125.0f, 160.0f);
	}
	else if (pTimelimit->GetCurrentCount() <= 1500 && pTimelimit->GetCurrentCount() >= 900)
	{
		THETA = rand.GetRand(45.0f, 90.0f);
	}
	else if (pTimelimit->GetCurrentCount() <= 900)
	{
		THETA = rand.GetRand(0.0f, 360.0f);
	}
	else
	{
		THETA = rand.GetRand(0.f, 45.0f);
	}
	return THETA;
}


void UFOComponent::SetListenerPos(Pos&& pos)
{
	if (!IsActive())
	{
		return;
	}
	if (!data.empty())
	{
		listenerPos = pos;
		appSound.UpDate3DSound(Vec3(data.back()->trans.pos), Vec3(pos.x, pos.y, pos.z));
	}
}

UFOComponent::UFOComponent() :
	cnt(0, 1, 0, 60)
{
	appSound.Load("Resource/Sounds/steam_long.wav", true);
	exproSound.Load("Resource/Sounds/expro.wav", true);
}

void UFOComponent::Damaged(Entity& e)
{
	if (!IsActive())
	{
		return;
	}
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::DEATH)
		{
			continue;
		}
		if (e.GetComponent<InputShotComponent>().IsHit(it->aabb.Create(it->trans.pos, Scale(it->trans.scale.x * 2.1f, it->trans.scale.y, it->trans.scale.z))))
		{
			efHandle = AsetManager::GetParticle().Play("expro", Pos(it->trans.pos));
			AsetManager::GetParticle().SetScale(efHandle, Vec3(6, 6, 6));
			exproSound.PlaySE(0, 15);
			exproSound.UpDate3DSound(Pos(it->trans.pos), Vec3(listenerPos));
			--it->lifeSpan;
		}
	}
}

bool UFOComponent::IsToBeInRange(Sphere& sphere, long long& id_)
{
	if (data.empty())
	{
		return false;
	}
	for (auto& it : data)
	{
		if (it->state != EnemyData::State::TRACKING)
		{
			continue;
		}
		if (Collison::SphereAABBCollision(sphere, it->aabb.Create(
			Pos(it->trans.pos.x, it->trans.pos.y - 5, it->trans.pos.z),
			Scale(it->trans.scale.x * 0.001f, it->trans.scale.y * 3.3f, it->trans.scale.z * 0.001f))))
		{
			//当たった敵と同じIDにする
			id_ = it->id;
			it->state = EnemyData::State::GETAWAY;
			AsetManager::GetParticle().Play("sucking", Pos(it->trans.pos));
			return true;
		}
	}
	return false;
}

void UFOComponent::Initialize()
{
	addedSpeed = 0;
	isNotFound = false;
	pTimelimit = nullptr;
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		it->state = EnemyData::State::DEATH;
	}
	id_ = 0;
	Refresh();
}

void UFOComponent::UpDate()
{
	if (&entity->GetComponent<UFOComponent>() == nullptr)
	{
		return;
	}
	//$Test$
	if (pTimelimit != nullptr && pTimelimit->GetCurrentCount() <= 600)
	{
		cnt.SetEndTime(30, -1);
	}
	if (++cnt >= cnt.GetMax())
	{
		Create(GetTheta());
	}

	if (data.empty())
	{
		return;
	}
	LifeCheck();
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::TRACKING)
		{
			//追従させる
			Vec3 ret = (it->trackingTarget - it->trans.pos);
			ret.Normalize();

			it->trans.pos += ret * it->trans.velocity;
			//高さの制限を決める
			if (it->trans.pos.y <= HeightMax)
			{
				it->trans.pos.y = HeightMax;
			}
		}
		if (it->state == EnemyData::State::GETAWAY)
		{
			if (it->trans.pos.y >= UpMoveMAX)
			{
				it->upMove.Reset();
				it->trans.pos.z += it->trans.velocity.z * -1;
				it->trans.pos.x += it->trans.velocity.x * -1;
			}
			else
			{
				it->upMove.Run(Easing::QuintIn, 60);
				it->trans.pos.y = it->upMove.GetVolume(HeightMax, UpMoveMAX);
			}
			if ((abs(it->trans.pos.x) >= FieldOut || abs(it->trans.pos.z) >= FieldOut &&
				it->state == EnemyData::State::GETAWAY))
			{
				AsetManager::GetParticle().Play("away", Pos(it->trans.pos));
			}
		}
	}
	Refresh();
}

void UFOComponent::Draw3D()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		if (it->state != EnemyData::State::DEATH)
		{
			TransForm convert = it->trans;	//元のモデルが大きすぎるので
			convert.scale /= 10;
			AsetManager::GetModels().DrawModel("UFO", convert);
		}
	}
}

void UFOComponent::SetTrackingTarget(Entity& target) noexcept
{
	if (!IsActive())
	{
		return;
	}
	if (!target.HasComponent<TomatoComponent>())
	{
		return;
	}
	if (target.GetComponent<TomatoComponent>().GetData().empty())
	{
		return;
	}
	auto& targets = target.GetComponent<TomatoComponent>().GetData();
	std::vector<std::pair<float, Pos>> dist;
	dist.resize(targets.size());
	dist.shrink_to_fit();
#undef min
#undef max
	constexpr float Max = std::numeric_limits<float>::max();
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::TRACKING)
		{
			for (size_t i = 0; i < targets.size(); ++i)
			{
				if (targets[i].state == TomatoData::State::INVALID)
				{
					//無効なターゲットも追跡してしまうので無効なものは遠くにしておく	
					dist[i].first = Max;
					dist[i].second = Pos(Max, Max, Max);
					continue;
				}
				//複数の有効なターゲットとの距離を測る
				dist[i].first = abs(it->trans.pos.GetDistance(Pos(targets[i].trans.pos)));
				//座標の保存
				dist[i].second = targets[i].trans.pos;
			}
			//自分から見て一番近いものを追う
			std::sort(std::begin(dist), std::end(dist),
				[](const std::pair<float, Pos> &a, const std::pair<float, Pos> &b)
			{
				return a.first < b.first;
			});
			it->trackingTarget = dist[0].second;
		}
	}
	//有効なターゲットがいない場合出現させない
	auto count = std::count_if(targets.begin(), targets.end(),
		[](const TomatoData& state)
	{
		return state.state == TomatoData::State::EFFECTIVE;
	});
	if (count == 0)
	{
		isNotFound = true;
	}
	else
	{
		isNotFound = false;
	}
}

const std::vector<std::unique_ptr<EnemyData>>& UFOComponent::GetData() const
{
	return data;
}

void UFOComponent::SetTimeLimit(const Counter& limit)
{
	pTimelimit = &limit;
}
