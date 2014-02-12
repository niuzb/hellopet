#ifndef _ILOGIC_MANAGER_H_
#define _ILOGIC_MANAGER_H_

class ILogicManager
{
public :		
	/*
	* @prototype: startGame()
	* @note:
	*     start the game now, bring the player to the main menu layer.
	* @param: void
	* @return: void
	*/
	virtual void startGame() = 0;
	virtual void exitGame() = 0;
};

#endif	//_ILOGIC_MANAGER_H_