#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_

#include "Arduino.h"

#define DEBUG_SM false

/**
 * State Machine is stateful object that represents particular state. On each loop (MachineDriver#execute()) the method
 * #execute() will be called - until in returns next state. In this case the next State Machine will get executed,...
 * an so on.
 */
class StateMashine {

public:
	/**
	 * This function returns id of the state that will be executed as next,  or #STATE_NOCHANGE if state should not
	 * be changed.
	 */
	virtual uint8_t execute() = 0;
	virtual void init() = 0;
	virtual ~StateMashine() = 0;

	/**
	 * Predefined states.
	 */
	enum mstate_t {
		STATE_NOCHANGE = 254, STATE_NOOP = 255
	};

protected:
	StateMashine();
};

#endif /* STATEMASHINE_H_ */
