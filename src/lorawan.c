#include "lorawan.h"
#include "rn2903Lorawan.h"

lorawan_join_result_t lorawan_Join(lorawan_keys_t keys,
                                   lorawan_join_mode_t mode)
{
    if (!rn2903Lorawan_SetAppKey(keys.appkey)) {
        return LORAWAN_JOIN_ERR_INVALID_KEYS;
    }

    if (!rn2903Lorawan_SetAppEui(keys.appeui)) {
        return LORAWAN_JOIN_ERR_INVALID_KEYS;
    }

    if (!rn2903Lorawan_SetDevEui(keys.deveui)) {
        return LORAWAN_JOIN_ERR_INVALID_KEYS;
    }

    return rn2903Lorawan_Join(mode) ?
            LORAWAN_JOIN_SUCCESS : LORAWAN_JOIN_ERR_TIMEOUT;
}

lorawan_send_result_t lorawan_Send(char *msg, size_t msgSize)
{
    if (!rn2903Lorawan_IsJoined()) {
        return LORAWAN_SEND_ERR_NOT_JOINED;
    }

    if (rn2903Lorawan_IsBusy()) {
        return LORAWAN_SEND_ERR_BUSY;
    }
}
