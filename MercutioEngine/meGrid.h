#pragma once
#include <vector>
struct Grid
{
private:
	std::vector<int> data;
	int width = 0;
	int height = 0;
public:
	Grid() {}
	Grid(int width, int height)
	{
		SetSize(width, height);
	}

	void SetSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		data.clear();
		data = std::vector<int>(width*height, 0);
	}

	int GetElement(int id)
	{
		return data[id];
	}

	int GetElement(int x, int y)
	{
		int id = width * y + x;
		return GetElement(id);
	}

	void SetElement(int id, int value)
	{
		data[id] = value;
	}

	void SetElement(int x, int y, int value)
	{
		int id = width * y + x;
		SetElement(id, value);
	}

	bool OnGrid(int x, int y)
	{
		return x>-1 && x<width && y>-1 && y<height;
	}
};