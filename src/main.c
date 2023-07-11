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

    tusock_t *node = tcp_init();
    if (node && node->is_init) {
        tcp_open(node);
        tcp_close(node);
    }
    tcp_deinit(node);
    
    return 0;
}
