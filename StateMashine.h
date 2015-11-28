#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_

#include "Arduino.h"

class StateMashine {

public:
	virtual uint8_t execute() = 0;
	virtual void init() = 0;
	virtual ~StateMashine() = 0;

	enum mstate_t {
		STATE_NOCHANGE = 254, STATE_NOOP = 255
	};

protected:
	StateMashine();
};

#endif /* STATEMASHINE_H_ */
