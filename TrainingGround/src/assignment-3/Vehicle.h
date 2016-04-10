
#ifndef  ELLOOP_VEHICLE_H
#define	ELLOOP_VEHICLE_H		

class Vehicle
{
public:
    Vehicle (const char * type = "car", const char*licensePlate = "ottawa01"
        , double gasTankSize = 100.0, double fuelConsumption = 10.0); 

    Vehicle ( const Vehicle &other );

    virtual ~Vehicle ();                            

    Vehicle& operator = ( const Vehicle &other );

    virtual void printSpecification() const;
    virtual double computeTravelDistance() const;

    const char * getMake (  ) const { return make_; }
    void setMake ( const char * value );

    const char * getType_ (  ) const { return type_; }
    void setType_ ( const char * value );

    const char * getLicensePlate_ (  ) const { return static_cast<const char*>(licensePlate_); }
    void setLicensePlate_ ( const char * value );

    double getFuelConsumption (  ) const { return fuelConsumption_; }
    void setFuelConsumption ( double value ) { fuelConsumption_	= value; }

    double getGasTankSize (  ) const { return gasTankSize_; }
    void setGasTankSize ( double value ) { gasTankSize_	= value; }

private:
    char licensePlate_[9];
    char *type_;
    char *make_;
    double gasTankSize_;
    double fuelConsumption_;

}; // -----  end of class Vehicle  -----

#endif     // -----  not ELLOOP_VEHICLE_H  -----

