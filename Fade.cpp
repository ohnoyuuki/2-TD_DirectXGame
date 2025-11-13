#include "Fade.h"


Fade::Fade() {}
Fade::~Fade() { delete fadeSprite_; }

void Fade::Initialize() {
	// 黒テクスチャ（1×1ピクセルの黒画像を作るか、既存テクスチャIDを使う）
	fadeHandle_ = TextureManager::Load("white1x1.png");

	// スプライト生成（ここを先に！）
	fadeSprite_ = Sprite::Create(fadeHandle_, {0, 0});

	// 画面全体に拡大
	fadeSprite_->SetSize({1280.0f, 720.0f});

	// 画面中央に配置
	fadeSprite_->SetPosition({640.0f, 360.0f});

	// 初期の色（alpha を反映）
	float a = alpha_ / 255.0f;
	// Vector4(r,g,b,a) と仮定（r,g,b が 0 = 黒）
	// 黒で初期化
	fadeSprite_->SetColor(Vector4{0.0f, 0.0f, 0.0f, a});

	// ※ "white1x1.png" は1ピクセルの白画像でOK
	//    存在しない場合、全画面矩形をシェーダーで描く方式でも可
	

	
}

void Fade::FadeIn() {
	fadeIn_ = true;
	isFading_ = true;
	alpha_ = 255;
}

void Fade::FadeOut() {
	fadeIn_ = false;
	isFading_ = true;
	alpha_ = 0;
}

void Fade::Update() {
	if (!isFading_)
		return;

	if (fadeIn_) {
		alpha_ -= fadeSpeed_;
		if (alpha_ <= 0) {
			alpha_ = 0;
			isFading_ = false;
		}
	} else {
		alpha_ += fadeSpeed_;
		if (alpha_ >= 255) {
			alpha_ = 255;
			isFading_ = false;
		}
	}
	// Vector4 に変換してセット（0..1 の正規化）
	float a = static_cast<float>(alpha_) / 255.0f;
	fadeSprite_->SetColor(Vector4{0.0f, 0.0f, 0.0f, a});

}

void Fade::Draw() {
	if (fadeSprite_) {
		fadeSprite_->Draw();
	}
}
