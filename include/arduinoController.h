#ifndef ARDUINOCONTROLLER_H
#define ARDUINOCONTROLLER_H
#include "serial_lib.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

static int fd;

void write_state(const unsigned char *msg, int msg_length, int usleep);
int read_ack(char *buf, int bufSize, int timeout);
void set_fd(int serial_fd);
#endif
