#ifndef SINGLETONTEMPLATE_H_
#define SINGLETONTEMPLATE_H_

template<class T>
class Singleton {

	//シングルトンデザインパターン
public:

	//実体を作る関数
	static void CreateInstance() {
		if (IsNull() == true) {
			p_Instance = new T();
		}
	}

	//実体を破棄する関数
	static void DestroyInstance() {
		if (IsNull() == false) {
			delete p_Instance;
		}
	}

	//実体が存在するか確認する変数
	static bool IsNull() {
		return p_Instance == nullptr;
	}

	//実体を取得する関数
	static T* GetInstance() {
		if (IsNull() == true) {
			CreateInstance();
		}
		return p_Instance;
	}
protected:
	Singleton() {}	//コンストラクタ抑制
	~Singleton() {}	//デストラクタ抑制



private:
	static T* p_Instance;	//自分自身の唯一の実体
};
//staticなメンバ変数を初期化【コンストラクタではやらない】
template<class T>
T* Singleton<T>::p_Instance = nullptr;


#endif