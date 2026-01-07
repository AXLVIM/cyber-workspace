#include <stdio.h>

#define RECORD_SIZE sizeof(DoorRecord)

typedef struct {
    int year, month, day, hour, minute, second;
    int status;
    int code;
} DoorRecord;

int get_record_count(FILE *fp) {
    if (!fp) return -1;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    return (int)(size / RECORD_SIZE);
}

int read_record(FILE *fp, int index, DoorRecord *record) {
    if (!fp || !record) return 0;
    if (fseek(fp, index * RECORD_SIZE, SEEK_SET) != 0) return 0;
    return fread(record, RECORD_SIZE, 1, fp) == 1;
}

FILE *try_open_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) return fp;

    char alt_path[300];
    int i = 0;
    alt_path[0] = '.';
    alt_path[1] = '.';
    alt_path[2] = '/';
    while (filename[i] && i < 255) {
        alt_path[i + 3] = filename[i];
        i++;
    }
    alt_path[i + 3] = '\0';

    return fopen(alt_path, "rb");
}

int get_string_length(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int parse_date(const char *date_str, int *day, int *month, int *year) {
    if (!date_str || !day || !month || !year) return 0;

    int len = get_string_length(date_str);
    if (len != 10) return 0;

    if (date_str[2] != '.' || date_str[5] != '.') return 0;

    *day = 0;
    *month = 0;
    *year = 0;

    for (int i = 0; i < 2; i++) {
        if (date_str[i] < '0' || date_str[i] > '9') return 0;
        *day = *day * 10 + (date_str[i] - '0');
    }

    for (int i = 3; i < 5; i++) {
        if (date_str[i] < '0' || date_str[i] > '9') return 0;
        *month = *month * 10 + (date_str[i] - '0');
    }

    for (int i = 6; i < 10; i++) {
        if (date_str[i] < '0' || date_str[i] > '9') return 0;
        *year = *year * 10 + (date_str[i] - '0');
    }

    return 1;
}

int search_by_date(const char *filename, const char *date_str) {
    FILE *fp = try_open_file(filename);
    if (!fp) {
        return -1;
    }

    int search_day, search_month, search_year;
    if (!parse_date(date_str, &search_day, &search_month, &search_year)) {
        fclose(fp);
        return -1;
    }

    int count = get_record_count(fp);
    if (count <= 0) {
        fclose(fp);
        return -1;
    }

    for (int i = 0; i < count; i++) {
        DoorRecord r;
        if (read_record(fp, i, &r)) {
            if (r.day == search_day && r.month == search_month && r.year == search_year) {
                fclose(fp);
                return r.code;
            }
        }
    }

    fclose(fp);
    return -1;
}

int main(void) {
    char path[256];
    char date[256];

    if (scanf("%255s", path) != 1) {
        printf("n/a");
        return 1;
    }

    if (scanf("%255s", date) != 1) {
        printf("n/a");
        return 1;
    }

    int code = search_by_date(path, date);
    if (code == -1) {
        printf("n/a");
    } else {
        printf("%d", code);
    }

    return 0;
}