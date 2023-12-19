namespace hel::math
{
	struct Vector3
	{
		float x, y, z;

		float dot(const Vector3& other) const;
		Vector3 cross(const Vector3& other) const;

		void operator=(const Vector3& other);
		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator-() const;
		Vector3 operator*(const Vector3& other) const;
		Vector3 operator*(float scalar) const;
		Vector3 operator/(float scalar) const;

	}; // include functions later
}