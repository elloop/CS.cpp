#include "LoadVehicle.h"
#include "common.h"

/***************************************************************************************
	函数名称:  LoadVehicle::LoadVehicle
	函数描述:  constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
LoadVehicle::LoadVehicle ( const char * type /*= "car"*/, int numberOfWheels /*= 6 */
													 , double loadCapacity /*= 500*/, double towingCapacity /*= 5000 */
													 , double gasTankSize /*= 200*/, double fuelConsumption /*= 6*/ )
	: Vehicle ( type, "ottawa01", gasTankSize, fuelConsumption )
	, numberOfWheels_ ( numberOfWheels )
	, loadCapacity_ ( loadCapacity ), towingCapacity_ ( towingCapacity )
{ }

void LoadVehicle::printSpecification() const {
	Vehicle::printSpecification();
	printLoadVehicle();
	cr;
}

// print self's members.
void LoadVehicle::printLoadVehicle() const {
	ps ( towingCapacity_ );
	ps ( loadCapacity_ );
	ps ( numberOfWheels_ );
}

double LoadVehicle::computeTravelDistance() const {
	double distance = Vehicle::computeTravelDistance();
	if ( numberOfWheels_ < 5 )
	{ return distance; }
	else
	{ return distance * ( 100 - ( numberOfWheels_ - 4 ) / 2 * 5 ) / 100; }
}

LoadVehicle::~LoadVehicle() {
}
