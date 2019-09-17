#pragma once
#include "MenuManager.h"
#include "Texture.h"


class MenuExtra
{
public:
	explicit MenuExtra(MenuManager& manager);
	MenuExtra(const MenuExtra&) = delete;
	MenuExtra& operator=(const MenuExtra&) = delete;
	~MenuExtra() = default;

	void Update(float elapsedSec);

	void DrawExtraMain() const;
	void DrawExtraOptions() const;

	void DrawExtraStory() const;

	void DrawExtraCredits() const;

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e) const;
	void MouseClickBack(const SDL_MouseButtonEvent& e) const;

private:
	MenuManager& m_Manager;

	std::vector<std::unique_ptr<Texture>> m_pExtraMenuText;
	std::unique_ptr<Texture> m_VolumeCounterStreamCounter;
	std::unique_ptr<Texture> m_VolumeCounterSFXcounter;
	std::unique_ptr<Texture> m_VolumeZero;


	Texture m_StoryTexture;
	Texture m_OptionsTexture;
	Texture m_CreditsTexture;
	Point2f m_MousePos;

	int m_VolumeCounter{};
	int m_VolumeCounterPrevious{};

	int m_VolumeCounterSFX{};
	int m_VolumeCounterPreviousSFX{};
};
