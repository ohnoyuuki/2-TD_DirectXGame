#pragma once
#include "KamataEngine.h"
#include"Player.h"

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

	//自機--------------------------
	// 自機ハートハンドル
	uint32_t hatoHandle_ = 0;

	//敵ハートハンドル
	uint32_t ehatoHadle_ = 0;

	// 自機ハートを複数持つ
	std::vector<Sprite*> hearts_;

	// プレイヤーHP
	int playerHP_ = 0;

	//自機ハンドル
	uint32_t playerHandle_ = 0;

	//3Dモデルデータ
	Model* modelPlayer_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;

	//------------------------------


	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//カメラ
	Camera camera_;


	// 敵ハートを複数持つ
	std::vector<Sprite*> enemyHearts_;

};
