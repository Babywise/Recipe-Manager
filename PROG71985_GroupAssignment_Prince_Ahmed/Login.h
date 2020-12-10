#pragma once
#define MAX_NAME_LENGTH 255

#include "User.h"

#include <stdbool.h>

void getLoginFromUser(USER*);
void createAccount();
bool checkCreds(char*, char*, USER*);
