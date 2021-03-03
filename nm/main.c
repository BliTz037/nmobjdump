/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** main
*/

#include "nm.h"

int check_type_file(uint16_t e_type, char *filename)
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
    printf("nm: %s: file format not recognized\n", filename);
    return -1;
}

char get_sym_type(Elf64_Sym symtab, Elf64_Shdr *sections)
{
    if (ELF64_ST_BIND(symtab.st_info) == STB_GNU_UNIQUE)
        return 'u';
    return 0;
}

int get_elf(int fd, struct stat s, char *filename)
{
    void *buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    Elf64_Ehdr *elf;
    Elf64_Shdr *sections;
    Elf64_Sym *symtab;
    char *str = NULL;
    int size = 0;

    if (buf == (void *)(-1))
        return 84;
    elf = (Elf64_Ehdr *)(buf);
    if (check_type_file(elf->e_type, filename) == -1)
        return 84;
    sections = (Elf64_Shdr *)(buf + elf->e_shoff);
    for (int i = 0; i < elf->e_shnum; i++) {
        if (sections[i].sh_type == SHT_SYMTAB) {
            symtab = (Elf64_Sym *)(buf + sections[i].sh_offset);
            str = (char *)(buf + sections[sections[i].sh_link].sh_offset);
            size = sections[i].sh_size / sections[i].sh_entsize;
            break;
        }
    }
    for (int i = 0; i < size; i++) {
        if (symtab[i].st_name != 0 && symtab->st_info != STT_FILE) {
            if (symtab[i].st_value != 0)
                printf("%016lx %s\n", symtab[i].st_value, &str[symtab[i].st_name]);
            else
                printf("%-16.16s %s\n", " ", &str[symtab[i].st_name]);
        }
    }
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
    if (fd == -1) {
        printf("nm: '%s': No such file\n", filename);
        return 84;
    }
    fstat(fd, &s);
    if (S_ISREG(s.st_mode) == 0) {
        printf("nm: Warning: '%s' is a directory\n", filename);
        return 84;
    }
    if (get_elf(fd, s, filename) == 84) {
        close(fd);
        return 84;
    }
    close(fd);
    return (0);
}