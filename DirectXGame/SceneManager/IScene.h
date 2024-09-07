#pragma once

#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"

/// <summary>
/// KamataEngine の上に配置する便利系リファレンス
/// </summary>
namespace ACJPN {
	/// <summary>
	/// シーン関係
	/// </summary>
	namespace Scene {

		/// <summary>
		/// シーン遷移を円滑にするための構造体
		/// </summary>
		struct SceneFlag {
			// シーンが完全に終了したことを示す変数
			// すべての処理が終わったか
			bool allEnd_ = false;
			// シーン遷移が始まったことを示す変数
			// シーン遷移中か
			bool isTransition_ = false;
		};

		/// <summary>
		/// すべてのシーンの継承元
		/// </summary>
		class IScene {
		public: //** メンバ関数 **//

			IScene() {
				// インスタンスを取得する
				input_ = Input::GetInstance();
				audio_ = Audio::GetInstance();
			}
			virtual ~IScene() = default;

			/// <summary>
			/// 初期化
			/// </summary>
			virtual void Init() = 0;
			/// <summary>
			/// 更新
			/// </summary>
			virtual void Update() = 0;
			/// <summary>
			/// 背景の描画
			/// </summary>
			virtual void DrawBackdrop() {}
			/// <summary>
			/// 3D モデルの描画
			/// </summary>
			virtual void Draw3D() {}
			/// <summary>
			/// UI の描画
			/// </summary>
			virtual void DrawOverlay() {}

			/// <summary>
			/// デバッグ情報の表示
			/// </summary>
			virtual void DebugWindow() {}

			/// <summary>
			/// シーンの処理がすべて終わったかを返す
			/// </summary>
			bool IsEnd() const { return sceneFlag_.allEnd_; }
			/// <summary>
			/// シーン遷移が始まったことを返す
			/// </summary>
			/// <returns></returns>
			bool IsTransition() const { return sceneFlag_.isTransition_; }

		public:
			/// <summary>
			/// 次に使うシーンを保存のみする
			/// すぐにシーンマネージャーに渡される
			/// </summary>
			IScene* nextScene_ = nullptr;

		protected: //** 継承メンバ変数 **//
			SceneFlag sceneFlag_;

			// 入力管理
			Input* input_ = nullptr;
			// 音声管理
			Audio* audio_ = nullptr;
		};
	} // namespace Scene
} // namespace ACJPN