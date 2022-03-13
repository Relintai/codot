
#include <stdio.h>

#include "core/math/vector2.h"

int main() {

	Vector2 v;

	vector2_set_all(&v, 23);
	vector2_max_axis(&v);

	printf("test %d\n", vector2_max_axis(&v));
}

