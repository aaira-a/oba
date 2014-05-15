#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_DSTA_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"

OBA_DSTA_Interface::OBA_DSTA_Interface() {

}

	DrivinStationStateWord *state;

unsigned int DSTA::getEngagedGearState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->engagedGear;
}


bool DSTA::getIgnitionState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->ignitionState;
}


bool DSTA::getClutchState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->clutchState;
}


bool DSTA::getBrakeState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->brakeState;
}


bool DSTA::getAcceleratorState() {
	state =  (DrivinStationStateWord *) (OTM::drivingControlsStateWordAddress);
	return state->acceleratorState;
}


void DSTA::handleDSTAinterrupt(DrivingStationInterruptStatusWord *whatChanged) {
	whatChanged = (DrivingStationInterruptStatusWord *) (OTM::drivingControlsInterruptWordAddress);


		if (whatChanged->brakeFlag || whatChanged->clutchFlag) {
			CRUISE::suspendCruising();
		}

		/*	cout << "\n\naccelerator: " << eventDSTA->acceleratorFlag <<
		"\nbrake: " << eventDSTA->brakeFlag <<
		"\nclutch:" << eventDSTA->clutchFlag <<
		"\nignition:" << eventDSTA-> ignitionFlag;
		*/

}