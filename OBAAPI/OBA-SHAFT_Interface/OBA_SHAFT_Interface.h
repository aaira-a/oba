#ifndef OBA_SHAFT_H
#define OBA_SHAFT_H

class OBA_SHAFT_Interface {
	public:
		OBA_SHAFT_Interface();
		static unsigned int getCurrentPulse();
		static double getCurrentSpeed();
};

#endif