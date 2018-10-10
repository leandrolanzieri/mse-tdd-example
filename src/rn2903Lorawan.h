#ifndef RN2903_LORAWAN_H_
#define RN2903_LORAWAN_H_

#include <stdbool.h>
#include "lorawan.h"

/**
 * @brief Sets the Application Key
 * 
 * @param[in] appkey String containing hex Application Key
 * @return true The key is valid
 * @return false The key is not valid
 */
bool rn2903Lorawan_SetAppKey(char *appkey);

/**
 * @brief Sets the Application EUI
 * 
 * @param[in] appeui String containing hex Application EUI
 * @return true The key is valid
 * @return false The key is not valid
 */
bool rn2903Lorawan_SetAppEui(char *appeui);

/**
 * @brief Sets the Device EUI
 * 
 * @param[in] deveui String containing hex Device EUI
 * @return true The key is valid
 * @return false The key is not valid
 */
bool rn2903Lorawan_SetDevEui(char *deveui);

/**
 * @brief Attempts to join the LoRaWAN network
 * 
 * @param[in] mode Mode to join the network
 * @return true Join successful
 * @return false Error joining
 */
bool rn2903Lorawan_Join(lorawan_join_mode_t mode);

/**
 * @brief Checks if the device has joined the network
 * 
 * @return true Device joined
 * @return false Device not joined
 */
bool rn2903Lorawan_IsJoined(void);

/**
 * @brief Checks if the device is busy
 * 
 * @return true Device busy
 * @return false Device not busy
 */
bool rn2903Lorawan_IsBusy(void);

#endif
