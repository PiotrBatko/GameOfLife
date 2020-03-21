#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>

class World
{
public:

    static constexpr char DeadCell = '\0';
    static constexpr char LiveCell = DeadCell + 1;

    World(int width, int height);

    int getWidth() const;
    int getHeight() const;
    char & getCell(int x, int y);

    void performTimeStep();
    void setRandomState();

private:

    const int Width;
    const int Height;

    const int BufferWidth;
    const int BufferHeight;

    using Cells = std::vector<char>;
    Cells cells = {};
};

#endif /* WORLD_HPP_ */
