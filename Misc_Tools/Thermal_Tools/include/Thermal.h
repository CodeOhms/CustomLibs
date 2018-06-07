#ifndef  THERMAL_H
#define  THERMAL_H

#include <math.h>
#include <fstream>
#include <functional>

namespace Thermal
{
    class ThermalStatsBase
    {
        public:
            virtual bool readRaw( float& temp, int sensorPin )   =0;
            virtual bool read( int& temp,      int sensorPin=-1 )=0;
            virtual bool read( float& temp,    int sensorPin=-1 )=0;

    };

    bool readRawBuiltIn( float& temp );
    class ThermalStats : public ThermalStatsBase
    {
        private:
            std::function<bool(float&,int)> userTempSensor = nullptr;

            virtual bool readRaw( float& temp, int sensorPin );

        public:
            ThermalStats() { }
            ThermalStats(const std::function<bool(float&,int)>& sensorFunc) : \
              userTempSensor(sensorFunc) { }


            bool setCustTempSensor(const std::function<bool(float&,int)>& \
              userTempSensor);

            virtual bool  read( int& temp,   int sensorPin=-1 );
            virtual bool  read( float& temp, int sensorPin=-1 );

    };

}

#endif //THERMAL_H

