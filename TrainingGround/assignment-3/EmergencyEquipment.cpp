#include "EmergencyEquipment.h"
#include "common.h"

/***************************************************************************************
	函数名称:  EmergencyEquipment
	函数描述:  constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
EmergencyEquipment::EmergencyEquipment ( int sirenNoiseDistance /*= 500*/, int numBeds /*= 2*/ )
	: sirenNoiseDistance_ ( sirenNoiseDistance ), numBeds_ ( numBeds )
{ }

void EmergencyEquipment::printSpecification() const {
	ps ( sirenNoiseDistance_ );
	ps ( numBeds_ );
}

EmergencyEquipment::~EmergencyEquipment() { }
