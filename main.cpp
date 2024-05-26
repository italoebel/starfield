#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <vector>

const int STARFIELD_SIZE = 160;
const float STAR_SIZE = 4.f;
const int HEIGHT = 800;
const int WIDTH = 800;
const float SPEED = 8.f;

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
    float x, y, px, py;

    Star() : starshape(0.f) {
        starshape.setPosition(x, y);
        starshape.setFillColor(sf::Color::White);
        //starshape.setOrigin(WIDTH / 2.f, HEIGHT / 2.f);
        x = rand_num(0, WIDTH);
        y = rand_num(0, HEIGHT);
        px, py = x, y;
    }

    void moveAwayFromCenter(sf::Vector2f center) {
        // Vector Center to Object (Object - Center)
        sf::Vector2f direction = starshape.getPosition() - center;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalized vector
        direction /= length;

        // Speed factor
        float distanceToCenter = length;
        float maxDistance = sqrt(center.x * center.x + center.y * center.y);
        float speedFactor = distanceToCenter / maxDistance;
        float speed = SPEED * speedFactor;

        // Size factor
        float sizeFactor = distanceToCenter / STAR_SIZE;
        starshape.setRadius(STAR_SIZE * sizeFactor / 100);

        // Star trail

        // SFML move function
        starshape.move(direction * speed);
    }

    void resetPosition() {
        sf::Vector2f position = starshape.getPosition();
        if (position.x < -10 || position.x > WIDTH || position.y < -10 || position.y > HEIGHT) {
            x = rand_num(0, WIDTH);
            y = rand_num(0, HEIGHT);
            starshape.setPosition(x, y);
            starshape.setRadius(0.f);
            //starshape.setFillColor(sf::Color::Red);
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(starshape);
    }

private:
    sf::CircleShape starshape;    
};

// Array of Star()
//std::array<Star*, STARFIELD_SIZE> starfield;

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "Starfield");

    // Vector of Star()
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
         
        // Center vector
        sf::Vector2f center(WIDTH / 2.f, HEIGHT / 2.f);

        //sf::Vector2f border(WIDTH, HEIGHT);

        window.clear();

        // // Center ball for test
        // sf::CircleShape centerpoint(5);
        // centerpoint.setFillColor(sf::Color::Red);
        // centerpoint.setPosition(WIDTH/2.f - 5, HEIGHT/2.f - 5);
        // window.draw(centerpoint);

        for (Star& star : starfield) {
            star.moveAwayFromCenter(center);
            star.resetPosition();
            star.draw(window);
        }
        window.display();
    }
    return 0;
}