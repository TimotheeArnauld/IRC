#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <fcntl.h>

/**
 *essaie de retrouver le path d'un fichier de keyboard connecté
 */


char *get_keyboard_event_file(void);
