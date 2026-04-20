#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mdns.h>  // Include specific mDNS library header

// mDNS service structure
typedef struct {
    const char *service_name;
    const char *service_type;
    const char *protocol;
    uint16_t port;
    mdns_service_t *mdns_service;
} mdns_service_t;

// Initialize mDNS
void mdns_init() {
    mdns_start(); // Initialize mDNS subsystem
}

// Start mDNS service
void mdns_start_service(mdns_service_t *mdns_service) {
    mdns_service->mdns_service = mdns_service_create(mdns_service->service_name, mdns_service->service_type, mdns_service->protocol, mdns_service->port);
    if (!mdns_service->mdns_service) {
        fprintf(stderr, "Failed to create mDNS service\n");
        return;
    }
    mdns_service_publish(mdns_service->mdns_service);  // Publish the service
}

// Stop mDNS service
void mdns_stop_service(mdns_service_t *mdns_service) {
    if (mdns_service && mdns_service->mdns_service) {
        mdns_service_unpublish(mdns_service->mdns_service);
        mdns_service_destroy(mdns_service->mdns_service);
    }
}

// Publish the mDNS service
void mdns_publish_service(mdns_service_t *mdns_service) {
    mdns_service_publish(mdns_service->mdns_service);
}

// Unpublish the mDNS service
void mdns_unpublish_service(mdns_service_t *mdns_service) {
    mdns_service_unpublish(mdns_service->mdns_service);
}

// Sample usage
int main() {
    mdns_service_t my_service = {"My Service", "_myservice._tcp", "tcp", 8080};
    mdns_init();
    mdns_start_service(&my_service);

    // Simulate running...
    printf("mDNS Service is running. Press Enter to stop...\n");
    getchar();

    mdns_stop_service(&my_service);
    return 0;
}