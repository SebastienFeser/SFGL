/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2vector.h>
#include <cmath>

p2Vec2::p2Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

p2Vec2::p2Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

p2Vec2 p2Vec2::operator+(const p2Vec2& v) const
{
	return p2Vec2(x + v.x, y + v.y);
}

p2Vec2& p2Vec2::operator+=(const p2Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

p2Vec2 p2Vec2::operator-(const p2Vec2& v) const
{
	return p2Vec2(x-v.x, y-v.y);
}

p2Vec2& p2Vec2::operator-=(const p2Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

p2Vec2& p2Vec2::operator*=(float f)
{
	x *= f;
	y *= f;
	return (*this);
}

p2Vec2 p2Vec2::operator/(float f) const
{
	return p2Vec2(x/f, y/f);
}

p2Vec2 p2Vec2::operator*(float f) const
{
	return p2Vec2(x*f, y*f);
}

float p2Vec2::Dot(p2Vec2 v1, p2Vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}
float p2Vec2::Cross(p2Vec2 v1, p2Vec2 v2)
{
	return (v2.x*v1.y - v2.y*v1.x);
}
float p2Vec2::GetMagnitude() const
{
	return (sqrt(pow(this->x, 2.0f) + pow(this->y, 2.0f)));
}

p2Vec2 p2Vec2::Normalized()
{
	return p2Vec2(this->y, -(this->x));
}

void p2Vec2::NormalizeSelf()
{
	float x;
	float y;
	x = this->y;
	y = -this->x;
	this->x = x;
	this->y = y;
}

p2Vec2 p2Vec2::Rotate(float angle) const
{
	//TODO (Eventually)
	return p2Vec2();
}

p2Vec2 p2Vec2::Lerp(const p2Vec2& origin, const p2Vec2& target, float t)
{
	return p2Vec2(origin + target * t);
}

float p2Vec2::AngleBetween(const p2Vec2& v1, const p2Vec2& v2)
{
	//TODO (Eventually)
	return 0.0f;
}

p2Vec3 p2Vec2::to3()
{
	return p2Vec3(x, y, 0.0f);
}

p2Vec3::p2Vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

p2Vec3::p2Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

p2Vec3 p2Vec3::operator+(const p2Vec3& v)const
{
	return {x + v.x, y + v.y, z + v.z};
}

p2Vec3& p2Vec3::operator+=(const p2Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

p2Vec3 p2Vec3::operator-(const p2Vec3& v) const
{
	return {x - v.x, y - v.y, z- v.z};
}

p2Vec3& p2Vec3::operator-=(const p2Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

p2Vec3& p2Vec3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= z;
	return (*this);
}

p2Vec3 p2Vec3::operator/(float f) const
{
	return {x / f, y / f, z/f};
}

p2Vec3 p2Vec3::operator*(float f) const
{
	return {x*f, y*f, z*f};
}

float p2Vec3::Dot(p2Vec3 v1, p2Vec3 v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

p2Vec3 p2Vec3::Cross(p2Vec3 v1, p2Vec3 v2)
{
	return p2Vec3(v2.y*v1.z - v2.z*v1.y, v2.z*v1.x - v2.x*v1.z, v2.x*v1.y - v2.y*v1.x);
}

p2Vec3 p2Vec3::Rotate(float angle) const
{
	//TODO (Eventually)
	return p2Vec3();
}

p2Vec3 p2Vec3::Lerp(const p2Vec3& v1, const p2Vec3& v2, float t)
{
	//TODO (Eventually)
	return p2Vec3();
}

float p2Vec3::AngleBetween(const p2Vec3& v1, const p2Vec3& v2)
{
	//TODO (Eventually)
	return 0.0f;
}

float p2Vec3::GetMagnitude() const
{
	//TODO (Eventually)
	return 0.0f;
}

p2Vec3 p2Vec3::Normalized() const
{
	//TODO (Eventually)
	return p2Vec3();
}

void p2Vec3::NormalizeSelf()
{
	//TODO (Eventually)
}
