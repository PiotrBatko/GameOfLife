#include "SFML/Graphics.hpp"

#include <iostream>

#include "Settings.hpp"
#include "World.hpp"

static constexpr float CellWidth = 10.0f;
static constexpr float CellHeight = CellWidth;

int main()
{
    Settings settings;
    settings.windowWidth = 800;
    settings.windowHeight = 800;
    settings.cellSize = 4;
    settings.stepsPerSecondLimit = 10;

    World world;

    // Blinker
    world.getCell(2, 11) = true;
    world.getCell(3, 11) = true;
    world.getCell(4, 11) = true;

    // Block
    world.getCell(10, 11) = true;
    world.getCell(10, 12) = true;
    world.getCell(11, 11) = true;
    world.getCell(11, 12) = true;

    // Glider
    world.getCell(15, 5) = true;
    world.getCell(16, 6) = true;
    world.getCell(17, 4) = true;
    world.getCell(17, 5) = true;
    world.getCell(17, 6) = true;

    // Tub
    world.getCell(10, 30) = true;
    world.getCell(9, 31) = true;
    world.getCell(11, 31) = true;
    world.getCell(10, 32) = true;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game of life", sf::Style::Fullscreen);

    sf::RectangleShape cellView(sf::Vector2f(CellWidth, CellHeight));
    cellView.setOutlineColor(sf::Color(32, 32, 32));
    cellView.setOutlineThickness(-0.5f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            world.setRandomState();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            world.performTimeStep();
        }

        window.clear();

        for (int y = 0; y < World::Height; ++y)
        {
            for (int x = 0; x < World::Width; ++x)
            {
                sf::Vector2f position
                {x * CellWidth, y * CellHeight};
                cellView.setPosition(position);

                if (world.getCell(x, y) == true)
                {
                    cellView.setFillColor(sf::Color(255, 192, 0));

                }
                else
                {
                    cellView.setFillColor(sf::Color(64, 64, 64));
                }

                window.draw(cellView);
            }
        }
        window.display();

        //sf::sleep(sf::milliseconds(20));
    }

    return 0;
}
