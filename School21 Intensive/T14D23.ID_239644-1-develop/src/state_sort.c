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

int write_record(FILE *fp, int index, const DoorRecord *record) {
    if (!fp || !record) return 0;
    if (fseek(fp, index * RECORD_SIZE, SEEK_SET) != 0) return 0;
    return fwrite(record, RECORD_SIZE, 1, fp) == 1;
}

int compare_records(const DoorRecord *a, const DoorRecord *b) {
    if (a->year != b->year) return a->year - b->year;
    if (a->month != b->month) return a->month - b->month;
    if (a->day != b->day) return a->day - b->day;
    if (a->hour != b->hour) return a->hour - b->hour;
    if (a->minute != b->minute) return a->minute - b->minute;
    return a->second - b->second;
}

void swap_records(FILE *fp, int i, int j) {
    DoorRecord a, b;
    if (read_record(fp, i, &a) && read_record(fp, j, &b)) {
        write_record(fp, i, &b);
        write_record(fp, j, &a);
    }
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

FILE *try_open_file_rw(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
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

    return fopen(alt_path, "rb+");
}

FILE *try_open_file_append(const char *filename) {
    FILE *fp = fopen(filename, "ab");
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

    return fopen(alt_path, "ab");
}

void sort_file(const char *filename) {
    FILE *fp = try_open_file_rw(filename);
    if (!fp) {
        printf("n/a\n");
        return;
    }

    int count = get_record_count(fp);
    if (count <= 0) {
        printf("n/a");
        fclose(fp);
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            DoorRecord a, b;
            if (read_record(fp, j, &a) && read_record(fp, j + 1, &b)) {
                if (compare_records(&a, &b) > 0) {
                    swap_records(fp, j, j + 1);
                }
            }
        }
    }

    fclose(fp);
}

void print_all_records(const char *filename) {
    FILE *fp = try_open_file(filename);
    if (!fp) {
        printf("n/a");
        return;
    }

    int count = get_record_count(fp);
    if (count <= 0) {
        printf("n/a");
        fclose(fp);
        return;
    }

    for (int i = 0; i < count; i++) {
        DoorRecord r;
        if (read_record(fp, i, &r)) {
            printf("%d %d %d %d %d %d %d %d", r.year, r.month, r.day, r.hour, r.minute, r.second, r.status,
                   r.code);
        }
        if (i < count - 1) {
            printf("\n");
        }
    }

    fclose(fp);
}

int add_record(const char *filename, const DoorRecord *record) {
    FILE *fp = try_open_file_append(filename);
    if (!fp) return 0;
    int res = fwrite(record, RECORD_SIZE, 1, fp) == 1;
    fclose(fp);
    return res;
}

int main(void) {
    char path[256];
    int option;

    if (scanf("%255s", path) != 1) {
        printf("n/a");
        return 1;
    }

    if (scanf("%d", &option) != 1) {
        printf("n/a");
        return 1;
    }

    if (option == 0) {
        print_all_records(path);
    } else if (option == 1) {
        sort_file(path);
        print_all_records(path);
    } else if (option == 2) {
        DoorRecord r;
        if (scanf("%d%d%d%d%d%d%d%d", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.second, &r.status,
                  &r.code) != 8) {
            printf("n/a");
            return 1;
        }

        if (!add_record(path, &r)) {
            printf("n/a");
            return 1;
        }

        sort_file(path);
        print_all_records(path);
    } else {
        printf("n/a");
    }

    return 0;
}
