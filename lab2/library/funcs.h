#ifndef FUNCS_H
#define FUNCS_H

int check_note(char* str);
char** parse_str(char* str, int* notes_count);
patient make_client(char* str);
void delete_note(char** notes,int* notes_count, int index);
patient find_curr(char** notes,int* notes_count, int curr_time);
int get_int(int* value);
#endif
