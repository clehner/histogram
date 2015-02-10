#include <malloc.h>

#include "histogram.h"

struct histogram *
histogram_new(int num_buckets, int bucket_size)
{
	struct histogram *hist = calloc(1, sizeof(*hist) +
			sizeof(hist->values[0]) * num_buckets);
	if (!hist) return NULL;
	hist->num_buckets = num_buckets;
	hist->bucket_size = bucket_size;
	return hist;
}

void
histogram_free(struct histogram *hist)
{
	free(hist);
}

void histogram_read_value(struct histogram *hist, long time, double value) {
	int bucket_offset = time % hist->bucket_size;
	int bucket = (time - bucket_offset) / hist->bucket_size;
	int num_buckets = hist->num_buckets;
	int bucket_i = bucket % num_buckets;
	int i;

	if (value == 0) {
		hist->values[bucket_i]++;
		return;
	}

	for (i = bucket_i; i < num_buckets; i++) {
		hist->values[i] += value;
	}
	hist->values[i] -= value * bucket_offset / hist->bucket_size;
	hist->value_all += value * (bucket_i - bucket) / num_buckets;
}
