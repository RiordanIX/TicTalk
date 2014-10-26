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
	errorMSG.setColor(sf::Color::Black);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Tic-Talk " + userName);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
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
				if (event.key.code == sf::Keyboard::R)
				{
					recorder.stop();
					buffer = recorder.getBuffer();
					sound.setBuffer(buffer);
					sound.play();
					sf::sleep(buffer.getDuration());
					sound.resetBuffer();
				}
			}
		}

		window.clear(sf::Color::Blue);
		window.draw(errorMSG);
		window.display();
	}
	return 0;
}
