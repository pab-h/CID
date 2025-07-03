#pragma once

#include <string>

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

        /**
         * @brief Sets the current or target sector name where the CID is located or heading.
         * 
         * @param sector The name of the sector (e.g., "Sector A1", "Heading to Sector B3").
         */
        void setCurrentSector(const std::string& sector);

        /**
         * @brief Gets the current or target sector name.
         * 
         * @return std::string The name of the sector.
         */
        std::string getCurrentSector() const;

        /**
         * @brief Sets the current activity of the CID.
         * 
         * @param activity The current activity from the Activity enum.
         */
        void setActivity(Activity activity);

        /**
         * @brief Gets the current activity of the CID.
         * 
         * @return Activity The current activity.
         */
        Activity getActivity() const;

        /**
         * @brief Converts the current activity to a human-readable string.
         * 
         * @return std::string The textual representation of the activity.
         */
        std::string activityToString() const;

        /**
         * @brief Sets the current battery level percentage.
         * 
         * @param level The battery level (0.0 to 100.0).
         */
        void setBatteryLevel(float level);

        /**
         * @brief Gets the current battery level percentage.
         * 
         * @return float The battery level (0.0 to 100.0).
         */
        float getBatteryLevel() const;

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
        void setConnectionLevel(int level);

        /**
         * @brief Gets the current connection quality level.
         * 
         * @return int The connection quality level.
         */
        int getConnectionLevel() const;

        /**
         * @brief Reads the ADC pin and updates the battery level percentage.
         * 
         * Requires an external voltage divider to safely measure battery voltage.
         * Assumes 1-cell Li-Ion battery (3.0V–4.2V) and 12-bit ADC resolution.
         * 
         * @param adcPin GPIO number connected to the battery divider (e.g., GPIO 34).
         */
        void measureAndUpdateBatteryLevel(int adcPin);

        /**
         * @brief Reads the current Wi-Fi RSSI and updates the connection level (0–4).
         * 
         * RSSI is mapped into:
         * - ≥ -50 dBm → 4 (excellent)
         * - ≥ -60 dBm → 3 (good)
         * - ≥ -70 dBm → 2 (fair)
         * - ≥ -80 dBm → 1 (weak)
         * - < -80 dBm → 0 (very weak)
         */
        void updateConnectionFromWiFi();

    private:

            /**
         * @brief Name of the current or target sector.
         * 
         * Example: "Sector A1", "Heading to Sector B2".
         */
        std::string currentSector;

        /**
         * @brief Current activity being executed by the system.
         * 
         * Represented using the Activity enum (e.g., MOVING, SENSING).
         */
        Activity currentActivity;

        /**
         * @brief Current battery level as a percentage.
         * 
         * Value ranges from 0.0 to 100.0.
         */
        float batteryLevel;

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
        int connectionLevel;

    };

}
