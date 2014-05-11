#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_SHAFT_Interface.h"

OBA_SHAFT_Interface::OBA_SHAFT_Interface() {

}


unsigned int OBA_SHAFT_Interface::getCurrentPulse() {
	CounterWord *pulse;
	pulse = (CounterWord *) (OTM::pulseCounterWordAddress);
	return pulse->pulsecount;
	//cout << " \n\t" << pulse->pulsecount;  //uncomment to see the value
}