#include <SFML/Graphics.hpp>
#include <ctime>
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
    float jump_counter = 30;  // Jump counter

   public:
    Dino(const std::string &pathToTexture, int wight, int height, float x,
         float y) {
        dinoTexture.loadFromFile(pathToTexture);  // Loading dino texture
        dinoSprite.setTexture(dinoTexture);       // Setting dino texture
        dinoSprite.setPosition(x, y);             // Setting dino position
        dinoWight = wight;
        dinoHeight = height;
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
    int moveSpeed{};
    int distanceToNextCactus;

    void setObject(const std::string &pathToTexture, int wight, int height,
                   float x, float y, int moveSpeed, int distanceToNextCactus) {
        objectTexture.loadFromFile(pathToTexture);  // Loading object texture
        objectSprite.setTexture(objectTexture);     // Setting object texture
        objectSprite.setPosition(x, y);             // Setting object position
        objectWight = wight;
        objectHeight = height;
        this->moveSpeed = moveSpeed;
        this->distanceToNextCactus = distanceToNextCactus;
    }

    void move(float x, float y) { objectSprite.move(x, y); }
};

int randomCactusIndex(int numberOfOptions) {
    srand(time(NULL));
    int result = rand() % 3;
    return result;
}

int randomDistanceBetweenObject(int minDistance, int maxDistance) {
    int difference = maxDistance - minDistance;
    int result = rand() % difference + minDistance;
    return result;
}

void creatingCactusArray(Object array[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        int randomCactus = randomCactusIndex(3);
        if (randomCactus == 0) {
            array[i].setObject("../Files/Img/Cactus_1.png", 40, 88, 1000, 420, 3,
                               randomDistanceBetweenObject(350, 700));
        } else if (randomCactus == 1) {
            array[i].setObject("../Files/Img/Cactus_2.png", 49, 93, 1000, 415, 3,
                               randomDistanceBetweenObject(350, 700));
        } else if (randomCactus == 2) {
            array[i].setObject("../Files/Img/Cactus_3.png", 44, 104, 1000, 405, 3,
                               randomDistanceBetweenObject(350, 700));
        }
    }
}

int main() {
    // Creating window
    sf::RenderWindow window(
        sf::VideoMode(WINDOWWIGHT, WINDOWHEIGHT), "Dino",
        sf::Style::Close);  // Mode: video, window wight = 1000, window height =
    // 600, name = Dino, style = Close

    // Creating dino
    Dino dino("../Files/Img/Dino_1.png", 80, 140, WINDOWWIGHT / 6,
              WINDOWHEIGHT - 140 - 100);

    // Creating background window
    WindowBackground WindowBackground("../Files/Img/BackGround.png");

    // Setting FPS
    window.setFramerateLimit(FPS);

    // Creating cactus
    int quantityOfCacti = 10;
    Object cactus[quantityOfCacti];
    creatingCactusArray(cactus, quantityOfCacti);

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

        for (int i = 0; i < quantityOfCacti - 1; i++) {
            if (i == 0) {
                cactus[i].objectSprite.setPosition(cactus[i].objectSprite.getPosition().x - cactus[i].moveSpeed,
                                                   cactus[i].objectSprite.getPosition().y);
            }
            if (cactus[i + 1].objectSprite.getPosition().x - cactus[i].objectSprite.getPosition().x >= cactus[i].distanceToNextCactus) {
                cactus[i + 1].objectSprite.setPosition(cactus[i + 1].objectSprite.getPosition().x - cactus[i + 1].moveSpeed,
                                                       cactus[i + 1].objectSprite.getPosition().y);
            }
        }

        for (int i = 0; i < quantityOfCacti; i++) {
            if (0 - cactus[i].objectWight < cactus[i].objectSprite.getPosition().x < 1000) {
                window.draw(cactus[i].objectSprite);
            }
        }

        // if (cactus[quantityOfCacti - 1].objectSprite.getPosition().x < 1000 - cactus[quantityOfCacti - 1].distanceToNextCactus) {
        //     creatingCactusArray(cactus, quantityOfCacti);
        // }

        window.display();
    }
    return 0;
}