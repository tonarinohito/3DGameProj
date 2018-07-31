#include "InuputMoveComponent.h"
#include "ComponentData/Collision.h"
void InuputMoveComponent::MoveForwardAndBack()
{
	if (KeyBoard::On(KeyBoard::Key::KEY_W))
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_S))
	{
		transform->pos -= dir;
	}
}

void InuputMoveComponent::MoveLeftAndRight()
{
	if (KeyBoard::On(KeyBoard::Key::KEY_D))
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_A))
	{
		transform->pos -= dir;
	}
}

void InuputMoveComponent::FixedMovableAngle()
{
	if (transform->angle.x >= DownMax)
	{
		transform->angle.x = DownMax;
	}
	if (transform->angle.x <= UpMax)
	{
		transform->angle.x = UpMax;
	}
}

void InuputMoveComponent::ManipulationOfView()
{
	transform->angle.x += Mouse::GetMousePosCenter().y * speed_;
	transform->angle.y += Mouse::GetMousePosCenter().x * speed_;
}

void InuputMoveComponent::ForwardAndBackwardDirection()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y + DirOffSet)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y + DirOffSet)) * transform->velocity.z;
}

void InuputMoveComponent::LeftAndRightDirection()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y)) * transform->velocity.z;
}

InuputMoveComponent::InuputMoveComponent(const float speed)
{
	speed_ = speed;
}
void InuputMoveComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		transform = &entity->AddComponent<TransformComponent>();
	}
	transform = &entity->GetComponent<TransformComponent>();

	//初期位置を保存しておく
	static bool isInit = false;
	if (!isInit)
	{
		isInit = true;
		initPos = transform->pos;
	}
	//次回以降の初期化には保存した値を用いる
	transform->pos = initPos;
	eyeHeight = transform->pos.y;


}
void InuputMoveComponent::UpDate()
{
	ForwardAndBackwardDirection();
	MoveForwardAndBack();
	LeftAndRightDirection();
	MoveLeftAndRight();
	transform->pos.y = eyeHeight;
	ManipulationOfView();
	FixedMovableAngle();
	
	
	Mouse::SetMousePos(0, 0);
}

void InuputMoveComponent::Draw2D()
{
	
	t.Create("distance" +(std::to_string(abs(transform->pos.GetDistance(Pos(0, 0, 0))))));
	t.color = Float4(1, 1, 1, 1);
	t.pos.y = 20;
	t.pos.x = -500;
	t.Draw();
	t.Create("x"+ std::to_string(transform->pos.x) + "::" + "z" + std::to_string(transform->pos.z));
	t.color = Float4(1, 1, 1, 1);
	t.pos.y = 0;
	t.pos.x = -500;
	t.Draw();
}
