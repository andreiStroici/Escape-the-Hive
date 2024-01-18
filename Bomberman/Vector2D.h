#pragma once
#include <iostream>

class Vector2D
{
private:

public:

	float x;
	float y;

	Vector2D(void);
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& vec);
	//substract
	Vector2D& sub(const Vector2D& vec);
	//multiply
	Vector2D& mul(const Vector2D& vec);
	//divide
	Vector2D& div(const Vector2D& vec);
	
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	//I use this to timesing our vector scale number
	Vector2D& operator*(const int& i);
	Vector2D& zero(void);


	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};