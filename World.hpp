#ifndef WORLD_HPP_
#define WORLD_HPP_

class World
{
public:

	static constexpr int Width = 192;
	static constexpr int Height = 108;

	bool & getCell(int x, int y);

	void performTimeStep();
	void setRandomState();

private:

	using Cells = bool[Height + 2][Width + 2];
	Cells cells = {};
};

#endif /* WORLD_HPP_ */
