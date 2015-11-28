#include "MashineDriver.h"
#include "StateMashine.h"

MashineDriver::MashineDriver(uint8_t statesCnt, ...) :
		statesCnt(statesCnt) {
	this->noopState = new MashineDriver::NoopState();
	this->stateMashine = noopState;

	states = new StateMashine*[statesCnt];
	va_list va;
	va_start(va, statesCnt);
	for (uint8_t sIdx = 0; sIdx < statesCnt; sIdx++) {
		states[sIdx] = va_arg(va, StateMashine *);
	}
}

MashineDriver::~MashineDriver() {
	for (uint8_t sIdx = 0; sIdx < statesCnt; sIdx++) {
		delete (states[sIdx]);
	}
	delete (states);
}

void MashineDriver::changeState(uint8_t state) {
#if DEBUG_TA
	debug(F("Drive %d of %d", state, statesCnt));
#endif

	switch (state) {
	case StateMashine::STATE_NOCHANGE:
		return;

	case StateMashine::STATE_NOOP:
		stateMashine = noopState;
		break;

	default:
		stateMashine = states[state];
		break;
	}

	stateMashine->init();
}

void MashineDriver::execute() {
	uint8_t retState = stateMashine->execute();
	changeState(retState);
}

// ################ NoopState ################
MashineDriver::NoopState::NoopState() {
}

void MashineDriver::NoopState::init() {
}

uint8_t MashineDriver::NoopState::execute() {
	return StateMashine::STATE_NOCHANGE;
}

