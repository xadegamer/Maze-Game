#include <cmath>
#include "cVector2.h"


// internal only
//-----------------------------------------------------------------------------
cVector2::cVector2()
    : x(0), y(0)
{
}


//-----------------------------------------------------------------------------
cVector2::cVector2(int x, int y)
    : x(x), y(y)
{
}

//-----------------------------------------------------------------------------
cVector2::cVector2(const cVector2 & v)
    : x(v.x), y(v.y)
{
}

//-----------------------------------------------------------------------------
cVector2&   cVector2::operator=(const cVector2 & v)
{
    x = v.x;
    y = v.y;
    return *this;
}

//-----------------------------------------------------------------------------
cVector2 cVector2::operator+(const cVector2& v)
{
	return cVector2(x + v.x, y + v.y);
}

//-----------------------------------------------------------------------------
cVector2 cVector2::operator-(const cVector2& v)
{
	return cVector2(x - v.x, y - v.y);
}

//-----------------------------------------------------------------------------
cVector2 cVector2::operator-()
{
	return cVector2{ -x, -y };
}

//-----------------------------------------------------------------------------

cVector2& cVector2::operator+=(const cVector2& v) 
{
	x += v.x;
	y += v.y;
	return *this;
}

//-----------------------------------------------------------------------------
cVector2& cVector2::operator-=(const cVector2& v) 
{
	x -= v.x;
	y -= v.y;
	return *this;
}

//-----------------------------------------------------------------------------
bool   cVector2::operator==(const cVector2 & v) const
{
    if (this->x == v.x && this->y == v.y)
        return true;
    return false;
}

//-----------------------------------------------------------------------------
float cVector2::dist(const cVector2& v) const
{
	return static_cast<float>(std::sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y)));
}

//-----------------------------------------------------------------------------
cVector2 operator+(const cVector2& lv, const cVector2& rv)
{
	cVector2 v(lv);
	v += rv;
	return v;
}

//-----------------------------------------------------------------------------
cVector2 operator-(const cVector2& lv, const cVector2& rv)
{
	cVector2 v(lv);
	v -= rv;
	return v;
}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const cVector2& v)
{
	out << "(" << v.x << ", " << v.y << ")";
	return out;
}
