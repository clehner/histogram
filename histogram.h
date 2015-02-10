#ifndef __HISTOGRAM_H
#define __HISTOGRAM_H

struct histogram {
	unsigned int num_buckets;
	unsigned int bucket_size;
	double value_all;
	double values[];
};

struct histogram *histogram_new(int, int);
void histogram_free(struct histogram *);
void histogram_read_value(struct histogram *, long, double);

#define after(x) if (x, 1)

#define histogram_read_results(hist, time, value) \
	for (time = 0; time < hist->num_buckets; time++) \
		after (value = hist->values[time] + hist->value_all)

#endif /* __HISTOGRAM_H */
