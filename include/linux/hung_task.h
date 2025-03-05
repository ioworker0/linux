/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Detect Hung Task: detecting tasks stuck in D state
 *
 * Copyright 2025 Lance Yang <ioworker0@gmail.com>
 */
#ifndef __LINUX_HUNG_TASK_H
#define __LINUX_HUNG_TASK_H

#include <linux/bug.h>
#include <linux/sched.h>
#include <linux/compiler.h>

/*
 * @blocker: Combines lock address and blocking type.
 *
 * Since lock pointers are at least 4-byte aligned(32-bit) or 8-byte
 * aligned(64-bit). This leaves the 2 least bits (LSBs) of the pointer
 * always zero. So we can use these bits to encode the specific blocking
 * type.
 *
 * Type encoding:
 * 00 - Blocked on mutex        (BLOCKER_TYPE_MUTEX)
 * 01 - Blocked on semaphore    (BLOCKER_TYPE_SEM)
 * 10 - Blocked on rw-mutex     (BLOCKER_TYPE_RWMUTEX)
 * 11 - Blocked on rw-semaphore (BLOCKER_TYPE_RWSEM)
 */
#define BLOCKER_TYPE_MUTEX      0x00UL
#define BLOCKER_TYPE_SEM        0x01UL
#define BLOCKER_TYPE_RWMUTEX    0x02UL
#define BLOCKER_TYPE_RWSEM      0x03UL

#define BLOCKER_TYPE_MASK       0x03UL

#ifdef CONFIG_DETECT_HUNG_TASK_BLOCKER
static inline void hung_task_set_blocker(void *lock, unsigned long type)
{
	unsigned long lock_ptr = (unsigned long)lock;

	WARN_ON_ONCE(!lock_ptr);
	WARN_ON_ONCE(lock_ptr & BLOCKER_TYPE_MASK);
	WARN_ON_ONCE(READ_ONCE(current->blocker));

	WRITE_ONCE(current->blocker, lock_ptr | type);
}

static inline void hung_task_clear_blocker(void)
{
	WARN_ON_ONCE(!READ_ONCE(current->blocker));

	WRITE_ONCE(current->blocker, 0UL);
}

static inline bool hung_task_blocker_is_type(unsigned long blocker,
					  unsigned long type)
{
	WARN_ON_ONCE(!blocker);

	return (blocker & BLOCKER_TYPE_MASK) == type;
}

static inline void *hung_task_blocker_to_lock(unsigned long blocker)
{
	WARN_ON_ONCE(!blocker);

	return (void *)(blocker & ~BLOCKER_TYPE_MASK);
}
#else
#define hung_task_set_blocker(lock, type)       do {} while (0)
#define hung_task_clear_blocker()               do {} while (0)
static inline bool hung_task_blocker_is_type(unsigned long blocker,
					     unsigned long type)
{
	return false;
}
static inline void *hung_task_blocker_to_lock(unsigned long blocker)
{
	return NULL;
}
#endif

#endif /* __LINUX_HUNG_TASK_H */
