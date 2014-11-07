#include "../Home-Made-Library/Llist.hpp"
#include "../Home-Made-Library/GUI/Button/button.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "string"


float minTime;
sf::Font liberFont;
sf::Text errorMSG;
sf::SoundBufferRecorder recorder;
sf::SoundBuffer buffer;
sf::Sound sound;

void startRecording()
{
	if(!sf::SoundBufferRecorder::isAvailable())
		errorMSG.setString("Please hook up your mic.");
	else
	{
		errorMSG.setString("");
		recorder.start();
	}
}

void stopRecording()
{
	recorder.stop();
	buffer = recorder.getBuffer();
	sound.setBuffer(buffer);
}

void saveRecording()
{
	if (buffer.getDuration().asSeconds() > minTime)
		buffer.saveToFile("Hello.ogg");
}

void playRecording()
{
	sound.play();
	sf::sleep(buffer.getDuration());
}

int main()
{
	// Inits.
	std::string liberFile = "LiberationMono-Regular.ttf";
	liberFont.loadFromFile(liberFile);
	std::string userName = "Steve";
	std::string recordBtnName = "Record_Button.png";
	minTime = 2.f;

	// Buttons and button list.
	std::vector<Button> buttons;
	Button recordbutton(recordBtnName, &startRecording);
	buttons.push_back(recordbutton);
	recordbutton.setPosition(10.f, 10.f);

	// Background texture and sprite.
	sf::Texture background;
	sf::Sprite backgroundSprite;
	background.loadFromFile("TestPage.png");
	backgroundSprite.setTexture(background);
	
	// Error message location, font, etc.
	errorMSG.setPosition(4.f, 4.f);
	errorMSG.setFont(liberFont);
	errorMSG.setString("");
	errorMSG.setColor(sf::Color::Red);

	sf::RenderWindow window(sf::VideoMode(400, 400), "Tic-Talk " + userName);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// If you close the window, exit and end program.
			case sf::Event::Closed:
				stopRecording(); // Stops recording just in case.
				window.close();
				break;

			case sf::Event::KeyPressed:
				// While 'R' is held down, it 'R'ecords the sound.
				if (event.key.code == sf::Keyboard::R)
				{
					startRecording();
				}
				// 'P' = 'Play', or 'Preview'.
				else if (event.key.code == sf::Keyboard::P)
				{
					playRecording();
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					saveRecording();
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

			default:
				recordbutton.handleEvent(event, window);
				break;
			}// Event Switch
		}// Event Loop

		window.clear(sf::Color::Black);
		window.draw(backgroundSprite);
		window.draw(recordbutton);
		window.draw(errorMSG);
		window.display();
	}// Window loop

	return 0;
}
