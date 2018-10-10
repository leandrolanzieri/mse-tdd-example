#ifndef LORAWAN_H_
#define LORAWAN_H_

#include <stdlib.h>

typedef struct {
    char *appkey;  /*< Application Key */
    char *appeui;  /*< Application EUI */
    char *deveui;  /*< Device EUI */
    char *devaddr; /*< Device Address */
    char *appskey; /*< Application Session Key */
    char *nwkskey; /*< Network Session Key */
} lorawan_keys_t;

typedef enum {
    LORAWAN_JOIN_ERR_INVALID_KEYS,
    LORAWAN_JOIN_ERR_TIMEOUT,
    LORAWAN_JOIN_ERR_ALREADY_JOINED,
    LORAWAN_JOIN_SUCCESS,
} lorawan_join_result_t;

typedef enum {
    LORAWAN_JOIN_OTAA,
    LORAWAN_JOIN_ABP
} lorawan_join_mode_t;

typedef enum {
    LORAWAN_SEND_ERR_NOT_JOINED,
    LORAWAN_SEND_ERR_BUSY,
    LORAWAN_SEND_SUCCESS
} lorawan_send_result_t;

/**
 * @brief Attempts to join the LoRaWAN network
 * 
 * @param[in] keys Necessary keys to join according to the mode
 * @param[in] mode Mode to join the network
 * @return lorawan_join_result_t 
 */
lorawan_join_result_t lorawan_Join(lorawan_keys_t keys,
                                   lorawan_join_mode_t mode);

/**
 * @brief Attempts to send a message
 * 
 * @param[in] msg Buffer with the message
 * @param[in] msgSize Size of the buffer
 * @return lorawan_send_result_t 
 */
lorawan_send_result_t lorawan_Send(char* msg, size_t msgSize);

#endif
