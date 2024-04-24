#ifndef LITTLETHING_TIMER_H
#define LITTLETHING_TIMER_H

#include "../littlething.h"

/* ================================================================ */

struct timer {

	/* Last frame end time in ticks */
	uint64_t pt;

	/* Delta time between two frames */
	float d;

	/* Accumulator */
	float acc;

	/* The variable can be used to specify the amount of time to wait before executing a particular action */
	float time;
};

typedef struct timer* Timer_t;

/* ========================== INTERFACE =========================== */

extern int Timer_new(Timer_t* t);

/* ================================ */

extern int Timer_destroy(Timer_t* t);

/* ================================ */

extern int Timer_set(const Timer_t t, float v);

/* ================================ */

extern int Timer_is_ready(const Timer_t t);

/* ================================ */

extern int Timer_reset(const Timer_t t);

/* ================================ */

extern void Timer_tick(const Timer_t t);

/* ================================================================ */

#endif /* LITTLETHING_TIMER_H */
