#include "SceneManager.h"

#include <DirectXCommon.h>
#include <Model.h>
#include <Sprite.h>


#include "Divide/SceneList.h"


using namespace ACJPN;
using namespace ACJPN::Scene;


void ACJPN::Scene::SceneManager::Init() {
	// 機能を取得
	dxCommon_ = DirectXCommon::GetInstance();

	// 最初のシーンを設定し初期化
#ifdef _DEBUG
	currentScene_ = new TestScene;
#endif // _DEBUG
#ifndef _DEBUG
	currentScene_ = new TitleScene;
#endif // !_DEBUG

	currentScene_->Init();
	
	// null にしておく
	nextScene_ = nullptr;
}

void ACJPN::Scene::SceneManager::Update() {

	// 現在のシーンでシーン遷移が始まったかを検知
	if (currentScene_->IsTransition()) {
		// 次のシーンが null の時だけ
		if (nextScene_ == nullptr) {
			// 生成されたものを持ってくる
			// 次のシーンを設定して初期化しておく
			nextScene_ = std::move(currentScene_->nextScene_);
			nextScene_->Init();
		}
		// シーン遷移が終わったタイミング
		if (currentScene_->IsEnd()) {
			// 現在のシーンを削除して設定しなおす
			delete currentScene_;
			currentScene_ = std::move(nextScene_);
			// 間違いがないように null にしておく
			nextScene_ = nullptr;
		}
	}
	// 更新する
	currentScene_->Update();
}

void ACJPN::Scene::SceneManager::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	currentScene_->DrawBackdrop();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	currentScene_->Draw3D();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	currentScene_->DrawOverlay();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
