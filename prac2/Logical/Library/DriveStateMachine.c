
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
#define CMD_SHUTDOWN 0x06
#define CMD_SWITCH_ON 0x07
#define CMD_ENABLE 0x0F
#define CMD_FAULT_RESET 0x80

#define STATE_MASK 0x6F
#define STATE_READY_TO_SWITCH_ON 0x21
#define STATE_SWITCHED_ON 0x23
#define STATE_OP_ENABLED 0x27
#define STATE_FAULT_BIT 0x08

void DriveStateMachine(struct DriveStateMachine* inst)
{	     
	UINT st = inst->state & STATE_MASK;
	
	switch (inst->step){
		case 0:
			inst->speed = 0;
			inst->command = (inst->state & STATE_FAULT_BIT) ? CMD_FAULT_RESET : CMD_SHUTDOWN;
			if (inst->enable && st == STATE_READY_TO_SWITCH_ON)
				inst->step = 1;
			break;
		case 1:
			inst->speed = 0;
			inst->command = CMD_SWITCH_ON;
			if (!inst->enable) inst->step = 0;
			else if (st == STATE_SWITCHED_ON) inst->step = 2;
		case 2:
			inst->command = CMD_ENABLE;
			inst->speed = inst->setSpeed;
			if (!inst->enable || (inst->state & STATE_FAULT_BIT))
				inst->step = 0;
			break;
	}		

}
