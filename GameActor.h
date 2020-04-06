#pragma once

class GameActor {
public:
	virtual void Jump();
	virtual void Attack();
	virtual void MoveLeft();
	virtual void MoveRight();
};

/* these should be pure virtual and overridden by the player
class which inherits from it, but they are like this for
getting it to compile*/