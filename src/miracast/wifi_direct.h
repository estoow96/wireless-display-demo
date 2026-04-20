#ifndef WIFI_DIRECT_H
#define WIFI_DIRECT_H

#ifdef __cplusplus
extern "C" {
#endif

int wifi_direct_init(void);
int wifi_direct_start_go(const char *ssid, const char *passphrase);
int wifi_direct_stop_go(void);
int wifi_direct_discover(void);
const char* wifi_direct_get_status(void);
void wifi_direct_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // WIFI_DIRECT_H