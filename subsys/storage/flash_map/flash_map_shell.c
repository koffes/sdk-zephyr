/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/shell/shell.h>
#include <zephyr/init.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL

LOG_MODULE_REGISTER(flash_map_shell);

extern const struct flash_area *flash_map;

static void fa_cb(const struct flash_area *fa, void *user_data)
{
	struct shell *shell = user_data;

	shell_print(sh, "%2d   0x%0*"PRIxPTR"   %-26s  0x%-10x 0x%-12x",
		    (int)fa->fa_id, sizeof(uintptr_t) * 2, (uintptr_t)fa->fa_dev, fa->fa_dev->name,
		    (uint32_t) fa->fa_off, fa->fa_size);
}

static int cmd_flash_map_list(const struct shell *sh, size_t argc,
			      char **argv)
{
	shell_print(sh, "ID | Device     | Device Name               "
		    "|   Offset   |   Size");
	shell_print(sh, "-----------------------------------------"
		    "------------------------------");
	flash_area_foreach(fa_cb, (struct shell *)shell);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_flash_map,
	/* Alphabetically sorted. */
	SHELL_CMD(list, NULL, "List flash areas", cmd_flash_map_list),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(flash_map, &sub_flash_map, "Flash map commands", NULL);
