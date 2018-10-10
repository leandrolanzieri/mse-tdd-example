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

void testJoinShouldSuccessUpponValidKeysAndNoTimeout(void)
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
    rn2903Lorawan_Join_ExpectAndReturn(mode, true);

    res = lorawan_Join(keys, mode);
    TEST_ASSERT_EQUAL(LORAWAN_JOIN_SUCCESS, res);
}

void testSendShouldFailWhenNotJoined(void)
{
    lorawan_send_result_t res;
    char msg[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t msgSize = 4;

    rn2903Lorawan_IsJoined_ExpectAndReturn(false);

    res = lorawan_Send(msg, msgSize);
    TEST_ASSERT_EQUAL(LORAWAN_SEND_ERR_NOT_JOINED, res);
}

void testSendShouldFailWhenDeviceBusy(void)
{
    lorawan_send_result_t res;
    char msg[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t msgSize = 4;

    rn2903Lorawan_IsJoined_ExpectAndReturn(true);
    rn2903Lorawan_IsBusy_ExpectAndReturn(true);

    res = lorawan_Send(msg, msgSize);
    TEST_ASSERT_EQUAL(LORAWAN_SEND_ERR_BUSY, res);
}

void testSendShouldFailWhenDeviceFailsToSend(void)
{
    lorawan_send_result_t res;
    char msg[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t msgSize = 4;

    rn2903Lorawan_IsJoined_ExpectAndReturn(true);
    rn2903Lorawan_IsBusy_ExpectAndReturn(false);
    rn2903Lorawan_Send_ExpectAndReturn(msg, msgSize, false);

    res = lorawan_Send(msg, msgSize);
    TEST_ASSERT_EQUAL(LORAWAN_SEND_ERR_DEVICE_FAILED, res);
}

void testSendShouldSuccessWhenDeviceFreeAndJoined(void)
{
    lorawan_send_result_t res;
    char msg[] = { 0x12, 0x34, 0x56, 0x78 };
    size_t msgSize = 4;

    rn2903Lorawan_IsJoined_ExpectAndReturn(true);
    rn2903Lorawan_IsBusy_ExpectAndReturn(false);
    rn2903Lorawan_Send_ExpectAndReturn(msg, msgSize, true);

    res = lorawan_Send(msg, msgSize);
    TEST_ASSERT_EQUAL(LORAWAN_SEND_SUCCESS, res);
}
