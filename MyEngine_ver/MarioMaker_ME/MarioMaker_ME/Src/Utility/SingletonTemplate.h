#pragma once

template<class T>
class Singleton 
{
public:
	static void CreateInstance()
	{
		if (IsNull() == true) { ptr_instance = new T(); }
	}
	static void DestroyInstance()
	{
		if(IsNull() == false) {	delete ptr_instance; }
	}
	static bool IsNull()
	{
		return ptr_instance == nullptr;
	}
	static T* GetInstance()
	{
		return ptr_instance;
	}
protected:
	Singleton(){}
	~Singleton(){}
private:
	static T* ptr_instance;
};

template <class T>
T* Singleton<T>::ptr_instance = nullptr;