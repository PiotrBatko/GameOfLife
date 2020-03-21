#include "World.hpp"

#include <cstring>
#include <functional>
#include <iostream>
#include <random>

World::World(int width, int height) :
    Width(width),
    Height(height),
    BufferWidth(Width + 2),
    BufferHeight(Height + 2),
    cells(BufferWidth * BufferHeight)
{

}

int World::getWidth() const
{
    return Width;
}

int World::getHeight() const
{
    return Height;
}

char& World::getCell(int x, int y)
{
    return cells[(y + 1) * BufferWidth + (x + 1)];
}

void World::performTimeStep()
{
    Cells buffer(BufferWidth * BufferHeight);

    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            const int NumberOfNeightbours = getCell(x - 1, y + 1) + getCell(x + 0, y + 1) + getCell(x + 1, y + 1)
                                          + getCell(x - 1, y + 0) +           0           + getCell(x + 1, y + 0)
                                          + getCell(x - 1, y - 1) + getCell(x + 0, y - 1) + getCell(x + 1, y - 1);

            if (getCell(x, y) == World::LiveCell)
            {
                if (NumberOfNeightbours < 2 || NumberOfNeightbours > 3)
                {
                    buffer[(y + 1) * BufferWidth + (x + 1)] = World::DeadCell;
                }
                else
                {
                    buffer[(y + 1) * BufferWidth + (x + 1)] = World::LiveCell;
                }
            }
            else
            {
                if (NumberOfNeightbours == 3)
                {
                    buffer[(y + 1) * BufferWidth + (x + 1)] = World::LiveCell;
                }
            }
        }
    }

    cells = std::move(buffer);
}

void World::setRandomState()
{
    static auto generateRandomState = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());

    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            if (y > 40 && y < 60 && x > 90 && x < 110)
            {
                getCell(x, y) = generateRandomState();
            }
            else
            {
                getCell(x, y) = false;
            }
        }
    }
}
