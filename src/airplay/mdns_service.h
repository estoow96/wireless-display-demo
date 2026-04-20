# mDNS Service Header

#ifndef MDNS_SERVICE_H
#define MDNS_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Function prototypes for mDNS service discovery

/**
 * @brief Initialize mDNS service.
 */
void mdns_service_init(void);

/**
 * @brief Start mDNS service.
 *
 * @return 0 on success, otherwise error code.
 */
int mdns_service_start(void);

/**
 * @brief Stop mDNS service.
 */
void mdns_service_stop(void);

/**
 * @brief Publish a service to the mDNS network.
 *
 * @param service_name The name of the service to publish.
 * @param port The port on which the service is running.
 * @return 0 on success, otherwise error code.
 */
int mdns_service_publish(const char* service_name, uint16_t port);

/**
 * @brief Unpublish a service from the mDNS network.
 *
 * @param service_name The name of the service to unpublish.
 * @return 0 on success, otherwise error code.
 */
int mdns_service_unpublish(const char* service_name);

#ifdef __cplusplus
}
#endif

#endif // MDNS_SERVICE_H
