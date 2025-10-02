#include "GameScene.h"

// 初期化
void GameScene::Initialize() {
	//ファイル名を指定してテクスチャハンドルを読み込む
	hatoHandle_ = TextureManager::Load("ha-to.png");

	// 複数のスプライトを生成
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして配置
		Sprite* heart = Sprite::Create(hatoHandle_, {500.0f + i * 55.0f, 400.0f});
		hearts_.push_back(heart);
	}

	ehatoHadle_ = TextureManager::Load("Eha-to.png");
	//複数のスプライトを生成
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして配置
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {800.0f + i * 55.0f, 100.0f});
		enemyHearts_.push_back(enemyHeart);
	}


}

// 更新
void GameScene::Update() {}

// 描画
void GameScene::Draw() {
	//スプライト描画前処理
	Sprite::PreDraw();

	// 複数の自機ハートスプライトを描画
	for (auto& heart : hearts_) {
		heart->Draw();
	}

	// 複数の敵ハートスプライトを描画
	for (auto& enemyHeart : enemyHearts_) {
		enemyHeart->Draw();
	}



	//スプライト描画後処理
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
