#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_SHAFT_Interface.h"
#include "../OBA-MMI_Interface/OBA_MMI_Interface.h"

OBA_SHAFT_Interface::OBA_SHAFT_Interface() {

}


double calibrationconst = 5291.0053;
static unsigned int lastpulse = 0;
static double speed = 0;
static unsigned int speedInt = 0;

void  SHAFT::calculateSpeed() {
	speed = ((getCurrentPulse() - lastpulse)/calibrationconst)*3600;
	speedInt = static_cast<unsigned int>(((getCurrentPulse() - lastpulse)/calibrationconst)*3600);
	lastpulse = getCurrentPulse();

/*
	if (speedInt < 150 ) {
		MMI::sendLEDsignal(2, 0);
		MMI::sendLEDsignal(3, 0);
	}

	if (speedInt>=150) {
		MMI::sendLEDsignal(2, 1);
		MMI::sendLEDsignal(3, 0);
	}

	if (speedInt >= 180 ) {
		MMI::sendLEDsignal(2, 1);
		MMI::sendLEDsignal(3, 1);
	}
*/
}


unsigned int SHAFT::getCurrentPulse() {
	CounterWord *pulse;
	pulse = (CounterWord *) (OTM::pulseCounterWordAddress);
	return pulse->pulsecount;
}


double SHAFT::getCurrentSpeed() {
	return speed;
}

unsigned int SHAFT::getCurrentSpeedInt() {
	return speedInt;
}