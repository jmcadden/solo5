/* 
 * Copyright (c) 2015-2017 Contributors as noted in the AUTHORS file
 *
 * This file is part of Solo5, a unikernel base layer.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "kernel.h"

static uint64_t prev_time = 0;
static uint64_t clock_step = 300000;

void time_init(struct ukvm_boot_info *bi)
{
    assert(tscclock_init(bi->cpu.tsc_freq) == 0);

		// set the clock step 
    if (bi->cpu.tsc_step > 0) {
      clock_step = bi->cpu.tsc_step;
    }
}

uint64_t solo5_clock_monotonic(void)
{
  // manually increment the clock after the initial tsc read
  if (!prev_time)
    prev_time = tscclock_monotonic();
  else
    prev_time += clock_step;

  return prev_time;
}

/* return wall time in nsecs */
uint64_t solo5_clock_wall(void)
{
    return tscclock_monotonic() + tscclock_epochoffset();
}
