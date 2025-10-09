#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(Model* model, uint32_t textureHandle,Camera*camera) { 
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;
	worldtransform_.Initialize();
	
}

void Player::Update() {
	//行列を定数バッファに転送
	worldtransform_.TransferMatrix();

}

void Player::Draw() {

if (!model_ || !camera_)
		return;

	

	Model::PreDraw(); // ← 引数なし
	model_->Draw(worldtransform_, *camera_, textureHandle_);
	Model::PostDraw();
}
