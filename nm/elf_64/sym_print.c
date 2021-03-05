/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** sym_print
*/

#include "nm.h"

void print_symtab64(Elf64_Shdr *sections, char *str, Elf64_Sym *symtab, int size)
{
    for (int i = 0; i < size; i++) {
        if (symtab[i].st_name && symtab->st_info != STT_FILE) {
            if (symtab[i].st_value != 0)
                printf("%016lx %c %s\n", symtab[i].st_value,
                get_sym_type64(symtab[i], sections), &str[symtab[i].st_name]);
            else
                printf("%-16.16s %c %s\n", " ",
                get_sym_type64(symtab[i], sections), &str[symtab[i].st_name]);
        }
    }
}

void nm_64(void *buf)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *sections;
    Elf64_Sym *symtab;
    char *str = NULL;
    int size = 0;

    elf = (Elf64_Ehdr *)(buf);
    sections = (Elf64_Shdr *)(buf + elf->e_shoff);
    for (int i = 0; i < elf->e_shnum; i++) {
        if (sections[i].sh_type == SHT_SYMTAB) {
            symtab = (Elf64_Sym *)(buf + sections[i].sh_offset);
            str = (char *)(buf + sections[sections[i].sh_link].sh_offset);
            size = sections[i].sh_size / sections[i].sh_entsize;
            break;
        }
    }
    print_symtab64(sections, str, symtab, size);
}