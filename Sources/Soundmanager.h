#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

class Soundmanager
{
public:
	Soundmanager();
	void PlaySound(std::string sound);
	void PlayMusic(bool pause);

private:
	std::map<std::string, sf::SoundBuffer> sounds;
	sf::Sound sound;
	sf::Music backgroundMusic;
};