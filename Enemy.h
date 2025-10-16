#include "KamataEngine.h"

using namespace KamataEngine;

class Enemy {
public:
	// 初期化
	void Initialize(Model* model, Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

	 // ダメージを受けたとき呼ばれる関数
	void OnDamage();

private:
	// ワールド変換データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;

	// カメラ
	Camera* camera_ = nullptr;

	// ノックバック関連
	bool isDamaged_ = false;
	int damageTimer_ = 0;
	float knockbackPower_ = 0.1f; // ノックバックの強さ（大きくしたければ0.2f〜0.3fに）
};