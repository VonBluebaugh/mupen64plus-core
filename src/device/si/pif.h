/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - pif.h                                                   *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2002 Hacktarux                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef M64P_DEVICE_SI_PIF_H
#define M64P_DEVICE_SI_PIF_H

#include <stddef.h>
#include <stdint.h>

#include "cic.h"

struct joybus_device_interface;
struct si_controller;

enum { PIF_RAM_SIZE = 0x40 };
enum { PIF_CHANNELS_COUNT = 5 };

struct pif_channel
{
    void* jbd;
    const struct joybus_device_interface* ijbd;

    uint8_t* tx;
    uint8_t* tx_buf;
    uint8_t* rx;
    uint8_t* rx_buf;
};

void disable_pif_channel(struct pif_channel* channel);
size_t setup_pif_channel(struct pif_channel* channel, uint8_t* buf);

struct pif
{
    uint8_t* ram;
    struct pif_channel channels[PIF_CHANNELS_COUNT];

    struct cic cic;
};

static uint32_t pif_ram_address(uint32_t address)
{
    return ((address & 0xfffc) - 0x7c0);
}


void init_pif(struct pif* pif,
    uint8_t* pif_base,
    void* jbds[PIF_CHANNELS_COUNT],
    const struct joybus_device_interface* ijbds[PIF_CHANNELS_COUNT],
    const uint8_t* ipl3);

void poweron_pif(struct pif* pif);

void setup_channels_format(struct pif* pif);

void read_pif_ram(void* opaque, uint32_t address, uint32_t* value);
void write_pif_ram(void* opaque, uint32_t address, uint32_t value, uint32_t mask);

void process_pif_ram(struct si_controller* si);
void update_pif_ram(struct si_controller* si);

#endif

