/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** main
*/

#include "nm.h"

int check_type_file(uint16_t e_type)
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
    return -1;
}

int main(int ac, char **av)
{
    int fd;
    struct stat s;
    void *buf;
    void *sections;
    Elf64_Ehdr *elf;
    char *filename = "a.out";

    if (ac >= 2)
        filename = av[1];
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("nm: '%s': No such file\n", filename);
        return 84;
    }
    fstat(fd, &s);
    if (S_ISREG(s.st_mode) == 0) {
        printf("nm: Warning: '%s' is a directory\n", filename);
        return 84;
    }
    buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd, 0);
    if (buf != (void *)(-1)) {
        elf = buf;
        if (check_type_file(elf->e_type) == -1) {
            printf("nm: %s: file format not recognized\n", filename);
            return 84;
        }
        printf("e_shnum: %d", elf->e_shnum);
        // printf("mmap(%s) : %08xn%s\n", av[1], buf, buf);
        // printf("Section  Header  Table : addr = %08x, nb = %dn\n",elf ->e_shoff , elf ->e_shnum);
    } else
        perror("mmap");
    close(fd);
    return (84);
}