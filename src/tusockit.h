/*
 * Copyright (c) 2023-2023, OpenEmber Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     luhuadong    the first version
 */

#ifndef __TUSOCKIT_H__
#define __TUSOCKIT_H__

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h> 

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_NAME_MAX          32

typedef enum {
    UNCONNECTED = 0,
    CONNECTED,
    DISCONNECTED,
    LISTENING,
    UNINITIALIZED,
    ERROR
} sock_status_t;

struct tusock_param
{
    char *device_name;
    char *file_name;

    struct sockaddr_in local;     /* local addr */
    struct sockaddr_in server;    /* server addr */
};
typedef struct tusock_param tusock_param_t;

struct tusock
{
    int fd;                            /* File descriptor */
    char filename[FILE_NAME_MAX];      /* Device file name */
    sock_status_t status;              /* Device status */
    bool is_init;                      /* Device initialization completed */

    tusock_param_t param;

    void *user_data;                   /* User-specific data */
};
typedef struct tusock tusock_t;        /* Type for ldal device. */

tusock_t *tcp_init(const char *ipaddr, const uint16_t port);
int tcp_deinit(struct tusock *dev);
int tcp_open(struct tusock *dev);
int tcp_close(struct tusock *dev);
int tcp_read(struct tusock *dev, void *buf, size_t len);
int tcp_write(struct tusock *dev, const void *buf, size_t len);
void set_server_addr(struct tusock *dev, const char *ipaddr, const uint16_t port);
int tcp_connect_server_addr(struct tusock *dev, const char *ipaddr, const uint16_t port);

#ifdef __cplusplus
}
#endif

#endif /* __TUSOCKIT_H__ */