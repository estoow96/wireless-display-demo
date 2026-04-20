#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "wifi_direct.h"

#define WIFI_INTERFACE "wlan0"

typedef struct {
    int initialized;
    char status[256];
} WifiDirectContext;

static WifiDirectContext g_wifi_direct = {0};

int wifi_direct_init(void) {
    printf("[WiFi-Direct] Initializing Wi-Fi Direct...\n");
    
    if (g_wifi_direct.initialized) {
        printf("[WiFi-Direct] Already initialized\n");
        return 0;
    }
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ip link show %s", WIFI_INTERFACE);
    
    int ret = system(cmd);
    if (ret != 0) {
        fprintf(stderr, "[WiFi-Direct] WiFi interface %s not found\n", WIFI_INTERFACE);
        return -1;
    }
    
    printf("[WiFi-Direct] WiFi interface %s is available\n", WIFI_INTERFACE);
    
    snprintf(cmd, sizeof(cmd), "wpa_cli -i %s p2p_find type=progressive", WIFI_INTERFACE);
    ret = system(cmd);
    
    if (ret == 0) {
        printf("[WiFi-Direct] P2P discovery started\n");
        g_wifi_direct.initialized = 1;
        strcpy(g_wifi_direct.status, "initialized");
        return 0;
    }
    
    printf("[WiFi-Direct] Warning: wpa_cli p2p_find may not be available\n");
    
    g_wifi_direct.initialized = 1;
    strcpy(g_wifi_direct.status, "initialized_with_warning");
    return 0;
}

int wifi_direct_start_go(const char *ssid, const char *passphrase) {
    printf("[WiFi-Direct] Starting as Group Owner with SSID: %s\n", ssid);
    
    if (!g_wifi_direct.initialized) {
        fprintf(stderr, "[WiFi-Direct] Not initialized. Call wifi_direct_init() first\n");
        return -1;
    }
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "wpa_cli -i %s p2p_group_add persistent=0", WIFI_INTERFACE);
    
    int ret = system(cmd);
    if (ret != 0) {
        fprintf(stderr, "[WiFi-Direct] Failed to create P2P group\n");
        return -1;
    }
    
    printf("[WiFi-Direct] P2P group created successfully\n");
    strcpy(g_wifi_direct.status, "group_owner_active");
    
    return 0;
}

int wifi_direct_stop_go(void) {
    printf("[WiFi-Direct] Stopping Group Owner mode...\n");
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "wpa_cli -i %s p2p_group_remove %s", WIFI_INTERFACE, WIFI_INTERFACE);
    
    int ret = system(cmd);
    if (ret != 0) {
        printf("[WiFi-Direct] Group removal may have failed or already removed\n");
        return 0;
    }
    
    strcpy(g_wifi_direct.status, "go_stopped");
    return 0;
}

int wifi_direct_discover(void) {
    printf("[WiFi-Direct] Starting P2P discovery...\n");
    
    if (!g_wifi_direct.initialized) {
        fprintf(stderr, "[WiFi-Direct] Not initialized\n");
        return -1;
    }
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "wpa_cli -i %s p2p_find", WIFI_INTERFACE);
    
    int ret = system(cmd);
    if (ret == 0) {
        printf("[WiFi-Direct] P2P discovery started\n");
        strcpy(g_wifi_direct.status, "discovering");
        return 0;
    }
    
    return -1;
}

const char* wifi_direct_get_status(void) {
    return g_wifi_direct.status;
}

void wifi_direct_cleanup(void) {
    printf("[WiFi-Direct] Cleaning up Wi-Fi Direct...\n");
    
    if (g_wifi_direct.initialized) {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "wpa_cli -i %s p2p_stop_find", WIFI_INTERFACE);
        system(cmd);
        
        g_wifi_direct.initialized = 0;
        strcpy(g_wifi_direct.status, "cleanup");
        
        printf("[WiFi-Direct] Cleanup complete\n");
    }
}