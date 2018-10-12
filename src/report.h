#ifndef REPORT_H_
#define REPORT_H_

#include <stdint.h>
#include <stdbool.h>

#define REPORT_SIZE_LAT         (4)
#define REPORT_SIZE_LNG         (4)
#define REPORT_SIZE_GPS         (REPORT_SIZE_LAT + REPORT_SIZE_LNG)
#define REPORT_SIZE_CONTAINER   (1)
#define REPORT_SIZE_BATTERY     (1)
#define REPORT_SIZE_MAX_PAYLOAD     REPORT_SIZE_CONTAINER + \
                                    REPORT_SIZE_BATTERY +   \
                                    REPORT_SIZE_GPS

#define REPORT_IDX_CONTAINER    (0)
#define REPORT_IDX_BATTERY      (1)
#define REPORT_IDX_GPS_LAT      (2)
#define REPORT_IDX_GPS_LNG      (6)
#define REPORT_IDX_GPS_NO_FIX   (2)

#define REPORT_MAX_CONTAINER    (100)
#define REPORT_MAX_BATTERY      (100)

typedef uint8_t container_state_t;

typedef uint8_t battery_state_t;

typedef struct {
    float lat;
    float lng;
    bool fixed;
} gps_coordinates_t;

typedef enum {
    REPORT_SEND_SUCCESS,
    REPORT_SEND_ERR_BAD_VALUE,
    REPORT_SEND_ERR_LORA
} report_send_result_t;

/**
 * @brief Sends a report via LoRa.
 * 
 * @param[in] container State of the container
 * @param[in] battery State of the battery
 * @param[in] gps GPS data
 * @return report_send_result_t 
 */
report_send_result_t report_Send(container_state_t container,
                                 battery_state_t battery,
                                 gps_coordinates_t *gps);

#endif
