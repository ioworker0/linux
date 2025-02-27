/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Support for Intel Camera Imaging ISP subsystem.
 * Copyright (c) 2015, Intel Corporation.
 */

#ifndef __GP_TIMER_GLOBAL_H_INCLUDED__
#define __GP_TIMER_GLOBAL_H_INCLUDED__

#include "hive_isp_css_defs.h" /*HIVE_GP_TIMER_SP_DMEM_ERROR_IRQ */

/* from gp_timer_defs.h*/
#define GP_TIMER_COUNT_TYPE_HIGH             0
#define GP_TIMER_COUNT_TYPE_LOW              1
#define GP_TIMER_COUNT_TYPE_POSEDGE          2
#define GP_TIMER_COUNT_TYPE_NEGEDGE          3
#define GP_TIMER_COUNT_TYPE_TYPES            4

/* timer - 3 is selected */
#define GP_TIMER_SEL                         3

/*HIVE_GP_TIMER_SP_DMEM_ERROR_IRQ is selected*/
#define GP_TIMER_SIGNAL_SELECT  HIVE_GP_TIMER_SP_DMEM_ERROR_IRQ

#endif /* __GP_TIMER_GLOBAL_H_INCLUDED__ */
