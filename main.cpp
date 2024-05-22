#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <vector>

const int STARFIELD_SIZE = 100;
const float STAR_SIZE = 2.5f;
const int HEIGHT = 600;
const int WIDTH = 600;
const float SPEED = 0.2f;

// Random number generation
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis;
int rand_num(int start, int end) {
    // Update the distribution range
    dis.param(std::uniform_int_distribution<>::param_type(start, end));
    return dis(gen);
}

class Star {
public:
    float x, y;

    Star() : starshape(STAR_SIZE) {
        starshape.setPosition(x, y);
        starshape.setFillColor(sf::Color::White);
        starshape.setOrigin(WIDTH / 16.f, HEIGHT / 16.f);
        x = rand_num(0, WIDTH);
        y = rand_num(0, HEIGHT);
    }

    void moveAwayFromCenter(sf::Vector2f center) {
        sf::Vector2f direction = starshape.getPosition() - center;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
        starshape.move(direction * SPEED);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(starshape);
    }

    void resetPosition(sf::Vector2f border){
        sf::Vector2f position = starshape.getPosition();
        if (sqrt(position.x * position.x + position.y * position.y) > sqrt(border.x * border.x + border.y * border.y) - 100){
            starshape.setFillColor(sf::Color::Red);
        }
    }

private:
    sf::CircleShape starshape;    
};

//Array of Star()
//std::array<Star*, STARFIELD_SIZE> starfield;

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "Starfield");

    //Vector of Star()
    std::vector<Star> starfield;
    for (int i = 0; i < STARFIELD_SIZE; ++i) {
        // float x = rand_num(0, WIDTH);
        // float y = rand_num(0, HEIGHT);
        starfield.push_back(Star());
    }

    // for (int i = 0; i < STARFIELD_SIZE; i++){
    //     starfield[i] = new Star();
    // }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
            }
        } 
        //Center vector
        sf::Vector2f center(WIDTH / 2.f, HEIGHT / 2.f);

        sf::Vector2f border(600.f, 600.f);

        window.clear();

        //Center ball for test
        sf::CircleShape centerpoint(5);
        centerpoint.setFillColor(sf::Color::Red);
        centerpoint.setPosition(WIDTH/2.f, HEIGHT/2.f);
        window.draw(centerpoint);

        for (auto &star : starfield) {
            star.moveAwayFromCenter(center);
            star.resetPosition(border);
            star.draw(window);
        }
        window.display();
    }
    return 0;
}