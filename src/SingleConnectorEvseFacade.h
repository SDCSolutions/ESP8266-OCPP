// matth-x/ESP8266-OCPP
// Copyright Matthias Akstaller 2019 - 2020
// MIT License

#ifndef SINGLE_CONNECTOR_EVSE_FACADE
#define SINGLE_CONNECTOR_EVSE_FACADE

#include "OcppOperation.h"


void OCPP_initialize(String CS_hostname, uint16_t CS_port, String CS_url);

void OCPP_loop();

/*
 * Provide hardware-related information to the library
 * 
 * The library needs a way to obtain information from your charger that changes over time. The
 * library calls following callbacks regularily (if they were set) to refresh its internal
 * status.
 * 
 * Set the callbacks once in your setup() function.
 */

void setPowerActiveImportSampler(float power());

void setEnergyActiveImportSampler(float energy());

/*
 * React on calls by the library's internal functions
 * 
 * The library needs to set parameters on your charger on a regular basis. The library calls
 * following callbacks regularily (if they were set) to perform updates on your charger.
 * 
 * Set the callbacks once in your setup() function.
 */

void setOnChargingRateLimitChange(void chargingRateChanged(float limit));

/*
 * React on CS-initiated operations
 * 
 * You can define custom behaviour in your integration which is executed every time the library
 * receives a CS-initiated operation. The following functions set a callback function for the
 * respective event. The library executes the callbacks always after its internal routines.
 * 
 * Set the callbacks once in your setup() function.
 */

void setOnSetChargingProfileRequest(void listener(JsonObject payload));

void setOnRemoteStartTransactionSendConf(void listener(JsonObject payload));

void setOnRemoteStopTransactionSendConf(void listener(JsonObject payload));

void setOnResetSendConf(void listener(JsonObject payload));

/*
 * Perform CP-initiated operations
 * 
 * Use following functions to send OCPP messages. Each function will adapt the library's
 * internal state appropriatley (e.g. after a successful StartTransaction request the library
 * will store the transactionId and send a StatusNotification).
 * 
 * On receipt of the .conf() response the library calls the callback function
 * "OnReceiveConfListener onConf" and passes the OCPP payload to it. The following functions
 * are non-blocking. Your application code will immediately resume with the subsequent code
 * in any case.
 */

void authorize(String &idTag);
void authorize(String &idTag, OnReceiveConfListener onConf);

void bootNotification(String chargePointModel, String chargePointVendor);
void bootNotification(String chargePointModel, String chargePointVendor, OnReceiveConfListener onConf);

void startTransaction();
void startTransaction(OnReceiveConfListener onConf);

void stopTransaction();
void stopTransaction(OnReceiveConfListener onConf);

/*
 * Provide hardware-related information II
 * 
 * When the EVSE state changes, you must notify the library in order to make StatusNotification
 * work properly.
 * 
 * Call these functions in your integration.
 */

void startEvDrawsEnergy();

void stopEvDrawsEnergy();

#endif
