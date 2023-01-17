#pragma once

// Internal Vector2 class is used to manage position/coordinates. Always keeping the 
//  row and col values together just makes life easier and shows a utility class
//  in action. The basics of the class are very simple, but there are more sophisticated elements too.

#include <ostream>

class cVector2
{
public:
    cVector2();
    cVector2(int x, int y);
    cVector2(const cVector2& v);
    virtual ~cVector2() {}

	// basic functions
	float	dist(const cVector2& v) const;
	bool	empty() { return (x == 0 && y == 0) ? true : false; }

	// operators
    cVector2& operator=(const cVector2& v);
	cVector2 operator+(const cVector2& v);
	cVector2 operator-(const cVector2& v);
	cVector2 operator-();
	cVector2& operator+=(const cVector2& v);
	cVector2& operator-=(const cVector2& v);
	bool operator==(const cVector2& v) const;

	// data - public
	int     x{ 0 }, y{ 0 };
};

// additional operators for arithmetic and stream operations
cVector2 operator+(const cVector2& lv, const cVector2& rv);
cVector2 operator-(const cVector2& lv, const cVector2& rv);
std::ostream& operator<<(std::ostream& out, const cVector2& v);