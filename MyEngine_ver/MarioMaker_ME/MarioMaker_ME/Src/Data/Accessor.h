#pragma once

#include "../Utility/SingletonTemplate.h"

class Accessor : public Singleton<Accessor>
{
public:

	void SetGravity(float gravity_) 
	{
		m_gravity_data = gravity_;
	}

	float GetGravity() 
	{
		return m_gravity_data;
	};

protected:

	float m_gravity_data;

private:
	friend Singleton<Accessor>;

	Accessor()
	{
		m_gravity_data = 0.f;
	};
	virtual ~Accessor()
	{

	};

	Accessor(const Accessor&) = delete;
	Accessor& operator=(const Accessor&) = delete;
	Accessor(const Accessor&&) = delete;
	Accessor& operator=(const Accessor&&) = delete;
};