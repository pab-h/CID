#pragma once

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "entity/Step.hpp"  
#include "entity/SensorData.hpp"  


#include <ArduinoJson.h>

using namespace entity;

    bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut);
    void testDownloadJson();
    void enviarDadosParaApi(SensorData* leituras, uint count);
    String gerarJson(SensorData* leituras, uint count);

#endif
