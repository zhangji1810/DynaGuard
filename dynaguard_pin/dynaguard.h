/*
 * Copyright (c) 2013, Columbia University
 * All rights reserved.
 *
 * This software was developed by Theofilos Petsios <theofilos@cs.columbia.edu>
 * and Vasileios P. Kemerlis <vpk@cs.columbia.edu> at Columbia University,
 * New York, NY, USA, in November 2013.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Columbia University nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __DYNAGUARD_H__
#define __DYNAGUARD_H__

/* compiler directives for branch prediction */
#define	likely(x)	__builtin_expect((x), 1)
#define	unlikely(x)	__builtin_expect((x), 0)

#if	defined(__x86_64__)
#define	TLS_BASE		REG_SEG_FS_BASE		/* TLS BASE		*/
#define	CAN_SEG_REG		REG_SEG_FS		/* TLS register (FS)	*/
#define	CAN_SEG_REG_OFFSET	0x28			/* TLS offset (0x28)	*/
#define	MASK_VAL		0x00000000FFFFFFFF	/* 32-bit mask		*/
#define	SHIFT_VAL		32			/* 32-bit shift value	*/
#elif	defined(__i386__)
#define	TLS_BASE		REG_SEG_GS_BASE		/* TLS BASE		*/
#define	CAN_SEG_REG		REG_SEG_GS		/* TLS register (GS)	*/
#define	CAN_SEG_REG_OFFSET	0x14			/* TLS offset (0x14)	*/
#else
#error "Unsupported architecture"
#endif

/* urandom device path */
#define URANDOM_PATH		"/dev/urandom"

/* canary */
typedef unsigned long canary_t;

/* thread context definition */
typedef struct {
	canary_t 	**cstack;	/* array of pointers to canaries */
	unsigned long	cstack_sz;	/* array size (in bytes) */
	unsigned long	cstack_idx;	/* index of the next free slot */
} thread_ctx_t;

#endif /* __DYNAGUARD_H__ */