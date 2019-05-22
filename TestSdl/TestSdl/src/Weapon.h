#pragma once
#include "math/Vector2.h"
class Weapon
{
public:
	Weapon();
	~Weapon();
	void Update(float time);
	const oxygine::Vector2& GetPos() const;
	const oxygine::Vector2& GetDir() const;
private:
	static Weapon* m_pInstance;
	bool m_didShoot;
	bool m_runing;
	oxygine::Vector2 m_pos;
	oxygine::Vector2 m_dir;
	std::thread m_inputThread;
};