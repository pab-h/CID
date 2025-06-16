#pragma once

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "entity/Step.hpp"  

#include <ArduinoJson.h>

using namespace entity;

    bool deserializeSteps(const char* jsonBuffer, Step*& stepsOut, uint& countOut);
    void testDownloadJson();

#endif
