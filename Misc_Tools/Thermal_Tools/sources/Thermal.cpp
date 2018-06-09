#include "Thermal.h"

namespace Thermal
{
    bool readRawBuiltIn(float& temp)
    {
        std::ifstream thermalData("/sys/class/thermal/thermal_zone0/temp");

        if( thermalData.is_open() )
            thermalData >> temp;
        else
            return false;

        thermalData.close();
        return true;
    }


    bool ThermalStats::setCustTempSensor(const std::function<bool(float&,int)>& \
      userTempSensor)
    {
        try
        {
            this->userTempSensor = userTempSensor;
        } catch(...) {
            return false;
        }

        return true;
    }

    bool ThermalStats::readRaw( float& temp, int sensorPin )
    {
        if(sensorPin == -1)
        {
            if( !readRawBuiltIn(temp) )
                return false;
        }
        else
        {
            if( !userTempSensor(temp, sensorPin) )
                return false;
        }

        return true;
    }

    bool  ThermalStats::read( int& temp, int sensorPin )
    {
        float temperature;
        if( !readRaw(temperature, sensorPin) )
            return false;

        temp = (temperature /1000) +0.5;
        return true;
    }

    bool  ThermalStats::read( float& temp, int sensorPin )
    {
        if( !readRaw(temp, sensorPin) )
            return false;

        temp = round( (temp /1000) *100 ) /100;
        return true;
    }
}
