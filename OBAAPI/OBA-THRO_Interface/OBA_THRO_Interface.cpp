#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_THRO_Interface.h"

OBA_THRO_Interface::OBA_THRO_Interface() {

}

void OBA_THRO_Interface::sendThrottleSignal(unsigned int voltage) {
	ThrottleCommandWord *throttle;
	throttle = (ThrottleCommandWord *)(OTM::throttleCommandWordAddress);
	throttle -> outputvoltagevalue = voltage;
	throttle -> paritybit = getOddParityBit(voltage);
}

unsigned int OBA_THRO_Interface::getThrottleResponse() {
	ThrottleResponseWord *throttle;
	throttle = (ThrottleResponseWord *)(OTM::throttlePositionWordAddress);
	return throttle->inputvoltagevalue;
}

bool OBA_THRO_Interface::getOddParityBit(unsigned int x) {
	x = ((x >> 1) & 0x55555555) + (x & 0x55555555);
	x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
	x = ((x >> 4) & 0x0F0F0F0F) + (x & 0x0F0F0F0F);
	x = ((x >>  8 ) + x);
	x = ((x >>  16 ) + x);
	return !(x&0x01); //return odd parity bit
}
