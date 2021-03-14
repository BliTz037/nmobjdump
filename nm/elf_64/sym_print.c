/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** sym_print
*/

#include "nm.h"

static int compare_name(const void *a, const void *b)
{
    char *str_a = ((symbole_t *)(a))->str;
    char *str_b = ((symbole_t *)(b))->str;

    for (; *str_a == '_'; str_a++);
    for (; *str_b == '_'; str_b++);
    return (strcasecmp(str_a, str_b));
}

void print_symtab64(symbole_t *s, int size)
{
    for (int i = 0; i != size; i++) {
        if (s[i].value != 0)
            printf("%016lx %c %s\n", s[i].value, s[i].type, s[i].str);
        else
            printf("%-16.16s %c %s\n", " ", s[i].type, s[i].str);
    }
}

void symtab64(Elf64_Shdr *sections, char *str, Elf64_Sym *symtab, int size)
{
    char c;
    int b = 0;
    symbole_t *s = NULL;

    for (int i = 0; i < size; i++) {
        c = get_sym_type64(symtab[i], sections);
        if (symtab[i].st_name && symtab->st_info != STT_FILE && c != 'a') {
            s = reallocarray(s, b + 1, sizeof(symbole_t));
            s[b].str = &str[symtab[i].st_name];
            s[b].type = c;
            s[b].value = symtab[i].st_value;
            b++;
        }
    }
    qsort(s, b, sizeof(symbole_t), compare_name);
    print_symtab64(s, b);
    free(s);
}

void nm_64(void *buf)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(buf);
    Elf64_Shdr *sections = (Elf64_Shdr *)(buf + elf->e_shoff);
    Elf64_Sym *symtab;
    char *str = NULL;
    int size = 0;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (sections[i].sh_type == SHT_SYMTAB) {
            symtab = (Elf64_Sym *)(buf + sections[i].sh_offset);
            str = (char *)(buf + sections[sections[i].sh_link].sh_offset);
            size = sections[i].sh_size / sections[i].sh_entsize;
            break;
        }
    }
    symtab64(sections, str, symtab, size);
}