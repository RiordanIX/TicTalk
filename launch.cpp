#include "../Home-Made-Library/Llist.hpp"
#include "../Home-Made-Library/GUI/Button/button.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "string"

sf::Font liberFont;
sf::Text errorMSG;
sf::SoundBufferRecorder recorder;
sf::SoundBuffer buffer;
sf::Sound sound;


void stopRecording()
{
	recorder.stop();
	buffer = recorder.getBuffer();
	sound.setBuffer(buffer);
	sound.play();
	sf::sleep(buffer.getDuration());
	sound.resetBuffer();
}

int main()
{
	// Inits.
	std::string liberFile = "LiberationMono-Regular.ttf";
	liberFont.loadFromFile(liberFile);
	std::string userName = "Pete";
	// Error message location, font, etc.
	errorMSG.setPosition(4.f, 4.f);
	errorMSG.setFont(liberFont);
	//errorMSG.setCharacterSize(14);
	errorMSG.setString("");
	errorMSG.setColor(sf::Color::Red);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Tic-Talk " + userName);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// If you close the window, exit and end program.
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				// While 'R' is held down, it records the sound.
				if (event.key.code == sf::Keyboard::R)
				{
					if(!sf::SoundBufferRecorder::isAvailable())
						errorMSG.setString("Please hook up your mic.");
					else
					{
						errorMSG.setString("");
						recorder.start();
					}
				}
				break;

			case sf::Event::KeyReleased:
				// Once 'R' is released, sound stops recording and plays back.
				if (event.key.code == sf::Keyboard::R)
				{
					stopRecording();
				}
				break;
				// If you leave the window, stop recording.
			case sf::Event::LostFocus:
				stopRecording();
				break;
			}
		}

		window.clear(sf::Color::Black);
		window.draw(errorMSG);
		window.display();
	}
	return 0;
}
