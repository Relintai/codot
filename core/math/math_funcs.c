/*************************************************************************/
/*  math_funcs.cpp                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "math_funcs.h"
#include <math.h>

//#include "core/error_macros.h"

//RandomPCG math_default_rand(RandomPCG::DEFAULT_SEED, RandomPCG::DEFAULT_INC);

#define PHI 0x9e3779b9

uint32_t math_rand_from_seed(uint64_t *seed) {
	/*
	RandomPCG rng = RandomPCG(*seed, RandomPCG::DEFAULT_INC);
	uint32_t r = rng.rand();
	*seed = rng.get_seed();
	return r;
	*/
	return 0;
}

void math_seed(uint64_t x) {
	//default_rand.seed(x);
}

void math_randomize() {
	//default_rand.randomize();
}

uint32_t math_rand() {
	//return default_rand.rand();
	return 0;
}

int math_step_decimals(double p_step) {
	static const int maxn = 10;
	static const double sd[10] = {
		0.9999, // somehow compensate for floating point error
		0.09999,
		0.009999,
		0.0009999,
		0.00009999,
		0.000009999,
		0.0000009999,
		0.00000009999,
		0.000000009999,
		0.0000000009999
	};

	double abs = math_absd(p_step);
	double decs = abs - (int)abs; // Strip away integer part
	for (int i = 0; i < maxn; i++) {
		if (decs >= sd[i]) {
			return i;
		}
	}

	return 0;
}


double math_ease(double p_x, double p_c) {
	if (p_x < 0) {
		p_x = 0;
	} else if (p_x > 1.0) {
		p_x = 1.0;
	}
	if (p_c > 0) {
		if (p_c < 1.0) {
			return 1.0 - math_powd(1.0 - p_x, 1.0 / p_c);
		} else {
			return math_powd(p_x, p_c);
		}
	} else if (p_c < 0) {
		//inout ease

		if (p_x < 0.5) {
			return math_powd(p_x * 2.0, -p_c) * 0.5;
		} else {
			return (1.0 - math_powd(1.0 - (p_x - 0.5) * 2.0, -p_c)) * 0.5 + 0.5;
		}
	} else {
		return 0; // no ease (raw)
	}
}

// Only meant for editor usage in float ranges, where a step of 0
// means that decimal digits should not be limited in String::num.
int math_range_step_decimals(double p_step) {
	if (p_step < 0.0000000000001) {
		return 16; // Max value hardcoded in String::num
	}
	return math_step_decimals(p_step);
}

double math_dectime(double p_value, double p_amount, double p_step) {
	//WARN_DEPRECATED_MSG("The `dectime()` function has been deprecated and will be removed in Godot 4.0. Use `move_toward()` instead.");
	double sgn = p_value < 0 ? -1.0 : 1.0;
	double val = math_absd(p_value);
	val -= p_amount * p_step;
	if (val < 0.0) {
		val = 0.0;
	}
	return val * sgn;
}

float math_stepifyf(float p_value, float p_step) {
	if (p_step != 0) {
		p_value = math_floorf(p_value / p_step + 0.5) * p_step;
	}
	return p_value;
}

double math_stepifyd(double p_value, double p_step) {
	if (p_step != 0) {
		p_value = math_floord(p_value / p_step + 0.5) * p_step;
	}
	return p_value;
}

uint32_t math_larger_prime(uint32_t p_val) {
	static const uint32_t primes[] = {
		5,
		13,
		23,
		47,
		97,
		193,
		389,
		769,
		1543,
		3079,
		6151,
		12289,
		24593,
		49157,
		98317,
		196613,
		393241,
		786433,
		1572869,
		3145739,
		6291469,
		12582917,
		25165843,
		50331653,
		100663319,
		201326611,
		402653189,
		805306457,
		1610612741,
		0,
	};

	int idx = 0;
	while (true) {
		//ERR_FAIL_COND_V(primes[idx] == 0, 0);
		if (primes[idx] > p_val) {
			return primes[idx];
		}
		idx++;
	}
}

double math_randomd(double from, double to) {
	//return default_rand.random(from, to);

	return 0;
}

float math_randomf(float from, float to) {
	//return default_rand.random(from, to);

	return 0;
}
