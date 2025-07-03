#include "application/SystemStatus.hpp"
#include <algorithm>

namespace application {


    SystemStatus::SystemStatus()
        : currentSector("Base"),
        currentActivity(Activity::IDLE),
        batteryLevel(100.0f),
        connectionLevel(0) {}

    void SystemStatus::setCurrentSector(const std::string& sector) {
        currentSector = sector;
    }

    std::string SystemStatus::getCurrentSector() const {
        return currentSector;
    }

    void SystemStatus::setActivity(Activity activity) {
        currentActivity = activity;
    }

    Activity SystemStatus::getActivity() const {
        return currentActivity;
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

    void SystemStatus::setBatteryLevel(float level) {
        batteryLevel = level;
    }

    float SystemStatus::getBatteryLevel() const {
        return batteryLevel;
    }

    void SystemStatus::setConnectionLevel(int level) {

        if (level < 0) level = 0;
        else if (level > 4) level = 4;
        connectionLevel = level;

    }

    int SystemStatus::getConnectionLevel() const {
        return connectionLevel;
    }

    //Implementar essa função depois
    void SystemStatus::measureAndUpdateBatteryLevel(int adcPin){
        return;
    }

    //Implementar depois
    void SystemStatus::updateConnectionFromWiFi(){
        return;
    }

}