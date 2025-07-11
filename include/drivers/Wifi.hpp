#pragma once

#include <WiFi.h>

namespace drivers{

  /**
   * @brief Driver class responsible for managing Wi-Fi connection.
   * 
   * Handles connection, disconnection, reconnection, and status checks
   * to a Wi-Fi network using given SSID and password.
   */
  class WifiDriver {

    private:
      String ssid;       /**< Wi-Fi network SSID */
      String password;   /**< Wi-Fi network password */

    public:

      /**
       * @brief Constructs the WifiDriver with network credentials.
       * 
       * @param ssid Wi-Fi network name.
       * @param password Wi-Fi network password.
       */
      WifiDriver(const String& ssid, const String& password); 

      /**
       * @brief Gets the stored SSID.
       * 
       * @return String containing the SSID.
       */
      String getSSID();

      /**
       * @brief Gets the stored password.
       * 
       * @return String containing the password.
       */
      String getPassword();

      /**
       * @brief Initiates connection to the configured Wi-Fi network.
       * 
       * @return true if connected successfully, false otherwise.
       */
      bool connect();

      /**
       * @brief Disconnects from the current Wi-Fi network.
       */
      void disconnect();

      /**
       * @brief Attempts to reconnect to the Wi-Fi network.
       * 
       * @return true if reconnection is successful, false otherwise.
       */
      bool reconnect();

      /**
       * @brief Checks if currently connected to Wi-Fi.
       * 
       * @return true if connected, false otherwise.
       */
      bool isConnected();

      /**
       * @brief Gets the current Wi-Fi signal strength (RSSI).
       * 
       * @return RSSI value in dBm (negative integer).
       */
      int getRSSI() const;

  };

}