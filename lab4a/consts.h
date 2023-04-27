#ifndef PRIMARY_H
#define PRIMARY_H

extern const char* msgs[];
extern const char* errmsg[];
extern const int Nmsgs;
enum Err
{
    OK,
    EMPTY,
    NO_KEY,
    BAD_INPUT
};
#endif