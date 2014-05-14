#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_SHAFT_Interface.h"

OBA_SHAFT_Interface::OBA_SHAFT_Interface() {

}


double calibrationconst = 5291.0053;
static unsigned int lastpulse = 0;
static double speed = 0;

void  SHAFT::calculateSpeed() {
	speed = ((getCurrentPulse() - lastpulse)/calibrationconst)*3600;
	lastpulse = getCurrentPulse();
}


unsigned int SHAFT::getCurrentPulse() {
	CounterWord *pulse;
	pulse = (CounterWord *) (OTM::pulseCounterWordAddress);
	return pulse->pulsecount;
}


double SHAFT::getCurrentSpeed() {
	return speed;
}
