#include <limits.h>
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
	hist->begin_time = LONG_MAX;
	hist->end_time = 0;
	return hist;
}

void
histogram_free(struct histogram *hist)
{
	free(hist);
}

void
update(unsigned int num_buckets, unsigned int bucket_size,
		double values[num_buckets], double *value_all,
		long time, double value)
{
	int bucket_offset = time % bucket_size;
	int bucket = (time - bucket_offset) / bucket_size;
	int bucket_i = bucket % num_buckets;
	unsigned int i;

	if (value == 0) {
		values[bucket_i]++;
		return;
	}

	for (i = bucket_i; i < num_buckets; i++) {
		values[i] += value;
	}
	values[i] -= value * bucket_offset / bucket_size;
	*value_all += value * (bucket_i - bucket) / num_buckets;
}

void
histogram_read_value(struct histogram *hist, long time, double value)
{
	update(hist->num_buckets, hist->bucket_size,
			hist->values, &hist->value_all,
			time, value);
	if (time > hist->end_time)
		hist->end_time = time;
	if (time < hist->begin_time)
		hist->begin_time = time;
}

void
histogram_done(struct histogram *hist)
{
	unsigned int num_buckets = hist->num_buckets;
	unsigned int value_all = hist->value_all;
	double totals[num_buckets], totals_all = 0;

	for (unsigned int i = 0; i < num_buckets; i++) {
		totals[i] = 0;
	}

	update(num_buckets, hist->bucket_size,
			totals, &totals_all, hist->begin_time, 1);
	update(num_buckets, hist->bucket_size,
			totals, &totals_all, hist->end_time, -1);

	for (unsigned int i = 0; i < num_buckets; i++) {
		hist->values[i] = (hist->values[i] + value_all) /
			(totals[i] + totals_all);
	}
}
