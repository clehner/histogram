#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "histogram.h"

#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))
#define ABS(a) (((a) < 0) ? -(a) : (a))

struct event {
    long time;
    float value;
};

struct testcase {
    int num_buckets;
    int bucket_size;
    int num_values;
    struct event *values;
    float *results;
};

struct testcase testcases[] = {
    {
        .num_buckets = 4,
        .bucket_size = 2,
        .num_values = 2,
        .values = (struct event[]){
            {7, 1},
            {19, -1}
        },
        .results = (float[]){
            2, 1, 1, 2
        }
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

        /* check histogram results */
        int time;
        float value;
        histogram_read_results(hist, time, value)
            // printf("%d %f, %f\n", time, value, tcase->results[time]);
            assert(ABS(tcase->results[time] - value) < 0.01);
    }

	return 0;
}


