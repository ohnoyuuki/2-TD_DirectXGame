#include "GameScene.h"

//==================================================
// 初期化処理
//==================================================
void GameScene::Initialize() {


	//シーン初期化
	titleScene = true;
	if (stageEnemy1 == 1) {
		playerHP_ = 7;
	}

	

	//-------------------------------
	// 自機のHPハート設定
	//-------------------------------

	// プレイヤーのハート画像を読み込み
	hatoHandle_ = TextureManager::Load("ha-to.png");

	// 複数のスプライトを生成
	for (int i = 0; i < playerHPPoint_; i++) {
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
	for (int i = 0; i < enemyHPPoint_; i++) {
		Sprite* enemyHeart = Sprite::Create(ehatoHadle_, {1000.0f + i * 55.0f, 10.0f});
		enemyHearts_.push_back(enemyHeart);
	}

	// HPの初期値（ハートの数で設定）
	playerHP_ = static_cast<int>(hearts_.size());
	enemyHP_ = static_cast<int>(enemyHearts_.size());

	//-------------------------------
	// プレイヤー設定
	//-------------------------------

	// 3Dモデルの読み込み
	modelPlayer_ = Model::CreateFromOBJ("suraimu");

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
	//-------------------------------
	// 攻撃種類
	//-------------------------------
	//とげ攻撃
	//3Dモデル読み込み
	modelToge_ = Model::CreateFromOBJ("toge");

	toge_ = new Toge();

	toge_->Initialize(modelToge_,&camera_);
	//雷攻撃
	// 3Dモデル読み込み
	modelKami_ = Model::CreateFromOBJ("beam");

	kami_ = new Kaminari();
	kami_->Initialize(modelKami_, &camera_);

	//ビーム攻撃
	
	
	

	// 3Dモデル読み込み
	modelBeam_ = Model::CreateFromOBJ("toge");


	//---------------------------------

	


}

//==================================================
// 更新処理
//==================================================
void GameScene::Update() {

	//タイトルシーン
	if (titleScene == 1) {
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			titleScene = 0;
			stageEnemy1 = 1;
			playerHPPoint_ = 5;
			enemyHPPoint_ = 5;
		}
	}

	if (playerHPPoint_ <= 0) {
		stageEnemy1 = 0;
		stageEnemy2 = 0;
		stageEnemy3 = 0;
		gameOver = 1;
	}


	//------------------------------------------
	// 攻撃ゲージの矢印の移動処理
	//------------------------------------------

	// プレイヤーの攻撃ターンが残っているときのみ動作
	if (playerAttackTurn == 0 && enemyHPPoint_ >= 0) {

		stageEnemy1 = 0;
		stageEnemy2 = 0;
		stageEnemy3 = 0;
		gameOver = 1;
	}

	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1) {

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
					player_->OnDamage(); // ★ ダメージリアクション発動！
					StartCameraShake();
				}
				if (attackGaugeLain >= 107 && attackGaugeLain <= 159) {
					enemyHP_--;          // 弱攻撃
					player_->OnAttack(); // ★ 攻撃モーション発動！
					enemy_->OnDamage(); 
				}
				if (attackGaugeLain >= 160 && attackGaugeLain <= 210) {
					enemyHP_ -= attackGauge2; // 中攻撃
					player_->OnAttack();      // ★ 攻撃モーション発動！
					enemy_->OnDamage(); 
				}
				if (attackGaugeLain >= 211 && attackGaugeLain <= 262) {
					enemyHP_ -= attackGauge3; // 強攻撃
					playerHP_--;
					player_->OnAttack();      // ★ 攻撃モーション発動！
					enemy_->OnDamage(); 
					StartCameraShake();
					kami_->Start(enemy_->GetWorldPosition()); // 敵の上から雷が落ちる！
					;

				}
				if (attackGaugeLain >= 263 && attackGaugeLain <= 315) {
					enemyHP_ -= attackGauge2; // 中攻撃
					player_->OnAttack();      // ★ 攻撃モーション発動！
					enemy_->OnDamage(); 
					toge_->Start(enemy_->GetWorldPosition()); // 敵の下からとげ出現！
				}
				if (attackGaugeLain >= 316 && attackGaugeLain <= 367) {
					enemyHP_--;          // 弱攻撃
					player_->OnAttack(); // ★ 攻撃モーション発動！
					enemy_->OnDamage(); 

					

				}
				if (attackGaugeLain >= 368 && attackGaugeLain <= 576) {
					playerHP_--; // ミス（自分にダメージ）
					player_->OnDamage(); // ★ ダメージリアクション発動！
					StartCameraShake();
				}
			}
		}

		if (stageEnemy1 == 1 && enemyHPPoint_ <= 0) {
			stageEnemy2 = 1;
			playerHPPoint_ = playerHPPoint_ += 1;
			enemyHPPoint_ = 5;
			playerAttackTurn = 3;
			stageEnemy1 = 0;
		}
		if (stageEnemy2 == 1 && enemyHPPoint_ <= 0) {
			stageEnemy3 = 1;
			playerHPPoint_ = playerHPPoint_ += 1;
			enemyHPPoint_ = 5;
			playerAttackTurn = 3;
			stageEnemy2 = 0;
		}
		if (stageEnemy3 == 1 && enemyHPPoint_ <= 0) {
			gameClear = 1;
			stageEnemy3 = 0;
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
	// 攻撃の更新処理
	//------------------------------------------
	toge_->Update();
	kami_->Update();
	


	//------------------------------------------


	



	//------------------------------------------
	// カメラ更新
	//------------------------------------------
	camera_.translation_ = Vector3(0.0f, 0.0f, -10.0f);
	camera_.UpdateMatrix();

	if (isCameraShaking_) {
		cameraShakeTimer_--;
		camera_.translation_.x = defaultCameraPos_.x + (rand() % 100 / 100.0f - 0.5f) * cameraShakePower_;
		camera_.translation_.y = defaultCameraPos_.y + (rand() % 100 / 100.0f - 0.5f) * cameraShakePower_;

		if (cameraShakeTimer_ <= 0) {
			isCameraShaking_ = false;
			camera_.translation_ = defaultCameraPos_;
		}
	} else {
		camera_.translation_ = defaultCameraPos_;
	}
	camera_.UpdateMatrix();

	

}

//==================================================
// 描画処理
//==================================================
void GameScene::Draw() {


	if (stageEnemy1 == 1 || stageEnemy2 == 1 || stageEnemy3 == 1) {

		//------------------------------------------
		// 3Dモデル描画
		//------------------------------------------
		Model::PreDraw();

		player_->Draw(); // プレイヤー
		enemy_->Draw();  // 敵
		toge_->Draw();//とげ攻撃
		kami_->Draw();//雷攻撃
		


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
	// 攻撃の解放
	//------------------------------------------
	//とげ攻撃
	delete toge_;
	delete modelToge_;

	//雷攻撃
	delete kami_;
	delete modelKami_;

	//ビーム攻撃
	
	delete modelBeam_;

	//------------------------------------------
	// （デバッグカメラは未使用）
	//------------------------------------------
	// delete debugCamera_;
}

void GameScene::StartCameraShake() {
	isCameraShaking_ = true;
	cameraShakeTimer_ = 30;   // 揺れるフレーム数
	cameraShakePower_ = 0.1f; // 揺れの強さ
}
