#ifndef EXECUTOR_EXECUTE_H
#define EXECUTOR_EXECUTE_H

#include "../include/shell.h"

void execute(Command *cmd);
void execute_pipeline(Command *cmd);

#endif