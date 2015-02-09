#ifndef __HISTOGRAM_H
#define __HISTOGRAM_H

enum histogram_event {
	HISTOGRAM_EVENT_START = 1,
	HISTOGRAM_EVENT_END = -1,
	HISTOGRAM_EVENT_INSTANT = 0,
};

struct histogram {
	int num_buckets;
	int bucket_size;
	float values[];
};

struct histogram *histogram_new(int, int);
void histogram_free(struct histogram *);
void histogram_read_value(struct histogram *, enum histogram_event, long,
		float);

#define histogram_read_results(hist, time, value) \
	for (time = 0; \
			time < hist->num_buckets && \
			(value = hist->values[time], 0); \
			time++)

#endif /* __HISTOGRAM_H */
