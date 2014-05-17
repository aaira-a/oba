#ifndef OBA_MAINT_H
#define OBA_MAINT_H

class OBA_Maintenance {
	public:
		OBA_Maintenance();

		static void maintenanceRoutine(int tick);
		static void maintenanceChecker();
		static void maintenanceMessageService1(int tick);
		static unsigned int getCurrentMileage();
		static void debugger(unsigned int overrideMileage);
};

typedef OBA_Maintenance		MAINT;

#endif