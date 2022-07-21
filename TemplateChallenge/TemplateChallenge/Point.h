#pragma once
template <typename Type>
class Point
{
public:
	Type x;
	Type y;

	Point(Type x = 0, Type y = 0)
		: x(x)
		, y(y)
	{

	}

	Type GetLargerCoordinate()
	{
		if (x > y)
			return x;
		return y;
	}

	Type GetSmallerCoordinate()
	{
		if (x < y)
			return x;
		return y;
	}
};

