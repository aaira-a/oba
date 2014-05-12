#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_DSTA_Interface.h"

OBA_DSTA_Interface::OBA_DSTA_Interface() {

}

unsigned int OBA_DSTA_Interface::getEngagedGearState() {
	DrivinStationStateWord *state;
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->engagedGear;
}
