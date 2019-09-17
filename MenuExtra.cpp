#include "stdafx.h"
#include "MenuExtra.h"
#include "MenuManager.h"
#include "utils.h"
#include "SoundManager.h"


MenuExtra::MenuExtra(MenuManager& manager)
	: m_Manager{manager}
	  , m_StoryTexture{"Resources/Images/Menu/StoryMenu.png"}
	  , m_OptionsTexture{"Resources/Images/Menu/Options.png"}
	  , m_CreditsTexture{"Resources/Images/Menu/CreditsMenu.png"}
{
	m_pExtraMenuText.push_back(std::make_unique<Texture>("Back", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pExtraMenuText.push_back(std::make_unique<Texture>("Story", "Resources/Fonts/Font00.ttf", 40, Color4f{1,1,1,1}));
	m_pExtraMenuText.push_back(std::make_unique<Texture>("Options", "Resources/Fonts/Font00.ttf", 40, Color4f{1,1,1,1}));
	m_pExtraMenuText.push_back(std::make_unique<Texture>("Credits", "Resources/Fonts/Font00.ttf", 40, Color4f{1,1,1,1}));
	m_pExtraMenuText.push_back(std::make_unique<Texture>(std::to_string(m_VolumeCounter), "Resources/Fonts/Font00.ttf", 12, Color4f{1,1,1,1}));
	m_VolumeZero = std::make_unique<Texture>("0", "Resources/Fonts/Font00.ttf", 50, Color4f(1, 1, 1, 1));
}

void MenuExtra::Update(float elapsedSec)
{
	m_VolumeCounter = SoundManager::GetVolumeSoundStream();
	m_VolumeCounterSFX = SoundManager::GetVolumeSoundEffect();

	if (m_VolumeCounterPrevious != m_VolumeCounter)
	{
		m_VolumeCounterStreamCounter = std::make_unique<Texture>(std::to_string(m_VolumeCounter), "Resources/Fonts/Font00.ttf", 50, Color4f(1, 1, 1, 1));
	}

	if (m_VolumeCounterPreviousSFX != m_VolumeCounterSFX)
	{
		m_VolumeCounterSFXcounter = std::make_unique<Texture>(std::to_string(m_VolumeCounterSFX), "Resources/Fonts/Font00.ttf", 50, Color4f(1, 1, 1, 1));
	}
}

void MenuExtra::DrawExtraMain() const
{
	utils::SetColor({0,0,0,0.4f});

	utils::FillRect({30,620,250,70});// back button draw
	utils::FillRect({515,420,250,70});//first
	utils::FillRect({515,320,250,70});//mid
	utils::FillRect({515,220,250,70});//second

	m_pExtraMenuText[0]->Draw({75,620}); // back
	m_pExtraMenuText[1]->Draw({585,430}); // story
	m_pExtraMenuText[2]->Draw({560,330}); // Options
	m_pExtraMenuText[3]->Draw({570,230}); // credit

	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		utils::DrawRect({30,620,250,70}, 5.0f);// border back
	}

	if (m_MousePos.x >= 515 && m_MousePos.x <= 765)
	{
		if (m_MousePos.y >= 420 && m_MousePos.y <= 490)
		{
			utils::DrawRect({515,420,250,70}, 5.0f);//Story
		}
		else if (m_MousePos.y >= 320 && m_MousePos.y <= 390)
		{
			utils::DrawRect({515,320,250,70}, 5.0f);//Options
		}
		else if (m_MousePos.y >= 220 && m_MousePos.y <= 290)
		{
			utils::DrawRect({515,220,250,70}, 5.0f);//Credits
		}
	}
}

void MenuExtra::DrawExtraStory() const
{
	utils::SetColor({0,0,0,0.4f});
	utils::FillRect({30,620,250,70});// back button draw
	utils::FillRect({30,40,1220,565});// large border
	m_pExtraMenuText[0]->Draw({75,620}); // back

	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		utils::DrawRect({30,620,250,70}, 5.0f);// border back
	}

	m_StoryTexture.Draw(Rectf(0, 0, 1280, 720));
}

void MenuExtra::DrawExtraOptions() const
{
	utils::SetColor({0,0,0,0.4f});
	utils::FillRect({30,620,250,70});// back button draw
	utils::FillRect({30,40,1220,565});// large border
	m_pExtraMenuText[0]->Draw({75,620}); // back

	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		utils::DrawRect({30,620,250,70}, 5.0f);// border back
	}
	m_OptionsTexture.Draw(Rectf(0, 0, 1280, 720));
	utils::SetColor({0,0,0,1});

	//MUSIC
	if (m_MousePos.y >= 338 && m_MousePos.y <= 418)
	{
		if (m_MousePos.x >= 166 && m_MousePos.x <= 246)
		{
			utils::DrawRect({166,338,80,80}, 5.0f); // + music
		}
		if (m_MousePos.x >= 295 && m_MousePos.x <= 375)
		{
			utils::DrawRect({295,338,80,80}, 5.0f); // - music
		}
	}

	//SFX
	if (m_MousePos.x >= 164 && m_MousePos.x <= 244 && m_MousePos.y >= 80 && m_MousePos.y <= 160)
	{
		utils::DrawRect({164,80,80,80}, 5.0f); // + sfx 
	}
	if (m_MousePos.x >= 292 && m_MousePos.x <= 372 && m_MousePos.y >= 80 && m_MousePos.y <= 160)
	{
		utils::DrawRect({292,80,80,80}, 5.0f); // - sfx
	}


	//FULL SCREEN
	if (m_MousePos.x >= 890 && m_MousePos.x <= 970 && m_MousePos.y >= 338 && m_MousePos.y <= 418)
	{
		utils::DrawRect({890,338,80,80}, 5.0f); // fullscreen on
	}
	if (m_MousePos.x >= 1018 && m_MousePos.x <= 1098 && m_MousePos.y >= 336 && m_MousePos.y <= 416)
	{
		utils::DrawRect({1018,336,80,80}, 5.0f); // fullscreen off
	}

	//VSYNC
	if (m_MousePos.x >= 890 && m_MousePos.x <= 970 && m_MousePos.y >= 82 && m_MousePos.y <= 162)
	{
		utils::DrawRect({890,82,80,80}, 5.0f); // Vsync on
	}
	if (m_MousePos.x >= 1018 && m_MousePos.x <= 1098 && m_MousePos.y >= 82 && m_MousePos.y <= 162)
	{
		utils::DrawRect({1018,82,80,80}, 5.0f); // Vsync off
	}

	// volume music counter
	if (m_VolumeCounter >= 10)
	{
		m_VolumeCounterStreamCounter->Draw({505,350,0,0});
	}

	if (m_VolumeCounter == 0)
	{
		m_VolumeZero->Draw({515,350,0,0});
	}


	// volume music counter
	if (m_VolumeCounterSFX >= 10)
	{
		m_VolumeCounterSFXcounter->Draw({505,90,0,0});
	}

	if (m_VolumeCounterSFX == 0)
	{
		m_VolumeZero->Draw({515,90,0,0});
	}
}

void MenuExtra::DrawExtraCredits() const
{
	utils::SetColor({0,0,0,0.4f});
	utils::FillRect({30,620,250,70});// back button draw
	utils::FillRect({30,40,1220,565});// large border
	m_pExtraMenuText[0]->Draw({75,620}); // back

	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		utils::DrawRect({30,620,250,70}, 5.0f);// border back
	}

	m_CreditsTexture.Draw(Rectf(0, 0, 1280, 720));
}

void MenuExtra::MouseMoved(const Point2f& mousePos)
{
	m_MousePos = mousePos;
}

void MenuExtra::MouseClick(const SDL_MouseButtonEvent& e) const
{
	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		m_Manager.SetState(MenuManager::MenuState::menuMain);
	}

	if (m_MousePos.x >= 515 && m_MousePos.x <= 765)
	{
		if (m_MousePos.y >= 420 && m_MousePos.y <= 490)
		{
			m_Manager.SetState(MenuManager::MenuState::menuExtraStory);//Story
		}
		else if (m_MousePos.y >= 320 && m_MousePos.y <= 390)
		{
			m_Manager.SetState(MenuManager::MenuState::menuExtraOptions);//Information
		}
		else if (m_MousePos.y >= 220 && m_MousePos.y <= 290)
		{
			m_Manager.SetState(MenuManager::MenuState::menuExtraCredits);//Credits
		}
	}


	if (m_MousePos.x >= 166 && m_MousePos.x <= 246 && m_MousePos.y >= 338 && m_MousePos.y <= 418)
	{
		SoundManager::VolumeUpSoundStream(); // + music
	}

	if (m_MousePos.x >= 295 && m_MousePos.x <= 375 && m_MousePos.y >= 338 && m_MousePos.y <= 418)
	{
		SoundManager::VolumeDownSoundStream(); // - music
	}

	if (m_MousePos.x >= 164 && m_MousePos.x <= 244 && m_MousePos.y >= 80 && m_MousePos.y <= 160)
	{
		SoundManager::VolumeUpSoundEffect(); // + sfx
	}

	if (m_MousePos.x >= 292 && m_MousePos.x <= 372 && m_MousePos.y >= 80 && m_MousePos.y <= 160)
	{
		SoundManager::VolumeDownSoundEffect(); // - sfx
	}

	//FULL SCREEN
	if (m_MousePos.x >= 890 && m_MousePos.x <= 970 && m_MousePos.y >= 338 && m_MousePos.y <= 418)
	{
		m_Manager.FullScreenOn(); // fullscreen on
	}
	if (m_MousePos.x >= 1018 && m_MousePos.x <= 1098 && m_MousePos.y >= 336 && m_MousePos.y <= 416)
	{
		m_Manager.FullScreenOff(); // fullscreen off
	}

	if (m_MousePos.x >= 890 && m_MousePos.x <= 970 && m_MousePos.y >= 82 && m_MousePos.y <= 162)
	{
		m_Manager.VsyncOn();// Vsync on
	}
	if (m_MousePos.x >= 1018 && m_MousePos.x <= 1098 && m_MousePos.y >= 82 && m_MousePos.y <= 162)
	{
		m_Manager.VsyncOff(); // Vsync off
	}
}

void MenuExtra::MouseClickBack(const SDL_MouseButtonEvent& e) const
{
	if (m_MousePos.x >= 20 && m_MousePos.x <= 270 && m_MousePos.y >= 620 && m_MousePos.y <= 690)
	{
		m_Manager.SetState(MenuManager::MenuState::menuExtra);
	}
}
