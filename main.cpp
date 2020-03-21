#include "SFML/Graphics.hpp"

#include <exception>
#include <iostream>
#include <string>

#include "Settings.hpp"
#include "World.hpp"

int main()
{
    Settings settings;
    settings.windowWidth = 800;
    settings.windowHeight = 800;
    settings.fullScreenOn = false;
    settings.cellSize = 10;

    if (settings.windowWidth % settings.cellSize != 0)
    {
        throw std::runtime_error("Window width is not divisible by cell size");
    }

    if (settings.windowHeight % settings.cellSize != 0)
    {
        throw std::runtime_error("Window height is not divisible by cell size");
    }

    const int NumberOfCellsInRow    = settings.windowWidth  / settings.cellSize;
    const int NumberOfCellsInColumn = settings.windowHeight / settings.cellSize;

    World world(NumberOfCellsInRow, NumberOfCellsInColumn);

    // Blinker
    world.getCell(2, 11) = World::LiveCell;
    world.getCell(3, 11) = World::LiveCell;
    world.getCell(4, 11) = World::LiveCell;

    // Block
    world.getCell(10, 11) = World::LiveCell;
    world.getCell(10, 12) = World::LiveCell;
    world.getCell(11, 11) = World::LiveCell;
    world.getCell(11, 12) = World::LiveCell;

    // Glider
    world.getCell(15, 5) = World::LiveCell;
    world.getCell(16, 6) = World::LiveCell;
    world.getCell(17, 4) = World::LiveCell;
    world.getCell(17, 5) = World::LiveCell;
    world.getCell(17, 6) = World::LiveCell;

    // Tub
    world.getCell(10, 30) = World::LiveCell;
    world.getCell( 9, 31) = World::LiveCell;
    world.getCell(11, 31) = World::LiveCell;
    world.getCell(10, 32) = World::LiveCell;

    sf::RenderWindow window(
        sf::VideoMode(settings.windowWidth, settings.windowHeight),
        "Game of life",
        settings.fullScreenOn ? sf::Style::Fullscreen : sf::Style::Default
    );

    sf::RectangleShape cellView(sf::Vector2f(settings.cellSize, settings.cellSize));
    cellView.setOutlineColor(sf::Color(32, 32, 32));
    cellView.setOutlineThickness(-0.5f);

    sf::RenderTexture cellTextures;
    cellTextures.create(2 * settings.cellSize, settings.cellSize);

    // Live cell
    cellView.setPosition(0, 0);
    cellView.setFillColor(sf::Color(255, 192, 0));
    cellTextures.draw(cellView);

    // Dead cell
    cellView.setPosition(settings.cellSize, 0);
    cellView.setFillColor(sf::Color(64, 64, 64));
    cellTextures.draw(cellView);

    sf::Sprite CellLiveView(
        cellTextures.getTexture(),
        sf::IntRect(
            0,
            0,
            settings.cellSize,
            settings.cellSize
        )
    );

    sf::Sprite CellDeadView(
        cellTextures.getTexture(),
        sf::IntRect(
            settings.cellSize,
            0,
            settings.cellSize,
            settings.cellSize
        )
    );

    sf::Font font;
    font.loadFromFile("Resources/Lato-Regular.ttf");

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(32);
    fpsText.setFillColor(sf::Color(255, 255, 255));
    fpsText.setString("FPS:");
    fpsText.setPosition(
        settings.windowWidth - fpsText.getLocalBounds().width - 100,
        20
    );

    int fpsCounter = 0;
    sf::Clock fpsClock;

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

        for (int y = 0; y < world.getHeight(); ++y)
        {
            for (int x = 0; x < world.getWidth(); ++x)
            {
                sf::Vector2f position{
                    static_cast<float>(x * settings.cellSize),
                    static_cast<float>(y * settings.cellSize)
                };

                if (world.getCell(x, y) == World::LiveCell)
                {
                    CellLiveView.setPosition(position);
                    window.draw(CellLiveView);
                }
                else
                {
                    CellDeadView.setPosition(position);
                    window.draw(CellDeadView);
                }
            }
        }

        ++fpsCounter;

        if (fpsClock.getElapsedTime() >= sf::seconds(1))
        {
            fpsText.setString("FPS: " + std::to_string(fpsCounter));

            fpsClock.restart();
            fpsCounter = 0;
        }

        window.draw(fpsText);

        window.display();

    }

    return 0;
}
