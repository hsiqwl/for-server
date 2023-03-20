#ifndef FUNCS_H
#define FUNCS_H
typedef struct line
{
	int line_lenght;
	int* arr;
}line;
int get_int(int* value);
int get_len(int* len);
int input_matrix(int lines_count,line** matrix);
int input_line(int** arr, int line_lenght);
void print_matrix(line* matrix, int lines_count);
int cmp(const void* a, const void* b);
void clean_memory(line** matrix, int lines_count);
int find_max_lenght(line* matrix, int lines_count);
void add_zeros(line** matrix, int lines_count, int max_lenght);
void swap(void* a, void* b, int size);
void swap_first_column(line** matrix, int lines_count, int index);
#endif
