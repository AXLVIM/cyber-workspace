#include "data_stat.h"

double max(double *data, int n) {
    double m = data[0];
    for (int i = 1; i < n; ++i)
        if (data[i] > m) m = data[i];
    return m;
}

double min(double *data, int n) {
    double m = data[0];
    for (int i = 1; i < n; ++i)
        if (data[i] < m) m = data[i];
    return m;
}

double mean(double *data, int n) {
    double s = 0.0;
    for (int i = 0; i < n; ++i) s += data[i];
    return s / n;
}

double variance(double *data, int n) {
    double m = mean(data, n);
    double s = 0.0;
    for (int i = 0; i < n; ++i) {
        double d = data[i] - m;
        s += d * d;
    }
    return s / n;
}