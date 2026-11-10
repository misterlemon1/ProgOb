
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{	
	doorSM.state = stateMachine.state; 
	DoorStateMachine(&doorSM);
	
	stateMachine.enable = 1;
	stateMachine.setSpeed = doorSM.speed;
	DriveStateMachine(&stateMachine);
	
	ledSM.state = doorSM.doorState;
	LedStateMachine(&ledSM);

	
}

void _EXIT ProgramExit(void)
{

}

