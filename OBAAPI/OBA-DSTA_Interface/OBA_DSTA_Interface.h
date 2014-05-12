#ifndef OBA_DSTA_H
#define OBA_DSTA_H

class OBA_DSTA_Interface {
	public:
		OBA_DSTA_Interface();
		static unsigned int getEngagedGearState();
		static unsigned int getIgnitionState();
		static unsigned int getClutchState();
		static unsigned int getBrakeState();
		static unsigned int getAcceleratorState();
};

#endif