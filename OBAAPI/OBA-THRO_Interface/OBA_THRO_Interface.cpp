#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_THRO_Interface.h"
#include "../OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"

OBA_THRO_Interface::OBA_THRO_Interface() {

}
	//static unsigned int throttleCounter = 0;
	static bool isMaintaining = 0;
	static unsigned int speedToMaintain = 0;

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


void THRO::setMaintainSpeed(int speed) {
		isMaintaining = 1;
		speedToMaintain = speed;
		//throttleCounter = getThrottleResponse();
}

void THRO::maintainSpeed() {

		if (SHAFT::getCurrentSpeed() < speedToMaintain) {
			sendThrottleSignal(80);
		}

		if (SHAFT::getCurrentSpeed() > speedToMaintain) {
			sendThrottleSignal(40);
		}
	
}