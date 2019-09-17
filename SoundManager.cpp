#include "stdafx.h"
#include "SoundManager.h"

std::map<std::string, SoundStream> SoundManager::m_SoundStreamMap{};
std::map<std::string, SoundEffect> SoundManager::m_SoundEffectMap{};

SoundManager::SoundManager()
{
	InitSoundEffects();
	InitSoundStreams();
}

void SoundManager::InitSoundStreams()
{
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("Story", SoundStream{"Resources/Sound/Music/Story.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("Intro", SoundStream{"Resources/Sound/Music/Intro.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("LevelOne", SoundStream{"Resources/Sound/Music/LevelOne.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("Boss", SoundStream{"Resources/Sound/Music/boss.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("End", SoundStream{"Resources/Sound/Music/end.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("LevelFour", SoundStream{"Resources/Sound/Music/levelfour.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("LevelTwo", SoundStream{"Resources/Sound/Music/leveltwo.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("LevelThree", SoundStream{"Resources/Sound/Music/levelthree.mp3"}));
	m_SoundStreamMap.insert(std::pair<std::string, SoundStream>("Credits", SoundStream{"Resources/Sound/Music/Credits.mp3"}));
	m_SoundStreamMap.begin()->second.SetVolume(100);
}

void SoundManager::InitSoundEffects()
{
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Grass", SoundEffect{"Resources/Sound/Sound_Effects/Grass.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Jump", SoundEffect{"Resources/Sound/Sound_Effects/Jump.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Death", SoundEffect{"Resources/Sound/Sound_Effects/Death.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Lever", SoundEffect{"Resources/Sound/Sound_Effects/Lever.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Blade", SoundEffect{"Resources/Sound/Sound_Effects/Blade.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Saw", SoundEffect{"Resources/Sound/Sound_Effects/Saw.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Wind", SoundEffect{"Resources/Sound/Sound_Effects/Wind.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("LifeUp", SoundEffect{"Resources/Sound/Sound_Effects/LifeUp.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Teleport", SoundEffect{"Resources/Sound/Sound_Effects/Teleport.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Wind2", SoundEffect{"Resources/Sound/Sound_Effects/Wind02.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Laser", SoundEffect{"Resources/Sound/Sound_Effects/Laser.mp3"}));
	m_SoundEffectMap.insert(std::pair<std::string, SoundEffect>("Coin", SoundEffect{"Resources/Sound/Sound_Effects/Coin.mp3"}));
	m_SoundEffectMap.begin()->second.SetVolume(100);
}

void SoundManager::PlaySoundStream(const std::string& name, bool repeat)
{
	m_SoundStreamMap.find(name)->second.Play(repeat);
}

void SoundManager::PlaySoundEffect(const std::string& name, bool repeat, bool isPlaying)
{
	if (isPlaying)
	{
		if (!IsPlaying(name))
		{
			m_SoundEffectMap.find(name)->second.Play(repeat);
		}
	}
	else
	{
		m_SoundEffectMap.find(name)->second.Play(repeat);
	}
}

void SoundManager::PlaySoundEffectTraps(const Vector2f& player, const Vector2f& trapPos, const std::string& name, bool repeat, bool isPlaying)
{
	if (isPlaying)
	{
		if (!IsPlaying(name))
		{
			m_SoundEffectMap.find(name)->second.PlaySoundEffectTraps(player, trapPos);
		}
	}
	else
	{
		m_SoundEffectMap.find(name)->second.PlaySoundEffectTraps(player, trapPos);
	}
}


void SoundManager::VolumeUpSoundEffect()
{
	m_SoundEffectMap.begin()->second.SetVolume(m_SoundEffectMap.begin()->second.GetVolume() + 10);

	if (m_SoundEffectMap.begin()->second.GetVolume() >= 100)
	{
		m_SoundEffectMap.begin()->second.SetVolume(100);
	}
}

void SoundManager::VolumeDownSoundEffect()
{
	if (m_SoundEffectMap.begin()->second.GetVolume() <= 10)
	{
		m_SoundEffectMap.begin()->second.SetVolume(0);
	}
	else
	{
		m_SoundEffectMap.begin()->second.SetVolume(m_SoundEffectMap.begin()->second.GetVolume() - 10);
	}
	std::cout << m_SoundEffectMap.begin()->second.GetVolume() << std::endl;
}

int SoundManager::GetVolumeSoundEffect()
{
	return m_SoundEffectMap.begin()->second.GetVolume();
}

void SoundManager::StopSoundEffect(const std::string& name)
{
	m_SoundEffectMap.find(name)->second.Stop();
}

void SoundManager::Update(const Vector2f& player, const Vector2f& trapPos, const std::string& name)
{
	std::map<std::string, SoundEffect>::iterator it{m_SoundEffectMap.find(name)};

	if (it != m_SoundEffectMap.end())
	{
		it->second.Update(player, trapPos);
	}
}

void SoundManager::VolumeUpSoundStream()
{
	m_SoundStreamMap.begin()->second.SetVolume(m_SoundStreamMap.begin()->second.GetVolume() + 10);

	if (m_SoundStreamMap.begin()->second.GetVolume() >= 100)
	{
		m_SoundStreamMap.begin()->second.SetVolume(100);
	}
}

void SoundManager::VolumeDownSoundStream()
{
	if (m_SoundStreamMap.begin()->second.GetVolume() <= 10)
	{
		m_SoundStreamMap.begin()->second.SetVolume(0);
	}
	else
	{
		m_SoundStreamMap.begin()->second.SetVolume(m_SoundStreamMap.begin()->second.GetVolume() - 10);
	}
	std::cout << m_SoundStreamMap.begin()->second.GetVolume() << std::endl;
}

int SoundManager::GetVolumeSoundStream()
{
	return m_SoundStreamMap.begin()->second.GetVolume();
}

bool SoundManager::IsPlaying(std::string name)
{
	for (int i = 0; i < Mix_AllocateChannels(-1); i++)
	{
		if (m_SoundEffectMap.find(name)->second.IsPlaying(i))
		{
			return true;
		}
	}
	return false;
}
