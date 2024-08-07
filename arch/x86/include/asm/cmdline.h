/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_CMDLINE_H
#define _ASM_X86_CMDLINE_H

#include <asm/setup.h>

extern char builtin_cmdline[COMMAND_LINE_SIZE];

int cmdline_find_option_bool(const char *cmdline_ptr, const char *option);
int cmdline_find_option(const char *cmdline_ptr, const char *option,
			char *buffer, int bufsize);

#endif /* _ASM_X86_CMDLINE_H */
