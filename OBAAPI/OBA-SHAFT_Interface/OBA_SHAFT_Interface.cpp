#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_SHAFT_Interface.h"
#include "../OBA-MMI_Interface/OBA_MMI_Interface.h"
#include "../../OBACalibration/OBA_Calibration.h"


OBA_SHAFT_Interface::OBA_SHAFT_Interface() {

}


static double calibrationReference = 5291.0053;
static unsigned int lastpulse = 0;
static double speed = 0;
static unsigned int speedInt = 0;


void  SHAFT::calculateSpeed() {
	speed = ((getCurrentPulse() - lastpulse)/calibrationReference)*3600;
	speedInt = static_cast<unsigned int>(((getCurrentPulse() - lastpulse)/calibrationReference)*3600);
	lastpulse = getCurrentPulse();

	if (speedInt >= 180 ) {
		MMI::sendLEDsignal(2, 1);
		MMI::sendLEDsignal(3, 1);
	}

	else if (speedInt>=150 && speedInt<=180) {
		MMI::sendLEDsignal(2, 1);
		MMI::sendLEDsignal(3, 0);
	}

	else if (speedInt < 150 ) {
		MMI::sendLEDsignal(2, 0);
		MMI::sendLEDsignal(3, 0);
	}
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

void SHAFT::setCalibrationReference(double calibrationOverride) {
	calibrationReference = calibrationOverride;
}

unsigned int SHAFT::getCalibrationReference() {
	return static_cast<unsigned int>(calibrationReference);
}