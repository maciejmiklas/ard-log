#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_

#include "Arduino.h"

#define LOG_SM false

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

	/**
	 * This method will be called always before switching to this state machine from another one. This can happen
	 * multiple times during single workflow. For example: machine A switches to machine B, and after that B to A
	 */
	virtual void init() = 0;

	/**
	 * This method resets whole workflow - this happens when state machine has to process completely new data. For
	 * example animating new sprite.
	 */
	virtual void reset() = 0;

	/**
	 * The execution of each state returns ID of next state, or no change. If state changes, the #execute() method of
	 * new state will be executed by machine driver on next iteration (as next sprite frame). But some states have only
	 * organizing propose - they redirect to another state without doing any useful job. In this case such state can
	 * be marked as intermediate - when #execute() returns Id of new state, this state will be executed immediately and
	 * not as usual on next iteration.
	 */
	virtual boolean isIntermediate() = 0;
	virtual ~StateMashine() = 0;

	/**
	 * Predefined states.
	 */
	enum mstate_t {
		STATE_RESET = 253, STATE_NOCHANGE = 254, STATE_NOOP = 255
	};

protected:
	StateMashine();
};

#endif /* STATEMASHINE_H_ */
