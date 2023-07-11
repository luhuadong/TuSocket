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
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include "tusockit.h"

static const char *TEST_MESSAGE = "Hello, Tusockit!\n";

static void show_brand()
{
    printf("\n");
    printf("████████╗██╗   ██╗███████╗ ██████╗  ██████╗██╗  ██╗██╗████████╗\n");
    printf("╚══██╔══╝██║   ██║██╔════╝██╔═══██╗██╔════╝██║ ██╔╝██║╚══██╔══╝\n");
    printf("   ██║   ██║   ██║███████╗██║   ██║██║     █████╔╝ ██║   ██║   \n");
    printf("   ██║   ██║   ██║╚════██║██║   ██║██║     ██╔═██╗ ██║   ██║   \n");
    printf("   ██║   ╚██████╔╝███████║╚██████╔╝╚██████╗██║  ██╗██║   ██║   \n");
    printf("   ╚═╝    ╚═════╝ ╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚═╝   ╚═╝   \n");
    printf("\n");
}

int main(int argc, char *argv[])
{
    show_brand();

    tusock_t *node = tcp_init("10.1.26.131", 6000);

    if (!node) {
        printf("Create socket failed\n");
        return -1;
    }
    
    tcp_open(node); // Connect to server

    if (node->status == CONNECTED) {
        printf("Connected!\n");

        while (1) {
            tcp_write(node, TEST_MESSAGE, strlen(TEST_MESSAGE));
            sleep(1);
        }
    }

    tcp_close(node);
    tcp_deinit(node);
    
    return 0;
}
