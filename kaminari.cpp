#include "kaminari.h"

void Kaminari::Initialize(Model* model, Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();

	worldTransform_.translation_ = {5.0f, -3.0f, 0.0f}; // X, Y, Z の位置
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldTransform_.rotation_ = {0.0f, 850.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldTransform_.TransferMatrix();
}

void Kaminari::Update() {


	// 行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Kaminari::Draw() { 
	model_->Draw(worldTransform_, *camera_); 
}
