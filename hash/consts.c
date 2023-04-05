#include "consts.h"

const int primary[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
const int primary_size = sizeof(primary)/sizeof(int);
const char* msgs[] = {"0.quit","1.add by key","2.delete by key","3.find by key","4.show table"};
const char* errmsg[] = {"all good","no more space","cant find such key or release","cant open this file"};
const int Nmsgs = sizeof(msgs)/sizeof(msgs[0]);

