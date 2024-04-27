#include <SFML/Graphics.hpp>
#include <array>
#include <random>

const int STARFIELD_SIZE = 50;
const int STAR_SIZE = 3;
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
        this->x = rand_num(-WIDTH/2,WIDTH/2);
        this->y = rand_num(-HEIGHT/2, HEIGHT/2);
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

        for (int i = 0; i < STARFIELD_SIZE; i++){
            if ((starfield[i]->x > 0) && (starfield[i]->y > 0)){
                starfield[i]->x+=0.002f;
                starfield[i]->y+=0.002f;
            }
            else if ((starfield[i]->x < 0) && (starfield[i]->y > 0)){
                starfield[i]->x-=0.002f;
                starfield[i]->y+=0.002f; 
            }
            else if ((starfield[i]->x > 0) && (starfield[i]->y < 0)){
                starfield[i]->x+=0.002f;
                starfield[i]->y-=0.002f; 
            }
            else if ((starfield[i]->x < 0) && (starfield[i]->y < 0)){
                starfield[i]->x-=0.002f;
                starfield[i]->y-=0.002f; 
            }
        }

        window.clear();
        for (int i = 0; i < STARFIELD_SIZE; i++){
            sf::CircleShape starshape(STAR_SIZE);
            starshape.setFillColor(sf::Color::White);
            starshape.setOrigin(-WIDTH/2, -HEIGHT/2);
            starshape.setPosition((starfield[i]->x), (starfield[i]->y));
            window.draw(starshape);
        }
        window.display();
    }
    return 0;
}