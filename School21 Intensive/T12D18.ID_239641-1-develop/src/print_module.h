#ifndef PRINT_MODULE_H
#define PRINT_MODULE_H

#define Module_load_success_message "Module loaded successfully."
#define Log_prefix "[LOG]"

char print_char(char ch);
void print_log(char (*print)(char), const char *message);

#endif
