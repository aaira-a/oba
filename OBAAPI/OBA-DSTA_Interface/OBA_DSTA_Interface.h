#ifndef OBA_DSTA_H
#define OBA_DSTA_H

class OBA_DSTA_Interface {
	public:
		OBA_DSTA_Interface();
		static unsigned int getEngagedGearState();
		static bool getIgnitionState();
		static bool getClutchState();
		static bool getBrakeState();
		static bool getAcceleratorState();
};

typedef OBA_DSTA_Interface	DSTA;

#endif