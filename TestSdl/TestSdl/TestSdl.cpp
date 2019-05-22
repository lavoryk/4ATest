// TestSdl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "src/BulletManager.h"
#include "src/Weapon.h"
#include "src/Consts.h"
// using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
	std::srand(static_cast<unsigned int>(time(0)));
	if (SDL_Init(SDL_INIT_VIDEO) == 0) 
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		BulletManager::Init();
		if (SDL_CreateWindowAndRenderer(static_cast<int>(PIXEL_WIDTH), static_cast<int>(PIXEL_HEIGHT), 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;
			const std::chrono::duration<float, std::ratio<1, 60>> SPF60{ 1 };
			// const std::chrono::duration<float, std::ratio<1, 30>> SPF30{ 1 };
			std::chrono::duration<float> elapsed = SPF60;
			auto start = std::chrono::high_resolution_clock::now();
			BulletManager* const pBulletManager = BulletManager::GetInstance();
			std::unique_ptr<Weapon> pWeapon = std::make_unique<Weapon>();

			while (!done) 
			{
				float time = elapsed.count();
				pBulletManager->Update(time);
				pWeapon->Update(time);
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				SDL_RenderSetScale(renderer, PIXEL_PER_METER, PIXEL_PER_METER);
				// SDL_RenderSetLogicalSize(renderer, METER_WIDTH, METER_HEIGHT);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

				// Draw walls
				for (const auto& wall : pBulletManager->GetWalls())
				{
					if (!wall->GetDestroyed())
					{
						const auto& line = wall->GetLineSegment2();
						SDL_RenderDrawLine(renderer, (int)line.p1.x, (int)line.p1.y, (int)line.p2.x, (int)line.p2.y);
					}
				}

				// Draw bullets
				for (const auto& bullet : pBulletManager->GetBullets())
				{
#ifdef  DEBUG_HIT_POINT
					SDL_Rect hitRect{
						static_cast<int>(bullet->GetHitPos().x - 5 * METER_PER_PIXEL),
						static_cast<int>(bullet->GetHitPos().y - 5 * METER_PER_PIXEL),
						static_cast<int>(10 * METER_PER_PIXEL),
						static_cast<int>(10 * METER_PER_PIXEL) };
					SDL_RenderFillRect(renderer, &hitRect);
					
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_Rect nearestRect{
						static_cast<int>(bullet->GetNearestPos().x - 5 * METER_PER_PIXEL),
						static_cast<int>(bullet->GetNearestPos().y - 5 * METER_PER_PIXEL),
						static_cast<int>(10 * METER_PER_PIXEL),
						static_cast<int>(10 * METER_PER_PIXEL) };
					SDL_RenderFillRect(renderer, &nearestRect);
#endif //  DEBUG_HIT_POINT

					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_Rect bulletRect{
						static_cast<int>(bullet->Pos().x - 2 * METER_PER_PIXEL),
						static_cast<int>(bullet->Pos().y - 2 * METER_PER_PIXEL),
						static_cast<int>(4 * METER_PER_PIXEL),
						static_cast<int>(4 * METER_PER_PIXEL) };
					SDL_RenderFillRect(renderer, &bulletRect);
				}

				// Draw weapon
				{
					const auto& dir = pWeapon->GetDir();
					const auto& position = pWeapon->GetPos();
					SDL_Rect weaponRect;
					weaponRect.x = static_cast<int>(position.x - 4 * METER_PER_PIXEL);
					weaponRect.y = static_cast<int>(position.y - 4 * METER_PER_PIXEL);
					weaponRect.w = static_cast<int>(8 * METER_PER_PIXEL);
					weaponRect.h = static_cast<int>(8 * METER_PER_PIXEL);
					SDL_RenderDrawRect(renderer, &weaponRect);
					auto la = dir;
					la.normalizeTo(40 * METER_PER_PIXEL);
					la += position;
					SDL_RenderDrawLine(renderer,
						static_cast<int>(position.x), static_cast<int>(position.y),
						static_cast<int>(la.x), static_cast<int>(la.y));
				}

				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) 
				{
					if (event.type == SDL_QUIT) 
					{
						done = SDL_TRUE;
					}
				}
				auto end = std::chrono::high_resolution_clock::now();
				elapsed = end - start;

				if (elapsed < SPF60)
				{
					std::this_thread::sleep_for(SPF60 - elapsed);
					elapsed = SPF60;
					start = std::chrono::high_resolution_clock::now();
				}
				else
				{
					start = end;
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
		BulletManager::Deinit();
	}
	SDL_Quit();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
