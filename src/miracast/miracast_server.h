#ifndef MIRACAST_SERVER_H
#define MIRACAST_SERVER_H

// Function prototypes for Miracast server

/**
 * Initializes the Miracast server.
 * @return 0 on success, non-zero on failure.
 */
int init_miracast_server();

/**
 * Starts the Miracast server.
 * @return 0 on success, non-zero on failure.
 */
int start_miracast_server();

/**
 * Stops the Miracast server.
 * @return 0 on success, non-zero on failure.
 */
int stop_miracast_server();

/**
 * Cleans up resources used by the Miracast server.
 */
void cleanup_miracast_server();

#endif // MIRACAST_SERVER_H
