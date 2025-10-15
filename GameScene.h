#pragma once
#include "KamataEngine.h"
#include"Player.h"
#include"Enemy.h"
#include"input/Input.h"
#include <algorithm>
#include <array>
#include <numbers>
#include"MyMath.h"

using namespace KamataEngine;
using namespace MathUtility;

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

	//自機3Dモデルデータ
	Model* modelPlayer_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;

	//敵キャラ
	Enemy* enemy_ = nullptr;

	Model* modelEnemy_ = nullptr;

	//------------------------------

	//カメラ
	Camera camera_;

	//デバッグカメラ
	//DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;


	// 敵ハートを複数持つ
	std::vector<Sprite*> enemyHearts_;

};
