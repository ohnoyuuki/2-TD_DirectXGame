#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

using namespace KamataEngine;

class Kaminari {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;
};
