objs = Vehicle.o LoadVehicle.o PassengerVehicle.o EmergencyEquipment.o EmergecyVehicle.o Decision.o main.o

v : $(objs)
	g++ -o v $(objs)

Vehicle.o : Vehicle.cpp
LoadVehicle.o : LoadVehicle.cpp
PassengerVehicle.o : PassengerVehicle.cpp
EmergencyEquipment.o : EmergencyEquipment.cpp
EmergecyVehicle.o : EmergecyVehicle.cpp
Decision.o : Decision.cpp
main.o : main.cpp

.PHONY : clean
clean : 
			-rm v $(objs) *.orig
