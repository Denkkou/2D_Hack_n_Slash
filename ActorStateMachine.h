#ifndef anActorStateMachineFile
#define anActorStateMachineFile

class ActorStateMachine {
public:
	bool IS_GROUNDED;
	bool IS_FALLING;

	bool IS_ATTEMPTING_JUMP;
	bool IS_JUMPING;

	bool IS_IDLE;

	bool IS_ATTEMPTING_ATTACK;
	bool IS_ATTACKING;
};

#endif