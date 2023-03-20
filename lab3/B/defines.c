#include "defines.h"

const char* msgs[] = {"0.quit","1.add by key","2.delete by key","3.find by key","4.show table","5.delete by range of keys","6.reorganize","7.read from file"};
const char* errmsg[] = {"the key is already used","all good","no more space","cant find such key","cant open this file"};
const int Nmsgs = sizeof(msgs)/sizeof(msgs[0]);
