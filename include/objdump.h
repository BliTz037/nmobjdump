/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** objdump
*/

#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

int get_stat_file(int fd, struct stat *s, char *filename, char *exec);
int check_type_file(char *buf, char *filename, char *exec);
int check_arch(char *buf);

#endif /* !OBJDUMP_H_ */