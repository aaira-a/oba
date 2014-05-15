#ifndef OBA_SHAFT_H
#define OBA_SHAFT_H

class OBA_SHAFT_Interface {
	public:
		OBA_SHAFT_Interface();
		static unsigned int getCurrentPulse();
		static void calculateSpeed();
		static double getCurrentSpeed();
		static unsigned int getCurrentSpeedInt();
};

typedef OBA_SHAFT_Interface		SHAFT;

#endif