#pragma once

#include "../Utility/SingletonTemplate.h"
#include "../Camera/Camera.h"

/**
* @brief
* �l�̈ꕔ��ۑ��E�񋟂���N���X\n
* ���݃e�X�g���I
*/

class Accessor : public Singleton<Accessor>
{
public:

	void SetCurrGravity(float gravity_) 
	{
		m_gravity_data = gravity_;
	}

	float GetCurrGravity() 
	{
		return m_gravity_data;
	};

	void UpdateCameraPTR(Camera* ptr_) { m_curr_camera_ptr = ptr_; };
	Camera* GetCurrCameraPTR() { return m_curr_camera_ptr; }

protected:

	float m_gravity_data;
	Camera* m_curr_camera_ptr;
private:
	friend Singleton<Accessor>;

	Accessor()
	{
		m_gravity_data = 0.f;
		m_curr_camera_ptr = new Camera();
	};
	virtual ~Accessor()
	{

	};

	Accessor(const Accessor&) = delete;
	Accessor& operator=(const Accessor&) = delete;
	Accessor(const Accessor&&) = delete;
	Accessor& operator=(const Accessor&&) = delete;
};