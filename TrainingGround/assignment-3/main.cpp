#include "common.h"
#include "LoadVehicle.h"
#include "PassengerVehicle.h"
#include "EmergencyEquipment.h"
#include "EmergecyVehicle.h"
#include "Decision.h"
#include <list>
using namespace std;

int main() {
	// the vehicle list.
	Decision::VehicleList  vehicleList;

	// create Vehicles. 
	LoadVehicle * lv1 = new LoadVehicle ( "load1" );
	vehicleList.push_back ( lv1 );

	PassengerVehicle * pv1 = new PassengerVehicle ( "passenger1" );
	vehicleList.push_back ( pv1 );

	EmergecyVehicle * ev1 = new EmergecyVehicle ( "emergency1", "super", "buaa", 101 );
	vehicleList.push_back ( ev1 );

	// create Decison object.
	Decision decision ( vehicleList );

	pc ("part 1");
	decision.printVehiclesSpecifications();
	cr;

	pc ("part 2");
	decision.printEmergencyVehicles();
	cr;

	pc ("part 3");
	ps ( decision.numberLongDistanceEmergencyVehicles() );
	cr;

	pc ("part 4");
	ps ( decision.numBeds() );
	cr;

	pc ("part 5");
	ps ( decision.numPassengers() );
	cr;

	// clear...
	delete lv1;
	delete pv1;
	delete ev1;

	return 0;
}
