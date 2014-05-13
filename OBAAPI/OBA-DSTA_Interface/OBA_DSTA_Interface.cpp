#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_DSTA_Interface.h"

OBA_DSTA_Interface::OBA_DSTA_Interface() {

}

	DrivinStationStateWord *state;

unsigned int OBA_DSTA_Interface::getEngagedGearState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->engagedGear;
}

unsigned int OBA_DSTA_Interface::getIgnitionState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->ignitionState;
}

unsigned int OBA_DSTA_Interface::getClutchState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->clutchState;
}

unsigned int OBA_DSTA_Interface::getBrakeState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->brakeState;
}

unsigned int OBA_DSTA_Interface::getAcceleratorState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->acceleratorState;
}