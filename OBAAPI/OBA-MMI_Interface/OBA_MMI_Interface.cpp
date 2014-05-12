#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_MMI_Interface.h"

OBA_MMI_Interface::OBA_MMI_Interface() {

}

void OBA_MMI_Interface::sendLEDsignal() {
	LedCommandWord *led;
	led =  (LedCommandWord *)(OTM::ledCommandByteAddress);

	//assign/override accordingly
	led->led_1=1;   //left   // green
	led->led_2=1;   //center // yellow
	led->led_3=1;   //right  // red
}
