#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

void printPVTdata(UBX_NAV_PVT_data_t ubxDataStruct)
{
    // Serial.println("UBLOX DATA RETRIEVED");

    // Serial.print(F("Time : ")); // Print the time
    // uint8_t hms = ubxDataStruct.hour; // Print the hours
    // if (hms < 10) Serial.print(F("0")); // Print a leading zero if required
    // Serial.print(hms);
    // Serial.print(F(":"));
    // hms = ubxDataStruct.min; // Print the minutes
    // if (hms < 10) Serial.print(F("0")); // Print a leading zero if required
    // Serial.print(hms);
    // Serial.print(F(":"));
    // hms = ubxDataStruct.sec; // Print the seconds
    // if (hms < 10) Serial.print(F("0")); // Print a leading zero if required
    // Serial.print(hms);
    // Serial.print(F("."));
    // unsigned long millisecs = ubxDataStruct.iTOW % 1000; // Print the milliseconds
    // if (millisecs < 100) Serial.print(F("0")); // Print the trailing zeros correctly
    // if (millisecs < 10) Serial.print(F("0"));
    // Serial.println(millisecs);

    long latitude = ubxDataStruct.lat; // Print the latitude
    Serial.print(F("Latitude : "));
    Serial.println(latitude);

    long longitude = ubxDataStruct.lon; // Print the longitude
    Serial.print(F("Longitude : "));
    Serial.println(longitude);
    // Serial.println(F(" (degrees * 10^-7)"));

    long altitude = ubxDataStruct.hMSL; // Print the height above mean sea level
    Serial.print(F("HeightAboveMSL : "));
    Serial.println(altitude);
    // Serial.println(F(" (mm)"));
    // Serial.println();
}