#include "Soundmanager.h"

Soundmanager::Soundmanager()
{
	sf::SoundBuffer snd;
	if (!backgroundMusic.openFromFile("Resources/Background.ogg"))
		std::cout << "Error: Could not load music file \"Background.ogg\"\n";
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(70.0f);

	if (!snd.loadFromFile("Resources/Hover.wav"))
		std::cout << "Error: Could not load sound file \"Hover.wav\"\n";
	sounds.insert(std::make_pair("Click", snd));

	if (!snd.loadFromFile("Resources/Clear.ogg"))
		std::cout << "Error: Could not load sound file \"Clear.ogg\"\n";
	sounds.insert(std::make_pair("Clear", snd));

	if (!snd.loadFromFile("Resources/Gameover.wav"))
		std::cout << "Error: Could not load sound file \"Gameover.wav\"\n";
	sounds.insert(std::make_pair("Gameover", snd));
}

void Soundmanager::PlaySound(std::string sound)
{
	this->sound.setBuffer(sounds.at(sound));
	this->sound.play();
}

void Soundmanager::PlayMusic(bool pause)
{
	if (pause)
		backgroundMusic.pause();
	else
		backgroundMusic.play();
}