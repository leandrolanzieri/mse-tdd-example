#include "unity.h"
#include "Mocklorawan.h"
#include "report.h"

#define TEST_CONTAINER_EMPTY    0
#define TEST_CONTAINER_FULL     100
#define TEST_CONTAINER_WRONG    101
#define TEST_CONTAINER_HALF     50

#define TEST_BATTERY_EMPTY      0
#define TEST_BATTERY_FULL       100
#define TEST_BATTERY_WRONG      101
#define TEST_BATTERY_HALF       50

#define TEST_GPS_NO_FIX         false
#define TEST_GPS_FIX            true

#define TEST_GPS_LAT            53.556511
#define TEST_GPS_LNG            10.023502

/******************************************************************************/
/* Stubs                                                                      */
/******************************************************************************/
lorawan_send_result_t lorawan_Send_Stub_ShouldContainerEmptyBatteryFullNoGPS(
                            char *msg, size_t msgSize, 
                            int numCalls)
{
    /* As there is no GPS msgSize should be 2:
        - container
        - battery
    */
    TEST_ASSERT_EQUAL(2, msgSize);
    TEST_ASSERT_EQUAL(TEST_CONTAINER_EMPTY, msg[REPORT_IDX_CONTAINER]);
    TEST_ASSERT_EQUAL(TEST_BATTERY_FULL, msg[REPORT_IDX_BATTERY]);
    return LORAWAN_SEND_SUCCESS;
}

lorawan_send_result_t lorawan_Send_Stub_ShouldContainerAndBatteryHalfAndGPS(
                            char *msg, size_t msgSize, 
                            int numCalls)
{
    uint32_t lat = 0, lng = 0;

    puts("Payload:");
    for (int i = 0; i < msgSize; i++) {
        printf("%d: %02x\n", i, (char)msg[i]&0xff);
    }

    /* As there is a GPS msgSize should be MAX */
    TEST_ASSERT_EQUAL(REPORT_SIZE_MAX_PAYLOAD, msgSize);
    TEST_ASSERT_EQUAL(TEST_CONTAINER_HALF, msg[REPORT_IDX_CONTAINER]);
    TEST_ASSERT_EQUAL(TEST_BATTERY_HALF, msg[REPORT_IDX_BATTERY]);

    /* Reconstruct Latitude and Longitude */
    for (int i = 0; i < REPORT_SIZE_LAT; i++) {
        lat |= (msg[REPORT_IDX_GPS_LAT + i] & 0xFF) << (i * 8);
    }

    for (int i = 0; i < REPORT_SIZE_LNG; i++) {
        lng += ((msg[REPORT_IDX_GPS_LNG + i] & 0xFF) << (i * 8));
    }

    /* Assert values within a delta because of possible rounding issues */
    TEST_ASSERT_INT32_WITHIN(2, (TEST_GPS_LAT * 1e6), lat);
    TEST_ASSERT_INT32_WITHIN(2, (TEST_GPS_LNG * 1e6), lng);

    return LORAWAN_SEND_SUCCESS;
}

/******************************************************************************/
/* Tests                                                                      */
/******************************************************************************/
void testSendShouldSendValuesAndNotGPS(void)
{
    container_state_t container = TEST_CONTAINER_EMPTY;
    battery_state_t battery = TEST_BATTERY_FULL;
    gps_coordinates_t gps = {
        .fixed = TEST_GPS_NO_FIX
    };
    report_send_result_t res;

    /* Mock lorawan_Send function to check the values in the buffer */
    lorawan_Send_ExpectAnyArgsAndReturn(LORAWAN_SEND_SUCCESS);
    lorawan_Send_StubWithCallback(
        lorawan_Send_Stub_ShouldContainerEmptyBatteryFullNoGPS
    );

    res = report_Send(container, battery, &gps);
    TEST_ASSERT_EQUAL(REPORT_SEND_SUCCESS, res);
}

void testSendShouldNotSendWrongContainer(void)
{
    container_state_t container = TEST_CONTAINER_WRONG;
    battery_state_t battery = TEST_BATTERY_FULL;
    gps_coordinates_t gps = {
        .lat = TEST_GPS_LAT,
        .lng = TEST_GPS_LNG,
        .fixed = TEST_GPS_FIX
    };
    report_send_result_t res;

    /* Note that lorawan_Send is expected to be called 0 times */

    res = report_Send(container, battery, &gps);
    TEST_ASSERT_EQUAL(REPORT_SEND_ERR_BAD_VALUE, res);
}

void testSendShouldNotSendWrongBattery(void)
{
    container_state_t container = TEST_CONTAINER_FULL;
    battery_state_t battery = TEST_BATTERY_WRONG;
    gps_coordinates_t gps = {
        .lat = TEST_GPS_LAT,
        .lng = TEST_GPS_LNG,
        .fixed = TEST_GPS_FIX
    };
    report_send_result_t res;

    /* Note that lorawan_Send is expected to be called 0 times */

    res = report_Send(container, battery, &gps);
    TEST_ASSERT_EQUAL(REPORT_SEND_ERR_BAD_VALUE, res);
}

void testSendShouldSendCorrectValuesAndGPS(void)
{
    container_state_t container = TEST_CONTAINER_HALF;
    battery_state_t battery = TEST_BATTERY_HALF;
    gps_coordinates_t gps = {
        .lat = TEST_GPS_LAT,
        .lng = TEST_GPS_LNG,
        .fixed = TEST_GPS_FIX
    };
    report_send_result_t res;

    /* Mock lorawan_Send function to check the values in the buffer */
    lorawan_Send_ExpectAnyArgsAndReturn(LORAWAN_SEND_SUCCESS);
    lorawan_Send_StubWithCallback(
        lorawan_Send_Stub_ShouldContainerAndBatteryHalfAndGPS
    );

    res = report_Send(container, battery, &gps);
    TEST_ASSERT_EQUAL(REPORT_SEND_SUCCESS, res);
}
