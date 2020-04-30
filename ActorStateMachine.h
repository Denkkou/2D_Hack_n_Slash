#ifndef anActorStateMachineFile
#define anActorStateMachineFile

class ActorStateMachine {
public:
	bool IS_GROUNDED;

	bool CAN_JUMP;
	bool IS_JUMPING;

	bool IS_IDLE;
	bool IS_FACING_RIGHT;
	bool IS_FACING_LEFT;
	bool IS_AIMING_UP;
	bool IS_AIMING_DOWN;

	bool IS_ATTACKING;
};

#endif