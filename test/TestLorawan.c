#include "unity.h"
#include "lorawan.h"

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
    res = lorawan_Join(keys, LORAWAN_JOIN_OTAA);
    TEST_ASSERT_EQUAL(LORAWAN_JOIN_ERR_INVALID_KEYS, res);
}
