
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
#define CYCLE_MS 10

static void setLeds(struct LedStateMachine* inst, BOOL a, BOOL b,BOOL c,BOOL d){
	inst->led1 = a;
	inst->led2 = b;
	inst->led3 = c;
	inst->led4 = d;
}

void LedStateMachine(struct LedStateMachine* inst)
{
	BOOL blink;
	
	switch (inst->state){
		case ST_UNKNOWN:
			inst->timer +=CYCLE_MS;
			if (inst->timer >= 1000) inst->timer = 0;
			blink = (inst->timer < 500);
			setLeds(inst, blink, blink, blink, blink);
			return;
		
		case ST_ACC_POS: case ST_DEC_NEG: setLeds(inst, 1,0,0,0); break;
		case ST_POS: case ST_NEG: setLeds(inst, 1,1,0,0); break;
		case ST_DEC_POS: case ST_ACC_NEG: setLeds(inst, 1,1,1,0); break;
		case ST_CLOSE: setLeds(inst, 1,1,1,1); break;
		default: setLeds(inst, 0,0,0,0); break;
	}
	inst->timer = 0;
}
