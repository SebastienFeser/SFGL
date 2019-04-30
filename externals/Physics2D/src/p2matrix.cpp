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

#include <p2matrix.h>

p2Mat22::p2Mat22()
{
}

p2Mat22::p2Mat22(p2Vec2 r1, p2Vec2 r2)
{
	//This is to instantiate a matrice, not really sure about that now
	this->rows[0] = r1;
	this->rows[1] = r2;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m1)
{
	return p2Mat22(p2Vec2(rows[0].x + m1.rows[0].x, rows[0].y + m1.rows[0].y), p2Vec2(rows[1].x + m1.rows[1].x, rows[1].y + m1.rows[1].y));
}

p2Mat22 p2Mat22::operator-(p2Mat22 m1)
{
	return p2Mat22(p2Vec2(rows[0].x - m1.rows[0].x, rows[0].y - m1.rows[0].y), p2Vec2(rows[1].x - m1.rows[1].x, rows[1].y - m1.rows[1].y));
}

p2Mat22 p2Mat22::operator*(p2Mat22 m1)
{
	return p2Mat22(p2Vec2(rows[0].x * m1.rows[0].x + rows[0].y * m1.rows[1].x, rows[0].x*m1.rows[0].y + rows[0].y*m1.rows[1].y), p2Vec2(rows[1].x * m1.rows[0].x + rows[1].y * m1.rows[1].x, rows[1].x*m1.rows[0].y + rows[1].y*m1.rows[1].y));
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	return p2Vec2(rows[0].x * v.x + rows[0].x * v.y, rows[1].x * v.x + rows[1].x * v.y);
}

p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22(p2Vec2(rows[0].x * f, rows[0].y * f), p2Vec2(rows[1].x * f, rows[1].y * f));
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22(p2Vec2 (rows[0].x / f, rows[0].y / f), p2Vec2(rows[1].x / f, rows[1].y * f));
}

p2Mat22 p2Mat22::Invert()
{
	//float multiplier(1 / (rows[0].x*rows[1].y - rows[0].y*rows[1].x));
	return p2Mat22(p2Vec2(rows[1].y * (1/GetDeterminant()),-rows[0].y * (1 / GetDeterminant())),p2Vec2(-rows[1].x * (1 / GetDeterminant()),rows[0].x * (1 / GetDeterminant())));
}

float p2Mat22::GetDeterminant()
{
	
	return rows[0].x*rows[1].y - rows[0].y*rows[1].x;
}

//Matrices 3x3

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3)
{
	//Not sure about this
	this->rows[0] = r1;
	this->rows[1] = r2;
	this->rows[3] = r3;
}

p2Mat33 p2Mat33::operator+(p2Mat33 m1)
{
	return p2Mat33(p2Vec3(rows[0].x + m1.rows[0].x, rows[0].y + m1.rows[0].y, rows[0].z + m1.rows[0].z), p2Vec3(rows[1].x + m1.rows[1].x, rows[1].y + m1.rows[1].y, rows[1].z + m1.rows[1].z), p2Vec3(rows[2].x + m1.rows[2].x, rows[2].y + m1.rows[2].y, rows[2].z + m1.rows[2].z));
}

p2Mat33 p2Mat33::operator-(p2Mat33 m1)
{
	return p2Mat33(p2Vec3(rows[0].x - m1.rows[0].x, rows[0].y - m1.rows[0].y, rows[0].z - m1.rows[0].z), p2Vec3(rows[1].x - m1.rows[1].x, rows[1].y - m1.rows[1].y, rows[1].z - m1.rows[1].z), p2Vec3(rows[2].x - m1.rows[2].x, rows[2].y - m1.rows[2].y, rows[2].z - m1.rows[2].z));
}

p2Mat33 p2Mat33::operator*(p2Mat33 m1)
{
	return p2Mat33(p2Vec3(rows[0].x*m1.rows[0].x + rows[0].y*m1.rows[1].x + rows[0].z*m1.rows[2].x, rows[0].y*m1.rows[0].y + rows[0].y*m1.rows[1].y + rows[0].z*m1.rows[2].z, rows[0].x*m1.rows[0].x + rows[0].y*m1.rows[1].z + rows[0].z*m1.rows[2].z), p2Vec3(rows[1].x*m1.rows[0].x + rows[1].y*m1.rows[1].x + rows[1].z*m1.rows[2].x, rows[1].y*m1.rows[0].y + rows[1].y*m1.rows[1].y + rows[1].z*m1.rows[2].z, rows[1].x*m1.rows[0].x + rows[1].y*m1.rows[1].z + rows[1].z*m1.rows[2].z), p2Vec3(rows[2].x*m1.rows[0].x + rows[2].y*m1.rows[1].x + rows[2].z*m1.rows[2].x, rows[2].y*m1.rows[0].y + rows[2].y*m1.rows[1].y + rows[2].z*m1.rows[2].z, rows[2].x*m1.rows[0].x + rows[2].y*m1.rows[1].z + rows[2].z*m1.rows[2].z));
}

p2Vec3 p2Mat33::operator*(p2Vec3 v)
{
	return p2Vec3(rows[0].x * v.x + rows[0].y * v.y + rows[0].z * v.z, rows[1].x * v.x + rows[1].y * v.y + rows[1].z * v.z, rows[2].x * v.x + rows[2].y * v.y + rows[2].z * v.z);
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33(p2Vec3(rows[0].x * f, rows[0].y * f, rows[0].z * f), p2Vec3(rows[1].x * f, rows[1].y * f, rows[1].z * f), p2Vec3(rows[2].x * f, rows[2].y * f, rows[2].z * f));
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33(p2Vec3(rows[0].x / f, rows[0].y / f, rows[0].z / f), p2Vec3(rows[1].x / f, rows[1].y / f, rows[1].z / f), p2Vec3(rows[2].x / f, rows[2].y / f, rows[2].z / f));
}

p2Mat33 p2Mat33::Invert()
{
	//TODO
	return p2Mat33(p2Vec3(), p2Vec3(), p2Vec3());
}

float p2Mat33::GetDeterminant()
{
	return rows[0].x*rows[1].y*rows[2].z + rows[0].y*rows[1].z*rows[2].x + rows[0].z*rows[1].x*rows[2].y - rows[0].z*rows[1].y*rows[2].x - rows[0].y*rows[1].x*rows[2].z - rows[0].z*rows[1].z*rows[2].y;
}
