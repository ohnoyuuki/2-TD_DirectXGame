#include "GameScene.h"
#include"input/Input.h"

// 初期化
void GameScene::Initialize() {

	//自機のハート//
	//ファイル名を指定してテクスチャハンドルを読み込む
	hatoHandle_ = TextureManager::Load("ha-to.png");
	// 複数のスプライトを生成
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして配置
		Sprite* heart = Sprite::Create(hatoHandle_, {300.0f + i * 55.0f, 660.0f});
		hearts_.push_back(heart);
	}

	// プレイヤーHP = ハート数
	playerHP_ = static_cast<int>(hearts_.size());
	//-------------------------------------


	//敵のハート//
	ehatoHadle_ = TextureManager::Load("Eha-to.png");
	//複数のスプライトを生成
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして配置
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {1000.0f + i * 55.0f, 10.0f});
		enemyHearts_.push_back(enemyHeart);
	}
	//------------------------------------

}

// 更新
void GameScene::Update() {
	// スペースキーが押された瞬間に HP を1減らす
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		if (playerHP_ > 0) {
			playerHP_--;
		}
	}


}

// 描画
void GameScene::Draw() {
	// スプライト描画前処理
	Sprite::PreDraw();

	// プレイヤーHP分だけ描画する
	for (int i = 0; i < playerHP_; i++) {
		hearts_[i]->Draw();
	}

	// 敵ハートは常に全描画
	for (auto& enemyHeart : enemyHearts_) {
		enemyHeart->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();


}

// デストラクタ
GameScene::~GameScene() {

	// 生成したスプライトを解放
	for (auto& heart : hearts_) {
		delete heart;
	}
	hearts_.clear(); // ベクターの中身（ポインタの参照）を削除

	// 生成したスプライトを解放
	for (auto& enemyHeart : hearts_) {
		delete enemyHeart;
	}
	enemyHearts_.clear(); // ベクターの中身（ポインタの参照）を削除

}
