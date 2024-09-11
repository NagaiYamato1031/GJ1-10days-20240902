#pragma once

#include "IScene.h"

class WinApp;
class DirectXCommon;

namespace ACJPN {
	namespace Scene {

		/// <summary>
		/// シーン更新、削除等の管理するクラス
		/// シーン内でシーン生成させる
		/// </summary>
		class SceneManager final {
		public:
			/// <summary>
			/// 初期化
			/// </summary>
			void Init();
			/// <summary>
			/// 更新
			/// </summary>
			void Update();
			/// <summary>
			/// 描画
			/// </summary>
			void Draw();
		private:
			// ウィンドウ機能
			WinApp* winApp_ = nullptr;
			// 描画用の機能
			DirectXCommon* dxCommon_ = nullptr;

			// 現在のシーン
			IScene* currentScene_ = nullptr;
			// 次に使うシーン
			IScene* nextScene_ = nullptr;

		};

	}
}