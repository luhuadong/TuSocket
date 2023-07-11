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
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct tusock
{
    int fd;                            /* File descriptor */
    bool is_init;                      /* Device initialization completed */

    void *user_data;                   /* User-specific data */
};
typedef struct tusock tusock_t;        /* Type for ldal device. */

tusock_t *tcp_init(void);
int tcp_deinit(struct tusock *dev);
int tcp_open(struct tusock *dev);
int tcp_close(struct tusock *dev);
int tcp_read(struct tusock *dev, void *buf, size_t len);
int tcp_write(struct tusock *dev, const void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* __TUSOCKIT_H__ */