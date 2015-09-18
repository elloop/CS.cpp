#include "common.h"
#include "Decision.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include "EmergecyVehicle.h"
// construtor.
Decision::Decision ( VehicleList & vList ) : list_ ( vList )
{ }
// print Vehicles' Specifications in the lis_.
void Decision::printVehiclesSpecifications() const {
	for_each ( list_.begin(), list_.end(), std::mem_fun ( &Vehicle::printSpecification ) );
}

// print all the Emergency Vehicles.
void Decision::printEmergencyVehicles() const {
	VehicleList::const_iterator iter = list_.begin();
	EmergecyVehicle * evp ( 0 );
	while ( iter != list_.end() ) {
		evp = dynamic_cast<EmergecyVehicle *> ( *iter );
		if ( evp ) {
			evp->printSpecification();
		}
		++iter;
	}
}

// print Emergency Vehicles who can travel more than 800 km.
int Decision::numberLongDistanceEmergencyVehicles() const {
	int cnt ( 0 );                                // counter.
	VehicleList::const_iterator iter = list_.begin();
	EmergecyVehicle * evp ( 0 );

	while ( iter != list_.end() ) {
		evp = dynamic_cast<EmergecyVehicle *> ( *iter );
		if ( evp && evp->computeTravelDistance() > 800 ) {
			++cnt;
		}
		++iter;
	}
	return cnt;
}
// compute how many mobile beds all the Vehicle have.
int Decision::numBeds() const {
	int beds ( 0 );
	VehicleList::const_iterator iter = list_.begin();
	EmergecyVehicle * evp ( 0 );

	while ( iter != list_.end() ) {
		evp = dynamic_cast<EmergecyVehicle *> ( *iter );
		if ( evp ) {
			beds += evp->getNumBeds();
		}
		++iter;
	}
	return beds;
}
// compute how many passengers all the vehicle can move.
int Decision::numPassengers() const {
	int passengers ( 0 );
	VehicleList::const_iterator iter = list_.begin();
	PassengerVehicle * pvp ( 0 );

	while ( iter != list_.end() ) {
		pvp = dynamic_cast<PassengerVehicle *> ( *iter );
		if ( pvp ) {
			passengers += pvp->getNumberOfPassenger();
		}
		++iter;
	}
	return passengers;
}

