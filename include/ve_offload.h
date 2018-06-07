/* Copyright (C) 2017-2018 by NEC Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/**
 * @file ve_offload.h
 */
#ifndef _VE_OFFLOAD_H_
#define _VE_OFFLOAD_H_

#define VEO_SYMNAME_LEN_MAX (255)
#define VEO_LOG_CATEGORY "veos.veo"
#define VEO_MAX_NUM_ARGS (32)

#define VEO_REQUEST_ID_INVALID (~0UL)

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
enum veo_context_state {
  VEO_STATE_UNKNOWN = 0,
  VEO_STATE_RUNNING,
  VEO_STATE_SYSCALL,
  VEO_STATE_BLOCKED,
  VEO_STATE_EXIT,
};

enum veo_command_state {
  VEO_COMMAND_OK = 0,
  VEO_COMMAND_EXCEPTION,
  VEO_COMMAND_ERROR,
  VEO_COMMAND_UNFINISHED,
};


struct veo_call_args {
  uint64_t arguments[VEO_MAX_NUM_ARGS];
	int nargs;
};

struct veo_proc_handle;
struct veo_thr_ctxt;

struct veo_proc_handle *veo_proc_create(int);
int veo_proc_destroy(struct veo_proc_handle *);
struct veo_proc_handle *veo_proc__create(const char *, const char *);
uint64_t veo_load_library(struct veo_proc_handle *, const char *);
uint64_t veo_get_sym(struct veo_proc_handle *, uint64_t, const char *);

struct veo_thr_ctxt *veo_context_open(struct veo_proc_handle *);
int veo_context_close(struct veo_thr_ctxt *);
int veo_get_context_state(struct veo_thr_ctxt *);
uint64_t veo_call_async(struct veo_thr_ctxt *, uint64_t,
                        const struct veo_call_args *);
int veo_call_peek_result(struct veo_thr_ctxt *, uint64_t, uint64_t *);
int veo_call_wait_result(struct veo_thr_ctxt *, uint64_t, uint64_t *);
int veo_alloc_mem(struct veo_proc_handle *, uint64_t *, const size_t);
int veo_free_mem(struct veo_proc_handle *, uint64_t);
int veo_read_mem(struct veo_proc_handle *, void *, uint64_t, size_t);
int veo_write_mem(struct veo_proc_handle *, uint64_t, void *, size_t);
#ifdef __cplusplus
} // extern "C"
#endif
#endif