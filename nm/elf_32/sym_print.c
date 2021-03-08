/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** sym_print
*/

#include "nm.h"

void print_symtab32(Elf32_Shdr *sections, char *str, Elf32_Sym *symtab, int size)
{
    char c;

    for (int i = 0; i < size; i++) {
        c = get_sym_type32(symtab[i], sections);
        if (symtab[i].st_name && symtab->st_info != STT_FILE && c != 'a') {
            if (symtab[i].st_value != 0)
                printf("%016x %c %s\n", symtab[i].st_value,
                get_sym_type32(symtab[i], sections), &str[symtab[i].st_name]);
            else
                printf("%-16.16s %c %s\n", " ",
                get_sym_type32(symtab[i], sections), &str[symtab[i].st_name]);
        }
    }
}

void nm_32(void *buf)
{
    Elf32_Ehdr *elf;
    Elf32_Shdr *sections;
    Elf32_Sym *symtab;
    char *str = NULL;
    int size = 0;

    elf = (Elf32_Ehdr *)(buf);
    sections = (Elf32_Shdr *)(buf + elf->e_shoff);
    for (int i = 0; i < elf->e_shnum; i++) {
        if (sections[i].sh_type == SHT_SYMTAB) {
            symtab = (Elf32_Sym *)(buf + sections[i].sh_offset);
            str = (char *)(buf + sections[sections[i].sh_link].sh_offset);
            size = sections[i].sh_size / sections[i].sh_entsize;
            break;
        }
    }
    print_symtab32(sections, str, symtab, size);
}