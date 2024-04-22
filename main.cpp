#include <SFML/Graphics.hpp>
#include <array>
#include <random>

const int STARFIELD_SIZE = 10;

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

    Star() {
        this->x = rand_num(0,500);
        this->y = rand_num(0,500);
    }
};

std::array<Star*, STARFIELD_SIZE> starfield;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Window!");

    for (int i = 0; i < STARFIELD_SIZE; i++){
        starfield[i] = new Star();
    }

    window.clear();
    for (int i = 0; i < STARFIELD_SIZE; i++){
        sf::CircleShape starshape(5.f);
        starshape.setFillColor(sf::Color::White);
        starshape.setPosition((starfield[i]->x), (starfield[i]->y));
        window.draw(starshape);
    }
    window.display();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}