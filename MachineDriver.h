#ifndef MASHINEDRIVER_H_
#define MASHINEDRIVER_H_

#include "StateMashine.h"

/**
 * Machine Driver orchestrates State Machines - it contains list of all possible states, executes and switches them.
 *
 * Each execution of particular state returns id of the next state to be executed, or #STATE_NOCHANGE if next iteration
 * should execute current state again.
 *
 * Each state has it's own ID and there can be up to 0-240 states - last 15 are reserved for predefined states. The are
 * defined in StateMashine#mstate_t.
 */
class MachineDriver {

public:

	/**
	 * Creates Machine Driver with number of states given by #states. The var-arg argument contains pointers to
	 * implementation of #StateMashine. There are two rules that you have to follow:
	 * 1) Amount of expected pointers is given by #states
	 * 2) States are numbered starting from 0 to #states. In order to change state, function #changeState(uint8_t)
	 *    takes an int argument and this is the state id determined by it's position in provided var-arg argument.
	 *    For example:
	 *    - if you have created the driver with 5 states, in order to change to last one execute #changeState(4)
	 *    - in order to switch to predefined noop-state execute: #change(STATE_NOOP)
	 */
	MachineDriver(uint8_t states, ...);

	/** returns true if current state is not noop. */
	boolean isRunning();

	void changeState(uint8_t state);
	void execute();

	virtual ~MachineDriver();

private:
	/** Array of pointers to StateMashine obejcts.s */
	StateMashine **states;
	const uint8_t statesCnt;

	/** Currently executed state. */
	StateMashine *current;

	/**
	 * Does nothing ;)
	 */
	class NoopState: public StateMashine {
	public:
		NoopState();
		virtual uint8_t execute();
		virtual void init();
	};
	NoopState *noopState;
};

#endif /* MASHINEDRIVER_H_ */
