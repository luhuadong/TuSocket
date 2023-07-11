/*
 * Copyright (c) 2023-2023, OpenEmber Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     luhuadong    the first version
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "tusockit.h"

tusock_t *tcp_init(void)
{
    struct tusock *dev = calloc(1, sizeof(struct tusock));
    if (!dev) {
        return NULL;
    }
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

    int s;
    struct sockaddr_in addr;

    dev->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(dev->fd < 0) {
        return -1;
    }

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
    struct ldal_tcp_device *link = (struct ldal_tcp_device *)dev->user_data;
    socklen_t addr_len = sizeof(struct sockaddr);

    ret = send(dev->fd, buf, len, 0);
    if (ret == -1) {
        return -1;
    }

    return 0;
}