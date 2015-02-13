# histogram

Calculate histograms of time series data to Visual cyclic activity.

The primary indended use case is to visualize when people are logged into a
server, e.g. shared computer, game server, or IRC channel. If you have a log
file that shows when users enter and leave a shared space, you can use this
histogram utility/library to visualize the average number of users present
throughout a time cycle.

## Install
```
make
[sudo] make install [PREFIX=/usr/local]
```

## Usage
```
histogram [num_buckets] [bucket_size]
```

### Options
* `num_buckets`: number of buckets to divide the time into
* `bucket_size`: the size in time units of each bucket

### Input format
Each line should have two numbers separated by a space:
```c
long time, double value
```
`value` indicates the number of events starting (if positive) or ending (if
negative) at `time`. If `value` is 0, the event is counted as instantaneous
(taking up fully the one bucket that `time` falls into).

## API

```c
struct histogram *histogram_new(int num_buckets, int bucket_size);
```
Allocate a new histogram, with the given number of buckets and sizes of buckets. The range of the histogram will be `num_buckets` * `bucket_size`.

```c
void histogram_free(struct histogram *hist);
```
Free the memory for a histogram and its values.

```c
void histogram_read_value(struct histogram *hist, long time, double value);
```
Insert event occurences into the histogram. Options are as in the [input
format](#options) for the command line program.

```c
void histogram_done(struct histogram *hist);
```
Calculate the results of a histogram.

```c
histogram_read_results(hist, time, value) { ... };
```
Iterate through the results of a histogram, after calculating the results using
`histogram_done`.
- `hist` should be of type `struct histogram *`
- `time` should be of integer type of big enough size to hold the number of
buckets in the histogram.
- `value` should be a double to match the type of the values of the histogram.

## License

MIT
