#include "Audio.h"
#include "Game.h"
//
//Audio::Audio()
//{
//	Game::initSound();
//}
//
//void Audio::addMusicTrack(const char* path)
//{
//	Mix_Music* tpm_music = Mix_LoadMUS(path);
//	if (tpm_music != nullptr)
//	{
//		mMusics.push_back(tpm_music);
//	}
//	else {
//		Mix_GetError();
//	}
//}
//
//void Audio::playMusicTrack(const int which)
//{
//	if (which > mMusics.size())
//	{
//		return;
//	}
//
//	Mix_PlayMusic(mMusics.at(which), - 1);
//	m_Playing = true;
//}
//
//void Audio::Play_Pause()
//{
//	if (m_Playing && !m_Paused)
//	{
//		Mix_PauseMusic();
//		m_Paused = true;
//	}
//	else if (m_Playing && m_Paused)
//	{
//		Mix_ResumeMusic();
//		m_Paused = false;
//	}
//	else
//	{
//		return;
//	}
//
//}