#pragma once

#include "entity/Step.hpp"  
#include "entity/SensorData.hpp"  

#include "drivers/wifi.hpp"

using namespace entity;

namespace application {

    class ApiService {

        private:
            WifiDriver* wifi;

        public:
            ApiService();

            bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut);
            
            void testDownloadJson();
            void enviarDadosParaApi(SensorData* leituras, uint count);
            String gerarJson(SensorData* leituras, uint count);

            WifiDriver* getWifi();

    };

}



