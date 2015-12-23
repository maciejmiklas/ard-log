#include "MachineDriver.h"
#include "StateMashine.h"

MachineDriver::MachineDriver(uint8_t statesCnt, ...) :
		statesCnt(statesCnt), noopState(), states(new StateMashine*[statesCnt]) {
	this->current = &noopState;

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

#if DEBUG_SM
	log(F("Change state to %d of %d"), state, statesCnt);
#endif

	current->init();
}
void MachineDriver::reset() {
	for (uint8_t sIdx = 0; sIdx < statesCnt; sIdx++) {
		states[sIdx]->reset();
	}
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

void MachineDriver::NoopState::reset() {
}

uint8_t MachineDriver::NoopState::execute() {
	return StateMashine::STATE_NOCHANGE;
}

