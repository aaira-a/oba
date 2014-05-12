#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_THRO_Interface.h"

OBA_THRO_Interface::OBA_THRO_Interface() {

}

void OBA_THRO_Interface::sendThrottleSignal() {
	ThrottleCommandWord *throttle;
	throttle = (ThrottleCommandWord *)(OTM::throttleCommandWordAddress);
	throttle->outputvoltagevalue=80;
	throttle->paritybit=1;
}

unsigned int OBA_THRO_Interface::getThrottleResponse() {
	ThrottleResponseWord *throttle;
	throttle = (ThrottleResponseWord *)(OTM::throttlePositionWordAddress);
	return throttle->inputvoltagevalue;
}