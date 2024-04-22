#include <SFML/Graphics.hpp>
#include <array>
#include <random>

const int STARFIELD_SIZE = 10;
const int STAR_SIZE = 5;
const int HEIGHT = 600;
const int WIDTH = 600;
const int SPEED = 10;

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
    float x, y, z;

    Star() {
        this->x = rand_num(0,WIDTH);
        this->y = rand_num(0,HEIGHT);
    }
};

//Array of Star()
std::array<Star*, STARFIELD_SIZE> starfield;

int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "Window!");

    for (int i = 0; i < STARFIELD_SIZE; i++){
        starfield[i] = new Star();
    }

    

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
        
        
        starfield[0]->x+=0.01f;

        window.clear();
        for (int i = 0; i < STARFIELD_SIZE; i++){
            sf::CircleShape starshape(STAR_SIZE);
            starshape.setFillColor(sf::Color::White);
            starshape.setPosition((starfield[i]->x), (starfield[i]->y));
            window.draw(starshape);
        }
        window.display();
    }
    return 0;
}