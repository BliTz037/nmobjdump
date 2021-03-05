/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** main
*/

#include "nm.h"

int get_elf(int fd, struct stat s, char *filename)
{
    void *buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (buf == (void *)(-1))
        return 84;
    if (check_type_file((char *)buf, filename, "nm") == -1)
        return 84;
    if (check_arch((char *)buf) == ELFCLASS64)
        nm_64(buf);
    if (check_arch((char *)buf) == ELFCLASS32)
        nm_32(buf);
    return 0;
}

int main(int ac, char **av)
{
    int fd;
    struct stat s;
    char *filename = "a.out";

    if (ac >= 2)
        filename = av[1];
    fd = open(filename, O_RDONLY);
    if (get_stat_file(fd, &s, filename, "nm") == 84) {
        close(fd);
        return 84;
    }
    if (get_elf(fd, s, filename) == 84) {
        close(fd);
        return 84;
    }
    close(fd);
    return (0);
}