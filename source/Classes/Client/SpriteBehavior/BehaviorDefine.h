#ifndef _BEHAVIOR_DEFINE_H_
#define _BEHAVIOR_DEFINE_H_

struct MoveStep
{
	int xOffset;
	int yOffset;
	MoveStep(){
		xOffset = 0;
		yOffset = 0;
	}
	MoveStep(int xOffset,int yOffset){
		this->xOffset = xOffset;
		this->yOffset = yOffset;
	}
};

typedef enum{
	MOVE_UP = 0,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP_LEFT,
	MOVE_UP_RIGHT,
	MOVE_DOWN_LEFT,
	MOVE_DOWN_RIGHT,
	MOVE_TYPE_UNKNOW
}EMoveStepType;


extern const MoveStep GMoveSteps[];


#endif	//_BEHAVIOR_DEFINE_H_