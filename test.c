#include <assert.h>

#include "histogram.h"

#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))

struct event {
	long time;
	double value;
};

struct testcase {
	int num_buckets;
	int bucket_size;
	int num_values;
	struct event *values;
	double *results;
};

#define VALS(...) __VA_ARGS__
#define RESULTS(...) .results = (double[])__VA_ARGS__,\
	.num_buckets = ARRAY_SIZE((double[])VALS(__VA_ARGS__))
#define VALUES(...) .values = (struct event[])VALS(__VA_ARGS__),\
	.num_values = ARRAY_SIZE((struct event[])VALS(__VA_ARGS__))

struct testcase testcases[] = {
	{
		.bucket_size = 2,
		RESULTS({1.5, 1.25, 1.25, 1.5}),
		VALUES({
			{0, 1},
			{7, 1},
			{19, -1},
			{32, -1},
		})
	},

	{
		.bucket_size = 2,
		RESULTS({0.5, 1, 0, 1}),
		VALUES({
			{6, 0},
			{7, 0},
			{19, 0},
			{16, 0},
		})
	}
};

int main()
{
	for (unsigned int i = 0; i < ARRAY_SIZE(testcases); i++) {
		struct testcase *tcase = &testcases[i];
		struct histogram *hist = histogram_new(tcase->num_buckets,
				tcase->bucket_size);

		assert(hist);

		/* read in test values */
		for (int j = 0; j < tcase->num_values; j++) {
			struct event *event = &tcase->values[j];
			histogram_read_value(hist, event->time, event->value);
		}

		histogram_done(hist);

		/* check histogram results */
		unsigned int time;
		float value;
		histogram_read_results(hist, time, value)
			// printf("%d %f, %f\n", time, value, tcase->results[time]);
			assert(tcase->results[time] == value);
	}

	return 0;
}


