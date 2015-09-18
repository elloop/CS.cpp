#ifndef ELLOOP_DECISION_H
#define ELLOOP_DECISION_H
#include <list>
#include "Vehicle.h"

class Decision {
public:
	typedef std::list<Vehicle *> VehicleList;

	Decision ( VehicleList & vList );

	void printVehiclesSpecifications() const;
	void printEmergencyVehicles() const;
	int numberLongDistanceEmergencyVehicles() const;
	int numBeds() const;
	int numPassengers() const;

private:
	VehicleList & list_;
};

#endif
