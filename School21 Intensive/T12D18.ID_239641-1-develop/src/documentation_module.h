#ifndef DOCUMENTATION_MODULE_H
#define DOCUMENTATION_MODULE_H

#define DOCUMENTS_COUNT 4
#define DOCUMENTS "Linked lists", "Queues", "Maps", "Binary Trees"
#define AVAILABLE_DOCUMENT "Binary Trees"

int validate(const char *data);
int *check_available_documentation_module(int (*validate)(const char *), int document_count, ...);

#endif
