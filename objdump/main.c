/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** main
*/

#include "objdump.h"

int main(int ac, char **av)
{
    int fd;
    struct stat s;
    char *filename = "a.out";

    if (ac >= 2)
        filename = av[1];
    fd = open(filename, O_RDONLY);
    if (get_stat_file(fd, &s, filename, "objdump") == 84) {
        close(fd);
        return 84;
    }
    close(fd);
    return (0);
}