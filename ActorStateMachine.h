#ifndef anActorStateMachineFile
#define anActorStateMachineFile

class ActorStateMachine {
public:
	bool IS_GROUNDED;

	bool CAN_JUMP;
	bool IS_JUMPING;
	//player is falling if not jumping and not grounded

	bool IS_IDLE;

	bool IS_ATTEMPTING_ATTACK;
	bool IS_ATTACKING;
};

#endif