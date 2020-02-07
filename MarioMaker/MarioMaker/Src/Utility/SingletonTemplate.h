#ifndef SINGLETONTEMPLATE_H_
#define SINGLETONTEMPLATE_H_

template<class T>
class Singleton {

	//�V���O���g���f�U�C���p�^�[��
public:

	//���̂����֐�
	static void CreateInstance() {
		if (IsNull() == true) {
			p_Instance = new T();
		}
	}

	//���̂�j������֐�
	static void DestroyInstance() {
		if (IsNull() == false) {
			delete p_Instance;
		}
	}

	//���̂����݂��邩�m�F����ϐ�
	static bool IsNull() {
		return p_Instance == nullptr;
	}

	//���̂��擾����֐�
	static T* GetInstance() {
		if (IsNull() == true) {
			CreateInstance();
		}
		return p_Instance;
	}
protected:
	Singleton() {}	//�R���X�g���N�^�}��
	~Singleton() {}	//�f�X�g���N�^�}��



private:
	static T* p_Instance;	//�������g�̗B��̎���
};
//static�ȃ����o�ϐ����������y�R���X�g���N�^�ł͂��Ȃ��z
template<class T>
T* Singleton<T>::p_Instance = nullptr;


#endif