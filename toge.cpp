#include "toge.h"

void Toge::Initialize(Model* model, Camera* camera) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransform_.Initialize();

	worldtransform_.translation_ = {-2.0f, 0.0f, 0.0f}; // X, Y, Z の位置
	worldtransform_.scale_ = {1.0f, 1.0f, 1.0f};        // 大きさ
	worldtransform_.rotation_ = {0.0f, 850.0f, 0.0f};   // 回転

	// 行列をGPUに転送（初期化時）
	worldtransform_.TransferMatrix();
}

void Toge::Update() {
	// 行列を更新
	worldtransform_.matWorld_ = MakeAffineMatrix(worldtransform_.scale_, worldtransform_.rotation_, worldtransform_.translation_);
	// 行列を定数バッファに転送
	worldtransform_.TransferMatrix();
}

void Toge::Draw() { 
	model_->Draw(worldtransform_, *camera_);
}
