
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
#define V_FAST 600
#define V_SLOW 150
#define CMD_CLOSE 1
#define DRV_OP_ENABLED 0x27

void DoorStateMachine(struct DoorStateMachine* inst)
{
	INT v = 0;
	BOOL closeCMD = (inst->direction == CMD_CLOSE);
	
	if ((inst->state & 0x6F) != DRV_OP_ENABLED){
		inst->doorState = ST_INIT;	
	}
	BOOL sw1_ch = (inst->sw1 != inst->sw1old);
	BOOL sw2_ch = (inst->sw2 != inst->sw2old);
	BOOL sw3_ch = (inst->sw3 != inst->sw3old);
	BOOL sw4_ch = (inst->sw4 != inst->sw4old);
	
	inst->sw1old = inst->sw1;
	inst->sw2old = inst->sw2;
	inst->sw3old = inst->sw3;
	inst->sw4old = inst->sw4;
	
	switch (inst->doorState){
		case ST_INIT:
			v = 0;
			if ((inst->state & 0x6F) == DRV_OP_ENABLED){
				inst->doorState = ST_UNKNOWN;	
			}
			break;
		
		case ST_UNKNOWN:
			if (closeCMD) {
				v = V_SLOW;
				if (sw4_ch){
					inst->doorState = ST_CLOSE;	
				}}
			else {
				v = -V_SLOW;
				if (sw1_ch){
					inst->doorState = ST_OPEN;
				}
			}
			break;
		
		case ST_OPEN:
			v = 0;
			if (closeCMD && sw1_ch){
				inst->doorState = ST_ACC_POS;
			}
			break;
			
		case ST_ACC_POS:
			v = V_SLOW;
			if (sw2_ch) {
				inst->doorState = ST_POS;
			}
			else if (!closeCMD){
				inst->doorState = ST_DEC_NEG;
			}
			break;
			
			
		case ST_POS:
			v = V_FAST;
			if (sw3_ch) {
				inst->doorState = ST_DEC_POS;
			}
			else if (!closeCMD){
				inst->doorState = ST_NEG;
			}
			break;	
	
		case ST_DEC_POS:
			v = V_SLOW;
			if (sw4_ch) {
				inst->doorState = ST_CLOSE;
			}
			else if (!closeCMD){
				inst->doorState = ST_ACC_NEG;
			}
			break;

		case ST_CLOSE:
			v = 0;
			if (!closeCMD && sw4_ch){
				inst->doorState = ST_ACC_NEG;
			}
			break;
		
		case ST_ACC_NEG:
			v = -V_SLOW;
			if (sw3_ch) {
				inst->doorState = ST_NEG;
			}
			else if (closeCMD){
				inst->doorState = ST_DEC_POS;
			}
			break;	
		
		case ST_NEG:
			v = -V_FAST;
			if (sw2_ch) {
				inst->doorState = ST_DEC_NEG;
			}
			else if (closeCMD){
				inst->doorState = ST_POS;
			}
			break;
		
		case ST_DEC_NEG:
			v = -V_SLOW;
			if (sw1_ch) {
				inst->doorState = ST_OPEN;
			}
			else if (closeCMD){
				inst->doorState = ST_ACC_POS;
			}
			break;	
	}
	inst->speed = v;
}