#include "MachineDriver.h"
#include "StateMashine.h"

MachineDriver::MachineDriver(uint8_t statesCnt, ...) :
		statesCnt(statesCnt),noopState() {
	this->current = &noopState;

	states = new StateMashine*[statesCnt];
	va_list va;
	va_start(va, statesCnt);
	for (uint8_t sIdx = 0; sIdx < statesCnt; sIdx++) {
		states[sIdx] = va_arg(va, StateMashine*);
	}
}

MachineDriver::~MachineDriver() {
	delete (states);
}

void MachineDriver::changeState(uint8_t state) {
#if DEBUG_SM
	debug(F("Change state to %d of %d", state, statesCnt));
#endif

	switch (state) {
	case StateMashine::STATE_NOCHANGE:
		return;

	case StateMashine::STATE_NOOP:
		current = &noopState;
		break;

	default:
		current = states[state];
		break;
	}

	current->init();
}

boolean MachineDriver::isRunning() {
	return current != &noopState;
}

void MachineDriver::execute() {
	uint8_t retState = current->execute();
	changeState(retState);
}

// ################ NoopState ################
MachineDriver::NoopState::NoopState() {
}

MachineDriver::NoopState::~NoopState() {
}

void MachineDriver::NoopState::init() {
}

uint8_t MachineDriver::NoopState::execute() {
	return StateMashine::STATE_NOCHANGE;
}

