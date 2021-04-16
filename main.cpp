#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <string>

const int WINDOWWIGHT = 1000;  // Window wight
const int WINDOWHEIGHT = 600;  // Window height
const int FPS = 60;            // FPS
sf::Font retroFont;
bool runMainLoop = true;

class Dino {
	public:
	sf::Texture dinoTexture;    // Creating dino texture
	sf::Sprite dinoSprite;      // Creating dino sprite
	int dinoWidht, dinoHeight;  // Dino wight and height

	Dino(const std::string &pathToTexture, int wight, int height, float x, float y) {
		dinoTexture.loadFromFile(pathToTexture);  // Loading dino texture
		dinoSprite.setTexture(dinoTexture);       // Setting dino texture
		dinoSprite.setPosition(x, y);             // Setting dino position
		dinoWidht = wight;
		dinoHeight = height;
	}

	// Jump
	bool make_jump_flag = false;  // Flag make jump
	int jump_counter = 30;      // Jump counter
	void jump() {
		if (jump_counter >= -30) {
			dinoSprite.move(0, -(jump_counter / 3));
			jump_counter -= 1;
		} else {
			jump_counter = 30;
			make_jump_flag = false;
		}
	}

	void clear() {
		dinoSprite.setPosition(0, 0);             // Setting dino position
		dinoWidht = 0;
		dinoHeight = 0;
	}
};

// Background
class WindowBackground {
	public:
	sf::Texture backgroundTexture;  // Creating object texture
	sf::Sprite backgroundSprite;    // Creating background sprite explicit
	WindowBackground(const std::string &pathToTexture) {
		backgroundTexture.loadFromFile(pathToTexture);   // Loading object texture
		backgroundSprite.setTexture(backgroundTexture);  // Setting object texture
		backgroundSprite.setPosition(0, 0);              // Setting background position
	}
};

class Object {
	public:
	sf::Texture objectTexture;  // Creating object texture
	sf::Sprite objectSprite;    // Creating object sprite
	int objectWight, objectHeight;
	int objectMoveSpeed{};

	void setObject(const std::string &pathToTexture, int wight, int height, float x, float y, int moveSpeed) {
		objectTexture.loadFromFile(pathToTexture);  // Loading object texture
		objectSprite.setTexture(objectTexture);     // Setting object texture
		objectSprite.setPosition(x, y);             // Setting object position
		objectWight = wight;
		objectHeight = height;
		objectMoveSpeed = moveSpeed;
	}

	void move(float x, float y) {
		objectSprite.move(x, y);
	}
};

int randomCactusIndex(int numberOfOptions) {
	int result = rand() % 3;
	return result;
}

int randomDistanceBetweenObject(int minDistance, int maxDistance) {
	int difference = maxDistance - minDistance;
	int result = rand() % difference + minDistance;
	return result;
}

int randomDistanceBetweenCactus(std::vector<Object> cactuses, int i) {
	int counter = randomCactusIndex(7);
	if (counter == 0) {
		if (i > 1
			and cactuses[i - 1].objectSprite.getPosition().x - cactuses[i - 2].objectSprite.getPosition().x > 100) {
			return 50;
		} else {
			return randomDistanceBetweenObject(350, 700);
		}
	} else {
		return randomDistanceBetweenObject(350, 700);
	}
}

void creatingCactusArray(std::vector<Object> &array, int fromWhichIndex, int toWhatIndex) {
	for (int i = fromWhichIndex; i <= toWhatIndex; i++) {
		if (i == 0) {
			int randomCactus = randomCactusIndex(3);
			if (randomCactus == 0) {
				array[i].setObject("../Files/Img/Cactus_1.png", 40, 88, 1000, 420, 4);
			} else if (randomCactus == 1) {
				array[i].setObject("../Files/Img/Cactus_2.png", 49, 93, 1000, 415, 4);
			} else if (randomCactus == 2) {
				array[i].setObject("../Files/Img/Cactus_3.png", 44, 104, 1000, 405, 4);
			}
		} else {
			int randomCactus = randomCactusIndex(3);
			int newX = array[i - 1].objectSprite.getPosition().x + randomDistanceBetweenCactus(array, i);
			if (randomCactus == 0) {

				array[i].setObject("../Files/Img/Cactus_1.png", 40, 88, newX, 420, 4);
			} else if (randomCactus == 1) {
				array[i].setObject("../Files/Img/Cactus_2.png", 49, 93, newX, 415, 4);
			} else if (randomCactus == 2) {
				array[i].setObject("../Files/Img/Cactus_3.png", 44, 104, newX, 405, 4);
			}
		}
	}
}

// Moving and generating new catuses
void movingAndGeneratingNewCactuses(std::vector<Object> &cactuses) {
	for (int i = 0; i < cactuses.size(); i++) {
		cactuses[i].objectSprite.setPosition(cactuses[i].objectSprite.getPosition().x - cactuses[i].objectMoveSpeed,
		                                     cactuses[i].objectSprite.getPosition().y);
		if (cactuses[i].objectSprite.getPosition().x < 0 - cactuses[i].objectWight) {
			int cactusWithMaxX = 0;
			for (int i = 0; i < 10; i++) {
				if (cactuses[i].objectSprite.getPosition().x > cactuses[cactusWithMaxX].objectSprite.getPosition().x) {
					cactusWithMaxX = i;
				}
			}
			cactuses[i].objectSprite.setPosition(
				cactuses[cactusWithMaxX].objectSprite.getPosition().x + randomDistanceBetweenCactus(cactuses, i),
				cactuses[i].objectSprite.getPosition().y);
		}
	}
}

bool checkingCactusAndDinoCollision(std::vector<Object> &cactuses, Dino &dino) {
	for (int i = 0; i <= cactuses.size(); i++) {
		if (!dino.make_jump_flag) {
			if (cactuses[i].objectSprite.getPosition().x < dino.dinoSprite.getPosition().x + dino.dinoWidht - 10
				and dino.dinoSprite.getPosition().x + dino.dinoWidht - 10
					< cactuses[i].objectSprite.getPosition().x + cactuses[i].objectWight) {
				return true;
			}
		} else if (dino.make_jump_flag) {
			if (dino.jump_counter >= 0) {
				if (dino.dinoSprite.getPosition().y + dino.dinoHeight - 35
					>= cactuses[i].objectSprite.getPosition().y) {
					if (cactuses[i].objectSprite.getPosition().x
						<= dino.dinoSprite.getPosition().x + dino.dinoWidht - 40
						and dino.dinoSprite.getPosition().x + dino.dinoWidht - 40
							<= cactuses[i].objectSprite.getPosition().x + cactuses[i].objectWight) {
						return true;
					}
				}
			} else if (dino.jump_counter <= -1) {
				if (dino.dinoSprite.getPosition().y + dino.dinoHeight - 15
					>= cactuses[i].objectSprite.getPosition().y) {
					if (cactuses[i].objectSprite.getPosition().x
						<= dino.dinoSprite.getPosition().x + 10
						and dino.dinoSprite.getPosition().x + 10
							<= cactuses[i].objectSprite.getPosition().x + cactuses[i].objectWight) {
						return true;
					}
				}
				if (dino.dinoSprite.getPosition().y + dino.dinoHeight - 35
					>= cactuses[i].objectSprite.getPosition().y) {
					if (cactuses[i].objectSprite.getPosition().x
						<= dino.dinoSprite.getPosition().x + dino.dinoWidht - 40
						and dino.dinoSprite.getPosition().x + dino.dinoWidht - 40
							<= cactuses[i].objectSprite.getPosition().x + cactuses[i].objectWight) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

int randomNumber(int fromNumber, int toNumber) {
	int difference = toNumber - fromNumber;
	return rand() % difference + fromNumber;
}

//int gameOver(sf::RenderWindow &window) {
//	sf::Event event;
//	while (window.pollEvent(event)) {
//if (event.type == sf::Event::Closed) {
//window.close();
//return 0;
//}
//		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
//			return 1;
//		} else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)) {
//			return 0;
//		}
//	}
//}

int pause(sf::RenderWindow &window) {
	sf::Text pauseText("Pause, press ESC, for continue", retroFont, 50); // Creating pauses text
	pauseText.setPosition(295, 275); // Setting position of pauses text
	pauseText.setStyle(sf::Text::Regular); // Setting style of pauses text
	sf::Color black(0, 0, 0); // Creating black color
	pauseText.setColor(black); // Setting color of pauses text

	while (1) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
				return 0;
			}
		}
		window.draw(pauseText);
		window.display();
	}
}

int runGame(sf::RenderWindow &window) {
	// Creating dino
	Dino dino("../Files/Img/Dino_1.png", 80, 140, WINDOWWIGHT / 6, WINDOWHEIGHT - 140 - 100);

	// Creating background window
	WindowBackground WindowBackground("../Files/Img/BackGround.png");

	//Array with textures of cactuses
	int numberOfCactuses = randomNumber(10, 20);
	std::vector<Object> arrayWithCactuses(numberOfCactuses);
	creatingCactusArray(arrayWithCactuses, 0, 9);

	int varForFixBug = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
				pause(window);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
				dino.make_jump_flag = true;  // Jump
			}
		}

		// Jump
		if (dino.make_jump_flag) {
			dino.jump();
		}

		window.clear();                                  // Clearing window
		window.draw(WindowBackground.backgroundSprite);  // Drawing background
		window.draw(dino.dinoSprite);                    // Drawing dino

		movingAndGeneratingNewCactuses(arrayWithCactuses);  // Moving and generating new cactuses

		// Drawing cactuses
		for (int i = 0; i < numberOfCactuses; i++) {
			window.draw(arrayWithCactuses[i].objectSprite);
		}

		// Checking cactus and dino collision
		varForFixBug++;
		if (checkingCactusAndDinoCollision(arrayWithCactuses, dino)) {
			return 1;

//			else {
//				if (gameOver(window) == 0) {
//					return 1;
//				} else {
//					window.close();
//				}
//			}
		}
		window.display();
	}
}

int main() {
	// Creating window
	sf::RenderWindow window(
		sf::VideoMode(WINDOWWIGHT, WINDOWHEIGHT), "Dino",
		sf::Style::Close);  // Mode: video, window wight = 1000, window height =
	// 600, name = Dino, style = Close

	retroFont.loadFromFile("../Files/Other/8930.ttf"); // Load font

	// Setting FPS
	window.setFramerateLimit(FPS);

	srand(time(nullptr));

	while (window.isOpen()) {
		runGame(window);
	}

	return 0;
}
