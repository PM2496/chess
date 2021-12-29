#pragma once
#include "AI.h"

bool gameOver(int x, int y, int role);
int* compu(int depth);
int* human();
void control(int* p, int role);