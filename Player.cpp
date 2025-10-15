#include "Player.h"
#include "input/Input.h"
using namespace KamataEngine;

void Player::Initialize(Model* model, /*uint32_t textureHandle,*/Camera*camera) { 
	assert(model); 
	model_ = model;
	/*textureHandle_ = textureHandle;*/
	camera_ = camera;
	worldtransform_.Initialize();
	
	worldtransform_.translation_ = {0.0f, 10000.0f, 200.0f}; // X, Y, Z の位置
	worldtransform_.scale_ = {20.0f, 20.0f, 20.0f};       // 大きさ
	worldtransform_.rotation_ = {0.0f, 0.0f, 0.0f};    // 回転

	// 行列をGPUに転送（初期化時）
	worldtransform_.TransferMatrix();

}

void Player::Update() {

	

	
	

	//行列を定数バッファに転送
	worldtransform_.TransferMatrix();


}

void Player::Draw() {

	Model::PreDraw(); 
	model_->Draw(worldtransform_, *camera_);
	Model::PostDraw();
}
