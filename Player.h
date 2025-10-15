#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Player {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera /*uint32_t textureHandle,*/);
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;
	////テクスチャハンドル
	// uint32_t textureHandle_ = 0u;

	// カメラ
	Camera* camera_ = nullptr;
};
