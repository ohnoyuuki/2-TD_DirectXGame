#pragma once
#include "KamataEngine.h"


using namespace KamataEngine;


class Fade {
public:
	Fade();
	~Fade();

	// 初期化
	void Initialize();

	// フェード制御
	void FadeIn();  // 明るくなる
	void FadeOut(); // 暗くなる

	// 更新・描画
	void Update();
	void Draw();

	// 状態チェック
	bool IsFading() const { return isFading_; }
	bool IsFadeInEnd() const { return (!isFading_ && fadeIn_ && alpha_ == 0); }
	bool IsFadeOutEnd() const { return (!isFading_ && !fadeIn_ && alpha_ == 255); }

private:
	uint32_t fadeHandle_ = 0;
	Sprite*fadeSprite_ = nullptr;
	int alpha_ = 255;       // 透明度（0 = 透明, 255 = 黒）
	int fadeSpeed_ = 8;     // フェード速度
	bool fadeIn_ = false;   // 明転中か暗転中か
	bool isFading_ = false; // フェード中フラグ
};