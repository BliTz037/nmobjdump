/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** file
*/

#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int get_stat_file(int fd, struct stat *s, char *filename, char *exec)
{
    if (fd == -1) {
        printf("%s: '%s': No such file\n", exec, filename);
        return 84;
    }
    fstat(fd, s);
    if (S_ISREG(s->st_mode) == 0) {
        printf("%s: Warning: '%s' is a directory\n", exec, filename);
        return 84;
    }
    return 0;
}

int check_type_file(uint16_t e_type, char *filename, char *exec)
{
    if (e_type == ET_NONE)
        return 0;
    if (e_type == ET_REL)
        return 0;
    if (e_type == ET_EXEC)
        return 0;
    if (e_type == ET_DYN)
        return 0;
    if (e_type == ET_CORE)
        return 0;
    printf("%s: %s: file format not recognized\n", exec, filename);
    return -1;
}