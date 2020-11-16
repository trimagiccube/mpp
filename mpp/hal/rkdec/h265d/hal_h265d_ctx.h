/*
 * Copyright 2020 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HAL_H265D_CTX_H__
#define __HAL_H265D_CTX_H__

#include "mpp_device.h"
#include "mpp_hal.h"

#define MAX_GEN_REG 3

typedef struct H265dRegBuf_t {
    RK_S32    use_flag;
    MppBuffer scaling_list_data;
    MppBuffer pps_data;
    MppBuffer rps_data;
    void*     hw_regs;
} H265dRegBuf;

typedef struct HalH265dCtx_t {
    /* for hal api call back */
    const MppHalApi *api;

    /* for hardware info */
    MppClientType   client_type;
    RK_U32          hw_id;
    MppDev          dev;

    /* for resource */
    MppBufSlots     slots;
    MppBufSlots     packet_slots;
    MppBufferGroup  group;
    MppBuffer       cabac_table_data;
    MppBuffer       scaling_list_data;
    MppBuffer       pps_data;
    MppBuffer       rps_data;
    MppBuffer       rcb_buf;
    void*           hw_regs;
    H265dRegBuf     g_buf[MAX_GEN_REG];
    RK_U32          fast_mode;
    IOInterruptCB   int_cb;
    RK_U32          fast_mode_err_found;
    void            *scaling_rk;
    void            *scaling_qm;
    RK_U32          is_v345;
    RK_U32          is_v34x;
} HalH265dCtx;

typedef struct ScalingList {
    /* This is a little wasteful, since sizeID 0 only needs 8 coeffs,
     * and size ID 3 only has 2 arrays, not 6. */
    RK_U8 sl[4][6][64];
    RK_U8 sl_dc[2][6];
} scalingList_t;

typedef struct ScalingFactor_Model {
    RK_U8 scalingfactor0[1248];
    RK_U8 scalingfactor1[96];     /*4X4 TU Rotate, total 16X4*/
    RK_U8 scalingdc[12];          /*N1005 Vienna Meeting*/
    RK_U8 reserverd[4];           /*16Bytes align*/
} scalingFactor_t;

#endif