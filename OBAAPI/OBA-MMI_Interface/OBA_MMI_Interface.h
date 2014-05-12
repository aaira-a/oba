#ifndef OBA_MMI_H
#define OBA_MMI_H

class OBA_MMI_Interface {
	public:
		OBA_MMI_Interface();
		static void sendLEDsignal();
		static void displayMessage();
		static enum KEYMAP;
};

#endif