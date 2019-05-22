#include "pch.h"
#include "Weapon.h"
#include "Consts.h"
#include "BulletManager.h"

Weapon* Weapon::m_pInstance = nullptr;

Weapon::Weapon():
	m_didShoot(false),
	m_runing(true),
	m_pos(METER_HEIGHT * 0.15f, METER_HEIGHT * 0.5f), m_dir(METER_HEIGHT * 0.2f, METER_HEIGHT * 0.5f)
{
	// thread to create a bullet
	std::thread inputThread([this]() {
		std::cout << "Start thread" << std::endl;
		while (this->m_runing)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			int x, y;
			SDL_GetMouseState(&x, &y);
			oxygine::Vector2 lookAt(static_cast<float>(x * METER_PER_PIXEL), static_cast<float>(y * METER_PER_PIXEL));
			m_dir = (lookAt - m_pos).normalized();
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_SPACE] && !m_didShoot)
			{
				m_didShoot = true;
				// Dear reviwer, here is an entry point for your unit test
				BulletManager::GetInstance()->Fire(
					m_pos, // starting point of the bullet on the plane (in meters), left up screen corner is Origin
					m_dir, // dir - direction, normalized vector
					1000,  // bullet speed (m / s),
					2,     // when the bullet will be fired,
					5      // time before bullet disappears.
				
				// Move weapon by means of AWSD
				// Aim to the target by means mouse
				// Fire by means of SPACEBAR
				);
			}
			else if (!state[SDL_SCANCODE_SPACE] && m_didShoot)
			{
				m_didShoot = false;
			}
		}
		std::cout << "Stop thread" << std::endl;
	});
	m_inputThread = std::move(inputThread);
}

Weapon::~Weapon()
{
	this->m_runing = false;
	m_inputThread.join();
	std::cout << "Weapon::~Weapon()" << std::endl;
}

void Weapon::Update(float time)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A])
	{
		m_pos.x -= 50 * METER_PER_PIXEL * time;
	}
	if (state[SDL_SCANCODE_D])
	{
		 m_pos.x += 50 * METER_PER_PIXEL * time;
	}
	if (state[SDL_SCANCODE_W])
	{
		m_pos.y -= 50 * METER_PER_PIXEL * time;
	}
	if (state[SDL_SCANCODE_S])
	{
		m_pos.y += 50 * METER_PER_PIXEL * time;
	}
}

const oxygine::Vector2& Weapon::GetPos() const
{
	return m_pos;
}

const oxygine::Vector2& Weapon::GetDir() const
{
	return m_dir;
}