#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_THRO_Interface.h"
#include "../OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"

OBA_THRO_Interface::OBA_THRO_Interface() {

}


void THRO::sendThrottleSignal(unsigned int voltage) {
	ThrottleCommandWord *throttle;
	throttle = (ThrottleCommandWord *)(OTM::throttleCommandWordAddress);
	throttle -> outputvoltagevalue = voltage;
	throttle -> paritybit = getOddParityBit(voltage);
}


unsigned int THRO::getThrottleResponse() {
	ThrottleResponseWord *throttle;
	throttle = (ThrottleResponseWord *)(OTM::throttlePositionWordAddress);
	return throttle->inputvoltagevalue;
}


bool THRO::getOddParityBit(unsigned int x) {
	x = ((x >> 1) & 0x55555555) + (x & 0x55555555);
	x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
	x = ((x >> 4) & 0x0F0F0F0F) + (x & 0x0F0F0F0F);
	x = ((x >>  8 ) + x);
	x = ((x >>  16 ) + x);
	return !(x&0x01); //return odd parity bit
}


void THRO::maintainSpeed(int cruisingSpeed) {
	
	//pseudo
	// 1 - get current speed
	// 2 - get current throttle voltage
	// 3 - adjust accordingly??
	// 4 - maybe start by getting the last voltage (for new, can be from user), old, can put an internal vold var
	// 5 - ++ or -- accordingly
	// 6 - infinity & beyond?

	static unsigned int throttleCounter = getThrottleResponse();

	for (;;) {

		if (SHAFT::getCurrentSpeed() < cruisingSpeed) {
			sendThrottleSignal(throttleCounter++);
		}

		if (SHAFT::getCurrentSpeed() > cruisingSpeed) {
			sendThrottleSignal(throttleCounter--);
		}
	}
}
