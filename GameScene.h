#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene {

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// デストラクタ
	~GameScene();

private:
	// 自機ハートハンドル
	uint32_t hatoHandle_ = 0;

	//敵ハートハンドル
	uint32_t ehatoHadle_ = 0;

	// 自機ハートを複数持つ
	std::vector<Sprite*> hearts_;

	// プレイヤーHP
	int playerHP_ = 0;

	// 敵ハートを複数持つ
	std::vector<Sprite*> enemyHearts_;

};
