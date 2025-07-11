#include "application/SystemStatus.hpp"
#include <algorithm>


namespace application {

    SystemStatus::SystemStatus()
        : currentSector("Base"),
        currentActivity(Activity::IDLE),
        batteryLevel(100),
        connectionLevel(0) {}
    
    /* Conection getters and setters*/

    uint8_t SystemStatus::getConnectionLevel() const {
        return connectionLevel;
    }

    void SystemStatus::setConnectionLevel(uint8_t level) {

        if (level < 0) level = 0;
        else if (level > 4) level = 4;

        connectionLevel = level;

    }

    /* Batery getters and setters */

    uint8_t SystemStatus::getBatteryLevel() const {
        return batteryLevel;
    }
    
    void SystemStatus::setBatteryLevel(uint8_t level) {
        batteryLevel = level;
    }

    /* Activity getters and setters */

    void SystemStatus::setActivity(Activity activity) {
        currentActivity = activity;
    }

    Activity SystemStatus::getActivity() const {
        return currentActivity;
    }

    /* Location getters and setters*/

    void SystemStatus::setCurrentSector(const std::string& sector) {
        currentSector = sector;
    }

    std::string SystemStatus::getCurrentSector() const {
        return currentSector;
    }

    /* General functions */
    
    //Implementar essa função depois
    void SystemStatus::measureAndUpdateBatteryLevel(uint8_t adcPin){
        return;
    }
    
    std::string SystemStatus::activityToString() const {

        switch (currentActivity) {

            case Activity::IDLE:        return "Idle";
            case Activity::MOVING:      return "Moving";
            case Activity::SENSING:     return "Sensing";
            case Activity::CONNECTING:  return "Connecting";
            case Activity::ERROR:       return "Error";
            default:                    return "Unknown";

        }

    }

    StatusData SystemStatus::getStatusData() const {

        StatusData data;

        data.batteryLevel = batteryLevel;
        data.connectionLevel = connectionLevel;
        data.currentActivity = currentActivity;
        data.currentSector = currentSector;

        return data;

    }

}