#include "GameScene.h"

//==================================================
// 初期化処理
//==================================================
void GameScene::Initialize() {

	//-------------------------------
	// 自機のHPハート設定
	//-------------------------------

	// プレイヤーのハート画像を読み込み
	hatoHandle_ = TextureManager::Load("ha-to.png");

	// ハートスプライトを5個生成して並べる
	for (int i = 0; i < 5; i++) {
		// X座標を少しずつずらして横に配置
		Sprite* heart = Sprite::Create(hatoHandle_, {300.0f + i * 55.0f, 660.0f});
		hearts_.push_back(heart);
	}

	//-------------------------------
	// 敵のHPハート設定
	//-------------------------------

	// 敵ハート画像を読み込み
	ehatoHadle_ = TextureManager::Load("Eha-to.png");

	// 敵ハートを5個生成して上部に並べる
	for (int i = 0; i < 5; i++) {
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {1000.0f + i * 55.0f, 10.0f});
		enemyHearts_.push_back(enemyHeart);
	}

	// HPの初期値（ハートの数で設定）
	playerHP_ = static_cast<int>(hearts_.size());
	enemyHP_ = static_cast<int>(enemyHearts_.size());

	//-------------------------------
	// プレイヤー設定
	//-------------------------------

	// プレイヤーの画像を読み込み
	playerHandle_ = TextureManager::Load("a.png");

	// 3Dモデルの読み込み
	modelPlayer_ = Model::CreateFromOBJ("player");

	// プレイヤーオブジェクト生成
	player_ = new Player();

	// モデルとカメラを渡して初期化
	player_->Initialize(modelPlayer_, &camera_);

	//-------------------------------
	// 攻撃ゲージの設定
	//-------------------------------

	// 攻撃ゲージ本体の画像読み込み
	attackHandle_ = TextureManager::Load("geegiBer.png");
	attackSprite_ = Sprite::Create(attackHandle_, {0, 0});

	// 攻撃ゲージ上を動く矢印画像読み込み
	attackArrowHandle_ = TextureManager::Load("RighAttackArrow.png");
	attackArrowSprite_ = Sprite::Create(attackArrowHandle_, {attackArrowX, attackArrowY});

	//-------------------------------
	// カメラ設定
	//-------------------------------
	camera_.Initialize();

	//-------------------------------
	// 敵キャラ設定
	//-------------------------------

	// 敵3Dモデル読み込み
	modelEnemy_ = Model::CreateFromOBJ("enemy");

	// 敵オブジェクト生成
	enemy_ = new Enemy();

	// モデルとカメラを渡して初期化
	enemy_->Initialize(modelEnemy_, &camera_);

	//-------------------------------
	// 攻撃ターン初期値
	//-------------------------------
	playerAttackTurn = 3;
}

//==================================================
// 更新処理
//==================================================
void GameScene::Update() {

	//------------------------------------------
	// 攻撃ゲージの矢印の移動処理
	//------------------------------------------

	// プレイヤーの攻撃ターンが残っているときのみ動作
	if (playerAttackTurn > 0) {

		// 矢印のY座標を上下に動かす
		attackArrowY += arrowDirection * 2;

		// 画面上端で反転
		if (attackArrowY <= 0) {
			attackArrowY = 0;
			arrowDirection = 5; // 下方向に
		}
		// 画面下端で反転
		else if (attackArrowY >= 576) {
			attackArrowY = 576;
			arrowDirection = -5; // 上方向に
		}

		//------------------------------------------
		// スペースキーで攻撃判定
		//------------------------------------------
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {

			// 一時停止 → 攻撃判定処理
			if (arrowDirection == 0) {
				// 動きを再開（上方向へ）
				attackArrowY = 576;
				arrowDirection = -5;
			} else {
				// 矢印の動きを止めて攻撃処理実行
				arrowDirection = 0;

				// 攻撃ターンを1消費
				playerAttackTurn--;

				// 矢印位置（攻撃ゲージライン）で攻撃の強さを決定
				if (attackGaugeLain >= 0 && attackGaugeLain <= 106) {
					playerHP_--; // ミス（自分にダメージ）
				}
				if (attackGaugeLain >= 107 && attackGaugeLain <= 159) {
					enemyHP_--; // 弱攻撃
				}
				if (attackGaugeLain >= 160 && attackGaugeLain <= 210) {
					enemyHP_ -= attackGauge2; // 中攻撃
				}
				if (attackGaugeLain >= 211 && attackGaugeLain <= 262) {
					enemyHP_ -= attackGauge3; // 強攻撃
				}
				if (attackGaugeLain >= 263 && attackGaugeLain <= 315) {
					enemyHP_ -= attackGauge2; // 中攻撃
				}
				if (attackGaugeLain >= 316 && attackGaugeLain <= 367) {
					enemyHP_--; // 弱攻撃
				}
				if (attackGaugeLain >= 368 && attackGaugeLain <= 576) {
					playerHP_--; // ミス（自分にダメージ）
				}
			}
		}
	}

	// 矢印スプライトの座標を更新
	attackArrowSprite_->SetPosition({attackArrowX, attackArrowY});

	// 攻撃ゲージライン位置を更新
	attackGaugeLain = attackArrowY + 24;

	//------------------------------------------
	// プレイヤー・敵の更新処理
	//------------------------------------------
	player_->Update();
	enemy_->Update();

	//------------------------------------------
	// カメラ更新
	//------------------------------------------
	camera_.translation_ = Vector3(0.0f, 0.0f, -10.0f);
	camera_.UpdateMatrix();
}

//==================================================
// 描画処理
//==================================================
void GameScene::Draw() {

	//------------------------------------------
	// 3Dモデル描画
	//------------------------------------------
	Model::PreDraw();

	player_->Draw(); // プレイヤー
	enemy_->Draw();  // 敵

	Model::PostDraw();

	//------------------------------------------
	// 2Dスプライト描画
	//------------------------------------------
	Sprite::PreDraw();

	// 攻撃ゲージと矢印を描画
	attackSprite_->Draw();
	attackArrowSprite_->Draw();

	// プレイヤーの残りHP分ハートを描画
	for (int i = 0; i < playerHP_; i++) {
		hearts_[i]->Draw();
	}

	// 敵の残りHP分ハートを描画
	for (int i = 0; i < enemyHP_; i++) {
		enemyHearts_[i]->Draw();
	}

	Sprite::PostDraw();
}

//==================================================
// デストラクタ（終了処理）
//==================================================
GameScene::~GameScene() {

	//------------------------------------------
	// プレイヤー関連の解放
	//------------------------------------------
	for (auto& heart : hearts_) {
		delete heart;
	}
	hearts_.clear();

	delete player_;
	delete modelPlayer_;

	delete attackSprite_;
	delete attackArrowSprite_;

	//------------------------------------------
	// 敵関連の解放
	//------------------------------------------
	delete enemy_;
	delete modelEnemy_;

	for (auto& enemyHeart : enemyHearts_) {
		delete enemyHeart;
	}
	enemyHearts_.clear();

	//------------------------------------------
	// （デバッグカメラは未使用）
	//------------------------------------------
	// delete debugCamera_;
}
