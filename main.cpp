#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const int WINDOWWIGHT = 1000;  // Window wight
const int WINDOWHEIGHT = 600;  // Window height
const int FPS = 60;            // FPS

class Dino {
   public:
    sf::Texture dinoTexture;    // Creating dino texture
    sf::Sprite dinoSprite;      // Creating dino sprite
    int dinoWight, dinoHeight;  // Dino wight and height

    // Jump
    bool make_jump_flag = false;  // Flag make jump
   private:
    int jump_counter = 30;  // Jump counter

   public:
    Dino(std::string pathToTexture, int wight, int height, int x, int y) {
        dinoTexture.loadFromFile(pathToTexture);  // Loading dino texture
        dinoSprite.setTexture(dinoTexture);       // Seting dino texture
        dinoSprite.setPosition(x, y);             // Seting dino position
    }

   public:
    // Jump
    void jump() {
        if (jump_counter >= -30) {
            dinoSprite.move(0, -(jump_counter / 3));
            jump_counter -= 1;
        } else {
            jump_counter = 30;
            make_jump_flag = false;
        }
    }
};

// Background
class WindowBackground {
   public:
    sf::Texture backgoundTexture;  // Creating object texture
    sf::Sprite backgroundSprite;   // Creating background sprite

    WindowBackground(std::string pathToTexture) {
        backgoundTexture.loadFromFile(pathToTexture);   // Loading object texture
        backgroundSprite.setTexture(backgoundTexture);  // Seting object texture
        backgroundSprite.setPosition(0, 0);             // Setting background position
    }
};

class Object {
   public:
    sf::Texture objectTexture;  // Creating object texture
    sf::Sprite objectSprite;    // Creating object sprite

    Object(std::string pathToTexture, int wight, int height, int x, int y) {
        objectTexture.loadFromFile(pathToTexture);  // Loading object texture
        objectSprite.setTexture(objectTexture);     // Seting object texture
        objectSprite.setPosition(x, y);             // Setting object position
    }
};

int main() {
    // Creating window
    sf::RenderWindow window(sf::VideoMode(WINDOWWIGHT, WINDOWHEIGHT), "Dino", sf::Style::Close);  // Mode: video, window wight = 1000, window height = 600, name = Dino, style = Close

    // Creating dino
    Dino dino("Files/Img/Dino_1.png", 80, 140, WINDOWWIGHT / 6, WINDOWHEIGHT - 140 - 100);

    // Creating background window
    WindowBackground WindowBackground("Files/Img/BackGround.png");

    // Ceating cactus
    Object cactus_1("Files/Img/Cactus_1.png", 40, 88, 40, 420);
    Object cactus_2("Files/Img/Cactus_2.png", 49, 93, 50, 415);
    Object cactus_3("Files/Img/Cactus_3.png", 44, 104, 45, 405);

    // Setting FPS
    window.setFramerateLimit(FPS);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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
        window.draw(cactus_1.objectSprite);
        window.draw(cactus_2.objectSprite);
        window.draw(cactus_3.objectSprite);
        window.display();
    }

    return 0;
}