#ifndef  aVector2dFILE
#define aVector2dFILE

class Vector2D {
public:
	Vector2D();
	Vector2D(int eX, int eY);
	~Vector2D();

	int X, Y;
	float magnitude();
};

#endif
