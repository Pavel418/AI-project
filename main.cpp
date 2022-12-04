#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Car
{
private:
    const float _car_height = 20.f;
    const float _car_width = 40.f;
public:
    int velocity;
    float angle;
    float angular_velocity;
    sf::Vector2f car_position;
    sf::RectangleShape shape;

    Car(sf::Vector2f initialPosition, float initialAngle = 0.f, float angularVelocity = 75.f, int carVelocity = 200);
    ~Car();
    void Update(sf::Time time);
    void Update(sf::Time time, bool input[]);
};

Car::Car(sf::Vector2f initialPosition, float initialAngle, float angularVelocity, int carVelocity)
{
    angle = initialAngle;
    velocity = carVelocity;
    angular_velocity = angularVelocity;
    car_position = initialPosition;
    sf::RectangleShape sh(sf::Vector2f(_car_width, _car_height));
    sh.setFillColor(sf::Color::Red);
    sh.setOrigin(_car_width / 2, _car_height / 2);
    sh.setPosition(car_position);

    shape = sh;
}

Car::~Car()
{
}

void Car::Update(sf::Time time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        car_position.x -= velocity * time.asSeconds() * cosf(angle * M_PI / 180.f);
        car_position.y -= velocity * time.asSeconds() * sinf(angle * M_PI / 180.f);
        shape.setPosition(car_position);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        car_position.x += velocity * time.asSeconds() * cosf(angle * M_PI / 180.f);
        car_position.y += velocity * time.asSeconds() * sinf(angle * M_PI / 180.f);
        shape.setPosition(car_position);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        float rotation = -angular_velocity * time.asSeconds();
        angle += rotation;
        shape.rotate(rotation);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        float rotation = angular_velocity * time.asSeconds();
        angle += rotation;
        shape.rotate(rotation);
    }
}

void Car::Update(sf::Time time, bool input[])
{
    if (input[0])
    {
        car_position.x -= velocity * time.asSeconds() * cosf(angle * M_PI / 180.f);
        car_position.y -= velocity * time.asSeconds() * sinf(angle * M_PI / 180.f);
        shape.setPosition(car_position);
    }

    if (input[1])
    {
        car_position.x += velocity * time.asSeconds() * cosf(angle * M_PI / 180.f);
        car_position.y += velocity * time.asSeconds() * sinf(angle * M_PI / 180.f);
        shape.setPosition(car_position);
    }

    if (input[2])
    {
        float rotation = -angular_velocity * time.asSeconds();
        angle += rotation;
        shape.rotate(rotation);
    }

    if (input[3])
    {
        float rotation = angular_velocity * time.asSeconds();
        angle += rotation;
        shape.rotate(rotation);
    }
}

int main()
{
    const int height = 1000;
    const int width = 1000;
    srand(50);
    sf::RenderWindow window(sf::VideoMode(height, width), "AI project");
    std::vector<Car> cars;
    for (size_t i = 0; i < 5; i++)
    {
        float x = static_cast<float>(rand() % 1000 + 1);
        float y = static_cast<float>(rand() % 1000 + 1);
        cars.push_back(Car(sf::Vector2f(x, y)));
    }
    

    bool values[5][4];
    sf::Clock gameClock, cycle;
    while (window.isOpen())
    {
        sf::Time time = gameClock.restart();
        if (cycle.getElapsedTime().asSeconds() > 1.f)
        {
            for (int k = 0; k < 5; k++)
            {
                values[k][0] = rand() % 10 < 5;
                values[k][1] = !values[0];
                values[k][2] = rand() % 10 < 5;
                values[k][3] = !values[2];
            }
            cycle.restart();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int k = 0; k < 5; k++)
        {
            cars[k].Update(time, values[k]);
            window.draw(cars[k].shape);
        }
        window.display();
    }

    return 0;
}