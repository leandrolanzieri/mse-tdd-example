#include "unity.h"
#include "lorawan.h"
#include "Mockrn2903Lorawan.h"
#include <stdbool.h>

void setUp(void)
{

}

void tearDown(void)
{

}

void testJoinShouldFailUpponInvalidKeys(void)
{
    char appkey[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char appeui[] = "BBBBBBBBBBBBBBBB";
    char deveui[] = "CCCCCCCCCCCCCCCC";
    lorawan_keys_t keys = {
        .appkey = appkey,
        .appeui = appeui,
        .deveui = deveui
    };
    lorawan_join_result_t res;
    lorawan_join_mode_t mode = LORAWAN_JOIN_OTAA;

    rn2903Lorawan_SetAppKey_ExpectAndReturn(appkey, true);
    rn2903Lorawan_SetAppEui_ExpectAndReturn(appeui, true);
    /* we suppose the DEVEUI is wrong */
    rn2903Lorawan_SetDevEui_ExpectAndReturn(deveui, false);

    res = lorawan_Join(keys, mode);
    TEST_ASSERT_EQUAL(LORAWAN_JOIN_ERR_INVALID_KEYS, res);
}

void testJoinShouldFailWhenTimeout(void)
{
    char appkey[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char appeui[] = "BBBBBBBBBBBBBBBB";
    char deveui[] = "CCCCCCCCCCCCCCCC";
    lorawan_keys_t keys = {
        .appkey = appkey,
        .appeui = appeui,
        .deveui = deveui
    };
    lorawan_join_result_t res;
    lorawan_join_mode_t mode = LORAWAN_JOIN_OTAA;

    rn2903Lorawan_SetAppKey_ExpectAndReturn(appkey, true);
    rn2903Lorawan_SetAppEui_ExpectAndReturn(appeui, true);
    rn2903Lorawan_SetDevEui_ExpectAndReturn(deveui, true);
    rn2903Lorawan_Join_ExpectAndReturn(mode, false);

    res = lorawan_Join(keys, mode);
    TEST_ASSERT_EQUAL(LORAWAN_JOIN_ERR_TIMEOUT, res);
}