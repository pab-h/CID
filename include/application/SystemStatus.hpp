#pragma once

#include <string>
#include "drivers/Wifi.hpp"

namespace application {
    
    /**
     * @brief Enumeration of possible activities the CID system can be performing.
     */
    enum class Activity {
        IDLE,        ///< Idle or waiting
        MOVING,      ///< Moving to a location
        SENSING,     ///< Performing sensing operations
        CONNECTING,  ///< Attempting to connect to the network
        ERROR        ///< An error has occurred
    };

    /**
     * @brief Snapshot structure representing the current system status.
     */
    struct StatusData {

        uint8_t batteryLevel;        ///< Battery level percentage (0–100%)
        uint8_t connectionLevel;     ///< Wi-Fi signal level (0–4)
        Activity currentActivity;    ///< Current activity being performed
        char currentSector[18];      ///< Current or target sector name

        /**
         * @brief Converts the current activity into a readable string.
         * @return std::string The current activity as a string.
         */
        std::string activityToString() const;

    };

    /**
     * @brief Represents the current status of the CID system.
     * 
     * Stores information about the current or target sector, 
     * current activity, battery level, and connection quality.
     */
    class SystemStatus {

        public:
        
            /**
             * @brief Default constructor. Initializes the system status with safe default values.
             */
            SystemStatus();
            
            /* > Getters and setters < */

            /**
             * @brief Gets the current connection quality level.
             * 
             * @return int The connection quality level.
             */
            uint8_t getConnectionLevel() const;

            /**
             * @brief Sets the current connection quality level.
             * 
             * The level must be between 0 and 4, where:
             * - 0 = No connection
             * - 1 = Very weak signal
             * - 2 = Weak signal
             * - 3 = Good signal
             * - 4 = Excellent signal
             * 
             * Values outside this range will be replaced by the closest value within the range.
             * 
             * @param level Connection quality level (0 to 4).
             */
            void setConnectionLevel(uint8_t level);

            /**
             * @brief Gets the current battery level percentage.
             * 
             * @return float The battery level (0.0 to 100.0).
             */
            uint8_t getBatteryLevel() const;
            
            /**
             * @brief Sets the current battery level percentage.
             * 
             * @param level The battery level (0.0 to 100.0).
             */
            void setBatteryLevel(uint8_t level);

            /**
             * @brief Gets the current activity of the CID.
             * 
             * @return Activity The current activity.
             */
            Activity getActivity() const;

            /**
             * @brief Sets the current activity of the CID.
             * 
             * @param activity The current activity from the Activity enum.
             */
            void setActivity(Activity activity);

            /**
             * @brief Gets the current or target sector name.
             * 
             * @return std::string The name of the sector.
             */
            std::string getCurrentSector() const;
            
            /**
             * @brief Sets the current or target sector name where the CID is located or heading.
             * 
             * @param sector The name of the sector (e.g., "Sector A1", "Heading to Sector B3").
             */
            void setCurrentSector(const char* sector);

            /* > Class general functions < */

            /**
             * @brief Reads the ADC pin and updates the battery level percentage.
             * 
             * Requires an external voltage divider to safely measure battery voltage.
             * Assumes 1-cell Li-Ion battery (3.0V–4.2V) and 12-bit ADC resolution.
             * 
             * @param adcPin GPIO number connected to the battery divider (e.g., GPIO 34).
             */
            void measureAndUpdateBatteryLevel(uint8_t bateryPin);

            /**
             * @brief Converts the current activity to a human-readable string.
             * 
             * @return std::string The textual representation of the activity.
             */
            std::string activityToString() const;

            /**
             * @brief Returns a snapshot of the current system status.
             * 
             * This method collects and returns the current system information
             * as a StatusData struct, which is useful for transmission or logging.
             * 
             * @return StatusData A copy of the current system state.
             */
            StatusData getStatusData() const;

        private:
            
            /**
             * @brief Connection quality level.
             * 
             * Integer scale from 0 to 4:
             * - 0: No signal
             * - 1: Very weak
             * - 2: Weak
             * - 3: Good
             * - 4: Excellent
             */
            uint8_t connectionLevel;

            /**
             * @brief Current battery level as a percentage.
             * 
             * Value ranges from 0 to 100.
             */
            uint8_t batteryLevel;
            
            /**
             * @brief Current activity being executed by the system.
             * 
             * Represented using the Activity enum (e.g., MOVING, SENSING).
             */
            Activity currentActivity;

            /**
             * @brief Name of the current or target sector.
             * 
             * Example: "Sector A1", "Heading to Sector B2".
             */
            char currentSector[18];

    };

}
