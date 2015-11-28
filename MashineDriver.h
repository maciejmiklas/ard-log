#ifndef MASHINEDRIVER_H_
#define MASHINEDRIVER_H_

#include "StateMashine.h"

class MashineDriver {

public:
	MashineDriver(uint8_t states, ...);
	virtual ~MashineDriver();
	void changeState(uint8_t state);
	void execute();

private:
	StateMashine **states;
	const uint8_t statesCnt;
	StateMashine *stateMashine;

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
