#ifndef STATEMASHINE_H_
#define STATEMASHINE_H_

#include "Arduino.h"

class StateMashine {

public:
	virtual uint8_t execute() = 0;
	virtual void init() = 0;
	virtual ~StateMashine() = 0;

protected:
	StateMashine();
};

#endif /* STATEMASHINE_H_ */
