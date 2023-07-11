/*
 * Copyright (c) 2023-2023, OpenEmber Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     luhuadong    the first version
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "tusockit.h"

tusock_t *tcp_init(const char *ipaddr, const uint16_t port)
{
    struct tusock *dev = calloc(1, sizeof(struct tusock));
    if (!dev) {
        return NULL;
    }

    dev->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(dev->fd < 0) {
        free(dev);
        return NULL;
    }

    set_server_addr(dev, ipaddr, port);

    dev->status = UNCONNECTED;
    dev->is_init = true;
    
    return dev;
}

int tcp_deinit(struct tusock *dev)
{
    free(dev);
    
    return 0;
}

int tcp_open(struct tusock *dev)
{
    assert(dev);

    if (-1 == connect(dev->fd, (struct sockaddr* )&dev->param.server, sizeof(struct sockaddr))) {
        dev->status = DISCONNECTED;
        return -1;
    }

    dev->status = CONNECTED;

    return 0;
}

int tcp_close(struct tusock *dev)
{
    assert(dev);
    close(dev->fd);
    return 0;
}

int tcp_read(struct tusock *dev, void *buf, size_t len)
{
    assert(dev);
    assert(buf);

    int ret;
    struct ldal_tcp_device *link = (struct ldal_tcp_device *)dev->user_data;
    
    ret = recv(dev->fd, buf, len, 0);
    if (ret == -1) {
        return -1;
    }

    return 0;
}

int tcp_write(struct tusock *dev, const void *buf, size_t len)
{
    assert(dev);
    assert(buf);

    int ret;
    struct tusock_param *param = &dev->param;
    socklen_t addr_len = sizeof(struct sockaddr);

    ret = send(dev->fd, buf, len, 0);
    if (ret == -1) {
        return -1;
    }

    return 0;
}

int tcp_bind_local_addr(struct tusock *dev, const char *ipaddr, const uint16_t port)
{
    assert(dev);

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(struct sockaddr_in));

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);

    if (NULL == ipaddr) {
        saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        saddr.sin_addr.s_addr = inet_addr(ipaddr);
    }

    return bind(dev->fd, (struct sockaddr*)&saddr, sizeof(struct sockaddr));
}

void set_server_addr(struct tusock *dev, const char *ipaddr, const uint16_t port)
{
    assert(dev);

    struct tusock_param *param = &dev->param;

    param->server.sin_family = AF_INET;
    param->server.sin_port = htons(port);
    param->server.sin_addr.s_addr = inet_addr(ipaddr);

    snprintf(dev->filename, FILE_NAME_MAX, "%s:%u", ipaddr, port);
}

int tcp_connect_server_addr(struct tusock *dev, const char *ipaddr, const uint16_t port)
{
    assert(dev);

    set_server_addr(dev, ipaddr, port);
    if (-1 == connect(dev->fd, (struct sockaddr* )&dev->param.server, sizeof(struct sockaddr))) {
        return -1;
    }

    dev->status = CONNECTED;
    return 0;
}

int set_reuse_addr(struct tusock *dev)
{
    assert(dev);

    int optval = 1;
    int optlen = sizeof(optval);
    return setsockopt(dev->fd, SOL_SOCKET, SO_REUSEADDR, &optval, optlen);
}

