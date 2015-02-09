#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "histogram.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "usage: %s num_buckets bucket_size\n", argv[0]);
		return 1;
	}

	int num_buckets = atoi(argv[1]);
	int bucket_size = atoi(argv[2]);
	struct histogram *hist = histogram_new(num_buckets, bucket_size);
	if (!hist) return 1;

	long time;
	float value;

	while (!feof(stdin)) {
		if (scanf("%ld %f\n", &time, &value) != 2) {
			fprintf(stderr, "%s: invalid input\n", argv[0]);
			return 1;
		}

		histogram_read_value(hist, time, value);
	}

	histogram_read_results(hist, time, value) {
		printf("%ld %f\n", time, value);
	}

	return 0;
}

