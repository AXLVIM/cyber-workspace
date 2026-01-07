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

FILE *try_open_file_read(const char *filename) {
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

FILE *try_open_file_write(const char *filename) {
    FILE *fp = fopen(filename, "wb");
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
    return fopen(alt_path, "wb");
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

int compare_dates(int day1, int month1, int year1, int day2, int month2, int year2) {
    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

int is_date_in_range(const DoorRecord *record, int start_day, int start_month, int start_year, int end_day,
                     int end_month, int end_year) {
    int cmp_start =
        compare_dates(record->day, record->month, record->year, start_day, start_month, start_year);
    int cmp_end = compare_dates(record->day, record->month, record->year, end_day, end_month, end_year);
    return cmp_start >= 0 && cmp_end <= 0;
}

FILE *create_temp_file(const char *filename, char *temp_filename, size_t temp_size) {
    size_t i = 0;
    while (filename[i] && i < temp_size - 5) {
        temp_filename[i] = filename[i];
        i++;
    }
    temp_filename[i] = '.';
    temp_filename[i + 1] = 't';
    temp_filename[i + 2] = 'm';
    temp_filename[i + 3] = 'p';
    temp_filename[i + 4] = '\0';
    FILE *write_fp = fopen(temp_filename, "wb");
    if (write_fp) return write_fp;
    char alt_temp[300];
    alt_temp[0] = '.';
    alt_temp[1] = '.';
    alt_temp[2] = '/';
    size_t j = 0;
    while (filename[j] && j < 255) {
        alt_temp[j + 3] = filename[j];
        j++;
    }
    alt_temp[j + 3] = '.';
    alt_temp[j + 4] = 't';
    alt_temp[j + 5] = 'm';
    alt_temp[j + 6] = 'p';
    alt_temp[j + 7] = '\0';
    write_fp = fopen(alt_temp, "wb");
    if (write_fp) {
        for (j = 0; alt_temp[j] && j < temp_size - 1; j++) {
            temp_filename[j] = alt_temp[j];
        }
        temp_filename[j] = '\0';
    }
    return write_fp;
}

int filter_records(FILE *read_fp, FILE *write_fp, int count, int start_day, int start_month, int start_year,
                   int end_day, int end_month, int end_year) {
    for (int j = 0; j < count; j++) {
        DoorRecord record;
        if (read_record(read_fp, j, &record)) {
            if (!is_date_in_range(&record, start_day, start_month, start_year, end_day, end_month,
                                  end_year)) {
                if (fwrite(&record, RECORD_SIZE, 1, write_fp) != 1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int replace_original_file(const char *filename, char *temp_filename, char *original_path) {
    int i = 0, found_original = 0;
    FILE *test_fp = fopen(filename, "rb");
    if (test_fp) {
        fclose(test_fp);
        for (i = 0; filename[i] && i < 299; i++) {
            original_path[i] = filename[i];
        }
        original_path[i] = '\0';
        found_original = 1;
    } else {
        test_fp = try_open_file_read(filename);
        if (test_fp) {
            fclose(test_fp);
            original_path[0] = '.';
            original_path[1] = '.';
            original_path[2] = '/';
            for (i = 0; filename[i] && i < 255; i++) {
                original_path[i + 3] = filename[i];
            }
            original_path[i + 3] = '\0';
            found_original = 1;
        }
    }
    if (!found_original) {
        remove(temp_filename);
        return 0;
    }
    if (remove(original_path) != 0) {
        remove(temp_filename);
        return 0;
    }
    if (rename(temp_filename, original_path) != 0) {
        return 0;
    }
    return 1;
}

int clear_data_in_range(const char *filename, const char *start_date, const char *end_date) {
    FILE *read_fp = try_open_file_read(filename);
    if (!read_fp) return 0;
    int start_day, start_month, start_year, end_day, end_month, end_year;
    if (!parse_date(start_date, &start_day, &start_month, &start_year) ||
        !parse_date(end_date, &end_day, &end_month, &end_year)) {
        fclose(read_fp);
        return 0;
    }
    int count = get_record_count(read_fp);
    if (count <= 0) {
        fclose(read_fp);
        return 0;
    }
    char temp_filename[512], original_path[300];
    FILE *write_fp = create_temp_file(filename, temp_filename, sizeof(temp_filename));
    if (!write_fp) {
        fclose(read_fp);
        return 0;
    }
    if (!filter_records(read_fp, write_fp, count, start_day, start_month, start_year, end_day, end_month,
                        end_year)) {
        fclose(read_fp);
        fclose(write_fp);
        remove(temp_filename);
        return 0;
    }
    fclose(read_fp);
    fclose(write_fp);
    return replace_original_file(filename, temp_filename, original_path);
}

void print_all_records(const char *filename) {
    FILE *fp = try_open_file_read(filename);
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

int main(void) {
    char path[256];
    char start_date[256];
    char end_date[256];
    if (scanf("%255s", path) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%255s", start_date) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%255s", end_date) != 1) {
        printf("n/a");
        return 1;
    }
    if (!clear_data_in_range(path, start_date, end_date)) {
        printf("n/a");
        return 1;
    }
    print_all_records(path);
    return 0;
}
