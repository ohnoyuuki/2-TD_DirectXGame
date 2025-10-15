#include "GameScene.h"


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

	//ファイル名を指定してテクスチャハンドルを読み込む
	playerHandle_ = TextureManager::Load("a.png");

	//3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player");

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(modelPlayer_, &camera_);

	//-------------------------------------

	//カメラの初期化
	camera_.Initialize();

	// デバッグカメラの生成
	//debugCamera_ = new KamataEngine::DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	//KamataEngine::AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	//KamataEngine::AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());


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

	//自キャラ------------------------------------------
	// スペースキーが押された瞬間に HP を1減らす
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		if (playerHP_ > 0) {
			playerHP_--;
		}
	}
	//自キャラの更新
	player_->Update();

	//デバッグカメラの更新
	//debugCamera_->Update();

	camera_.translation_ = Vector3(0.0f, 0.0f, -10.0f);
	camera_.UpdateMatrix();
}

// 描画
void GameScene::Draw() {



	//3Dモデル描画前処理
	Model::PreDraw();

	////自キャラの描画
	player_->Draw();

	//3Dモデル描画後処理
	Model::PostDraw();




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

	//自機------------------------------------------------------
	

	// 生成したスプライトを解放
	for (auto& heart : hearts_) {
		delete heart;
	}
	hearts_.clear(); // ベクターの中身（ポインタの参照）を削除

	//自キャラの解放
	delete player_;
	//モデル解放
	delete modelPlayer_;

	//-----------------------------------------------------------

	//デバッグカメラ
	//delete debugCamera_;



	// 生成したスプライトを解放
	for (auto& enemyHeart : hearts_) {
		delete enemyHeart;
	}
	enemyHearts_.clear(); // ベクターの中身（ポインタの参照）を削除

}
