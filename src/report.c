#include "report.h"
#include "lorawan.h"

#include <stdio.h>

static void _int_to_bytes(char *buffer, int32_t value,
                                       size_t byteSize)
{
    for (int i = 0; i < byteSize; i++) {
        buffer[i] = (int)(value >> (i * 8));
    }
}

report_send_result_t report_Send(container_state_t container,
                                 battery_state_t battery,
                                 gps_coordinates_t *gps)
{
    char payload[REPORT_SIZE_MAX_PAYLOAD];
    size_t size = 0;
    int32_t lat, lng;

    payload[REPORT_IDX_CONTAINER] = (char)container;
    size += REPORT_SIZE_CONTAINER;

    payload[REPORT_IDX_BATTERY] = (char)battery;
    size += REPORT_SIZE_BATTERY;

    if (gps->fixed) {
        lat = gps->lat * 1e6;
        lng = gps->lng * 1e6;

        _int_to_bytes(&(payload[REPORT_IDX_GPS_LAT]), lat, REPORT_SIZE_LAT);
        size += REPORT_SIZE_LAT;

        _int_to_bytes(&(payload[REPORT_IDX_GPS_LNG]), lng, REPORT_SIZE_LNG);
        size += REPORT_SIZE_LNG;
    }

    printf("container: %d", payload[0]);

    return lorawan_Send(payload, size) == LORAWAN_SEND_SUCCESS ? 
                REPORT_SEND_SUCCESS : REPORT_SEND_ERR_LORA;
}