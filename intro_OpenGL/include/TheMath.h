
#pragma once
#ifndef _THE_MATH_H_
#define _THE_MATH_H_

#include <math.h>
#include <ostream>

#define PI 3.14159

/*
Designates the list of data to extract from the grid i.e. horizontal or vertical.
*/
enum MATRIX_MAJOR
{
	ROW,
	COL
};

/*
Designates axis on Cartesion plane
*/
enum AXIS
{
	X,
	Y,
	Z
};

class JMath
{
public:
	/*
	returns the given angle in degrees converted to radians
	*/
	static float DegreeToRadians(float angleInDegrees)
	{
		return angleInDegrees * (PI / 180);
	}

	/*
	returns given angle in radians converted to degrees
	*/
	static float RadiansToDegrees(float angleInRadians)
	{
		return angleInRadians * (180 / PI);
	}

	/*
	returns true if given result is within delta of expected result using
	formula: (fabs(result - expected) < delta)
	*/
	static bool FloatEquals(const float& result, const float& expected, const float delta)
	{
		return (fabs(result - expected) < delta);
	}

	/*
	return float representing linear interpolation of given percentage between 2 given scalar values.
	NOTE: expect given percent to be value between 0 and 1;
	*/
	static float LERP(float begin, float end, float percent)
	{
		return (begin + (end - begin) * percent);
	}

	/*
	return true if given unsigned integer is a power of two else returns false
	*/
	static bool IsPowerOfTwo(const unsigned int num)
	{
		unsigned int n = num;
		//shift bits to right (divide by two) until get a set bit that is most significant or not
		while (((n & 1) == 0) && n > 1) //while num is even and greater than 1;
		{
			n >>= 1; //shift bits to the right one space
		}
		//if found a bit set to 1 and it's not most significant (i.e. n > 1) then return false
		//else return true;
		return (n == 1);
	}

	/*
	Return the next highest power of 2 of the given 32-bit value if the value is not a power of 2.  Otherwise, will return the value.
	*/
	static unsigned int GetNextPowerOfTwo(const unsigned int value)
	{
		unsigned int v = value;
		//check edge case of 0
		if (value == 0)
			return 0;
		/*copy the most significant bit to all lower bits, then add 1 which results in carry that
		sets all lower bits to 0 and one bit beyond to 1.  If the original number was a power of 2
		then the decrement will reduce it by one less, so then round up to original value.
		*/
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;

		return v;
	}
};

class Vector2
{
public:
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& other);

	~Vector2();

	float x, y;

	//operator overloads
	Vector2& operator=(const Vector2& rhs);

	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	Vector2 operator-();

	/*
	returns true if Vector not zero (Vector2 (0,0)) else returns false;
	*/
	bool operator!();

	Vector2 operator*(const float scalar);
	void operator*=(const float scalar);

	/*
	returns true if given other Vector2 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector2& other);

	friend bool operator==(const Vector2& lhs, const Vector2& rhs);

	/*
	returns false if given other Vector2 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector2& other);

	friend bool operator!=(const Vector2& lhs, const Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Vector2& v);

	//vector math functions
	/*
	returns magnitude of this vector
	*/
	float Magnitude();

	/*
	normalize this Vector2
	*/
	void Normalize();

	/*
	return normalized Vector2 from values of this one. This vector is not changed.
	*/
	Vector2 GetNormal();

	/*
	return dot product of this vector and given other vector
	*/
	float DotProduct(const Vector2& other);

	//return Vector2 perpendicular to this one
	Vector2 GetPerp();

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	Vector2 GetLERP(const Vector2& end, float const percent);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	static Vector2 LERP(const Vector2& start, const Vector2& end, float percent);

};



//need to declare because of GetVector3() static function's use of Matrix3
class Matrix3;

class Vector3
{
public:
	Vector3();
	Vector3(float a_x, float a_y, float a_z);
	Vector3(const Vector3& other);
	~Vector3();

	float x, y, z;

	//operator overloads
	Vector3& operator=(const Vector3& other);

	Vector3 operator+(const Vector3& other);
	Vector3& operator+=(const Vector3& other);

	Vector3 operator-(const Vector3& other);
	Vector3& operator-=(const Vector3& other);

	Vector3 operator*(const float scalar);
	void operator*=(const float scalar);

	Vector3 operator-();

	/*
	returns true if Vector not zero (Vector3 (0,0,0)) else returns false;
	*/
	bool operator!();
	/*
	returns true if given other Vector3 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector3& other);

	friend bool operator==(const Vector3& lhs, const Vector3& rhs);

	/*
	returns false if given other Vector3 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector3& other);

	friend bool operator!=(const Vector3& lhs, const Vector3& rhs);

	/*
	returns value of vector subelement at position of given int
	i.e. myVector3[0] = will return x element, myVector[1] will return y and myVector[2] will return z
	EXPECT given int to be greater than or equal to zero AND less than 3.
	*/
	float operator[](int rhs);

	friend std::ostream& operator<<(std::ostream& out, const Vector3& v);

	//vector math functions
	/*
	returns magnitude of this vector
	*/
	float Magnitude();

	/*
	normalize this Vector3
	*/
	void Normalize();

	/*
	return normalized Vector3 from values of this one. This vector is not changed.
	*/
	Vector3 GetNormal();

	/*
	return dot product of this vector and given other vector
	*/
	float DotProduct(const Vector3& other);

	/*
	return Vector3 cross product
	neither this or the given other vector are changed
	*/
	Vector3 CrossProduct(const Vector3& other);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	Vector3 GetLERP(const Vector3& end, float const percent);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	static Vector3 LERP(const Vector3& start, const Vector3& end, float percent);

};

class Vector4
{
public:
	Vector4();

	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);

	/*
	construct and return a Vector4 from given hex number with values x for the red value, y for the
	green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
	assume hex number is from 0x00000000 to 0xFFFFFFFF
	*/
	Vector4(const unsigned int a_hex);

	/*
	construct and return Vector4 as a copy of given Vector4. Note given Vector4 is unchanged during operation.
	*/
	Vector4(const Vector4& other);

	/*
	construct and return a Vector4 from given hex number with values x for the red value, y for the
	green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
	assume hex number is from 0x00000000 to 0xFFFFFFFF
	*/
	static Vector4 ConstructFromHex(const unsigned int a_hex);

	Vector4& operator= (const Vector4& rhs);

	Vector4& operator+=(const Vector4& rhs);
	Vector4 operator+(const Vector4& rhs);

	Vector4& operator-=(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs);
	Vector4 operator-();

	/*
	returns ths value of element pointed by given index.
	i.e. myVector4[0] returns myVector.x, myVector[0] returns myVector.y etc.
	EXPECT: given value must be -1 < index < 4
	*/
	float operator[](const int index);

	/*
	returns true if Vector not zero (Vector4 (0,0,0,0)) else returns false;
	*/
	bool operator!();

	Vector4 operator*(const float scalar);
	void operator*=(const float scalar);

	bool operator==(const Vector4& rhs);
	friend bool operator==(const Vector4& lhs, const Vector4& rhs);
	bool operator!=(const Vector4& rhs);
	friend bool operator!=(const Vector4& lhs, const Vector4& rhs);

	/*
	returns the magnitude of this Vector4
	*/
	float Magnitude();

	/*
	return a new Vector4 of this Vectr4 normalized
	*/
	Vector4 GetNormalized();

	/*
	returns true if this Vector4 able to be normalized, and will normalize this object else returns false and leaves this unchanged (i.e. magnitude of this vector
	is zero)
	*/
	bool Normalize();

	/*
	return dot product of this vector and given other vector
	*/
	float DotProduct(const Vector4& other);

	friend std::ostream& operator<<(std::ostream& out, const Vector4& rhs);

	float x, y, z, w;
};

/*
Representation of a 3X3 matrix
NOTE: All operations assume column major layout
*/
class Matrix3
{
public:

	/*
	Constructs a matrix filled with zeros.
	*/
	Matrix3();

	/*
	The data parameters assume a column major matrix starting in the upper left-hand corner
	and going left to right, top to bottom.
	E.g.
	********
	1  2  3
	4  5  6
	7  8  9
	********
	Matrix3(1,2,3,4,5,6,7,8,9);
	*/
	Matrix3(
		const float m00,
		const float m01,
		const float m02,
		const float m10,
		const float m11,
		const float m12,
		const float m20,
		const float m21,
		const float m22);

	Matrix3(Matrix3& rhs);
	~Matrix3();

	/*
	Returns identity matrix
	e.g.
	*******
	1  0  0
	0  1  0
	0  0  1
	*******
	*/
	static Matrix3 Identity();

	/*
	Returns 3X3 orthographic projection matrix
	*/
	static Matrix3 OrthographicProjection();

	/*
	returns new rotation matrix from given angle in radians.   This assumes the use of a right-handed Cartesian coordinate system
	therefore an angle value greater than 0 rotates counterclockwise, and an angle less than 0 rotates clockwise.
	*/
	static Matrix3 SetupRotation(float radians);

	/*
	returns new scale matrix
	*/
	static Matrix3 SetupScale(const Vector2& scale);

	/*
	return new translation matrix
	*/
	static Matrix3 SetupTranslation(Vector2& translation);

	static Vector3 GetVector3(MATRIX_MAJOR type, int index, const Matrix3& matrix);

	/*
	Transforms the given Vector2 with this Matrix3 returning the Vector2 result.
	NOTE:this converts the given Vector2 to a Vector3 with the z parameter set to one to
	do the matrix math and then returns a Vector2 with the calculated x,y values.
	*/
	Vector2 Transform(const Vector2& point);

	//transposes this matrix
	Matrix3& Transpose();

	//returns a matrix3 the transpose of this. This matrix does not change
	Matrix3 GetTranspose();

	Matrix3& operator=(const Matrix3& rhs);

	Matrix3 operator+(const Matrix3& rhs);
	Matrix3 operator-(const Matrix3& rhs);
	Matrix3 operator*(const Matrix3& rhs);
	friend Vector2 operator*(const Matrix3& lhs, const Vector2& rhs);
	friend Vector3 operator*(const Matrix3& lhs, const Vector3& rhs);

	Matrix3& operator+=(const Matrix3& rhs);
	Matrix3& operator-=(const Matrix3& rhs);
	Matrix3& operator*=(const Matrix3& rhs);
	float* operator[](int rhs);

	//bool operator==(const Matrix3& rhs);
	friend bool operator==(const Matrix3& lhs, const Matrix3& rhs);
	friend bool operator!=(const Matrix3& lhs, const Matrix3& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Matrix3& m);

	float matrix[3][3];
};

/*
Representation of a 4X4 matrix
NOTE: All operations assume column major layout
*/
class Matrix4
{
public:

	/*
	Constructs a matrix filled with zeros.
	*/
	Matrix4();

	/*
	The data parameters assume a column major matrix starting in the upper left-hand corner
	and going left to right, top to bottom.
	E.g.
	*************
	1   2   3   4
	5   6   7   8
	9  10  11  12
	13 14  15  16
	*************
	Matrix4(1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16);
	*/
	Matrix4(
		const float m00,
		const float m01,
		const float m02,
		const float m03,
		const float m10,
		const float m11,
		const float m12,
		const float m13,
		const float m20,
		const float m21,
		const float m22,
		const float m23,
		const float m30,
		const float m31,
		const float m32,
		const float m33);

	Matrix4(Matrix4& rhs);
	~Matrix4();

	/*
	Returns identity matrix
	e.g.
	**********
	1  0  0  0
	0  1  0  0
	0  0  1  0
	0  0  0  1
	**********
	*/
	static Matrix4 Identity();

	/*
	Returns 4X4 orthographic projection matrix
	*/
	static Matrix4 GetOrthographicProjection(const float left, const float right, const float top, const float bottom, const float near, const float far);

	/*
	returns new rotation matrix from given angle in radians around the given AXIS.   This assumes the use of a right-handed Cartesian coordinate system
	therefore an angle value greater than 0 rotates counterclockwise, and an angle less than 0 rotates clockwise.
	*/
	static Matrix4 SetupRotation(AXIS axis, float radians);

	/*
	returns new rotation matrix consisting of products of rotation matrix of given angle around each
	axis x,y and z.
	*/
	static Matrix4 SetupRotation(float radians);

	/* 
	returns new rotation matrix from Vector3 of angles to rotate around each axis
	*/
	static Matrix4 SetupRotation(const Vector3& angles);

	/*
	returns new scale matrix
	*/
	static Matrix4 SetupScale(const Vector3& scale);

	/*
	return new translation matrix
	*/
	static Matrix4 SetupTranslation(Vector3& translation);

	/*
	Transforms the given Vector3 with this Matrix4 returning the Vector3 result.
	NOTE:this converts the given Vector3 to a Vector4 with the w parameter set to one to
	do the matrix math and then returns a Vector3 with the calculated x,y,z values.
	*/
	Vector3 Transform(const Vector3& point);

	/*this static function returns a Vector3 representing the given index (zero based) row or column of the given matrix parameter depending
	on the given MATRIX_MAJOR enum type.
	(e.g.
	Matrix4 MyVector(
	1, 2, 3, 4,
	5, 6, 7, 8,
	9, 10, 11, 12,
	13, 14, 15, 16);
	Matrix4::GetVector4(ROW, 1, MyMatrix); returns a Vector4 representing the second row of MyMatrix => (5, 6, 7, 8)
	Matrix4::GetVector4(COL, 0, MyMatrix); returns a Vector4 representing the first column of MyMatrix => (1, 5, 9, 13)
	*/
	static Vector4 GetVector4(MATRIX_MAJOR type, int index, const Matrix4& matrix);

	/*
	transposes this matrix
	returns reference to this object to allow for operation chaining
	*/
	Matrix4& Transpose();

	//returns a Matrix4 the transpose of this. This matrix does not change
	Matrix4 GetTranspose();

	/*
	Converts this data structure to structure useable by OpenGL
	*/
	void Get(float* a_matrix);

	Matrix4& operator=(const Matrix4& rhs);

	friend Matrix4 operator+(const Matrix4& lhs, const Matrix4& rhs);
	friend Matrix4 operator-(const Matrix4& lhs, const Matrix4& rhs);
	friend Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
	friend Vector4 operator*(const Matrix4& lhs, const Vector4& rhs);

	Matrix4& operator+=(const Matrix4& rhs);
	Matrix4& operator-=(const Matrix4& rhs);
	Matrix4& operator*=(const Matrix4& rhs);
	float* operator[](int index);

	friend bool operator==(const Matrix4& lhs, const Matrix4& rhs);
	friend bool operator!=(const Matrix4& lhs, const Matrix4& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Matrix4& m);

	float matrix[4][4];
};


#endif
