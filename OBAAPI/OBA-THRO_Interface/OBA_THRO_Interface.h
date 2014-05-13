#ifndef OBA_THRO_H
#define OBA_THRO_H

class OBA_THRO_Interface {
	public:
		OBA_THRO_Interface();
		static void sendThrottleSignal(unsigned int voltage);
		static unsigned int getThrottleResponse();
		static bool getOddParityBit(unsigned int x);
};

#endif