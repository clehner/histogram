#include <malloc.h>

#include "histogram.h"

struct histogram *
histogram_new(int num_buckets, int bucket_size)
{
	struct histogram *hist = malloc(sizeof(*hist) +
			sizeof(hist->values[0]) * num_buckets);
}

void
histogram_free(struct histogram *hist)
{
	free(hist);
}

void
histogram_read_value(struct histogram *hist, enum histogram_event type,
		long time, float value)
{
}
