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

unsigned int OBA_DSTA_Interface::getIgnitionState() {
	DrivinStationStateWord *state;
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->ignitionState;
}

unsigned int OBA_DSTA_Interface::getClutchState() {
	DrivinStationStateWord *state;
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->clutchState;
}

unsigned int OBA_DSTA_Interface::getBrakeState() {
	DrivinStationStateWord *state;
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->brakeState;
}

unsigned int OBA_DSTA_Interface::getAcceleratorState() {
	DrivinStationStateWord *state;
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->acceleratorState;
}