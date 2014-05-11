#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_SHAFT_Interface.h"

OBA_SHAFT_Interface::OBA_SHAFT_Interface() {

}

double calibrationconst = 5291.0053;
unsigned int lastpulse = 0;
double speed = 0;

unsigned int OBA_SHAFT_Interface::getCurrentPulse() {
	CounterWord *pulse;
	pulse = (CounterWord *) (OTM::pulseCounterWordAddress);
	return pulse->pulsecount;
	//cout << " \n\t" << pulse->pulsecount;  //uncomment to see the value
}

double OBA_SHAFT_Interface::getCurrentSpeed() {
	
	speed = ((getCurrentPulse() - lastpulse)/calibrationconst)*3600;
	lastpulse = getCurrentPulse();
	//cout << speed << " : " << getCurrentPulse()/calibrationconst << endl;
	return speed;
}