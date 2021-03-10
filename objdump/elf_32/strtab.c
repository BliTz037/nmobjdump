/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** strtab
*/

#include "objdump.h"

int check_has_sht32(Elf32_Ehdr *elf, void *buf, unsigned int sht)
{
    Elf32_Shdr *sections = (Elf32_Shdr *)(buf + elf->e_shoff);

    for (int i = 0; i < elf->e_shnum; i++)
        if (sections[i].sh_type == sht)
            return 1;
    return 0;
}

int get_flag32(Elf32_Ehdr *elf, void *buf)
{
    int flags = 0;

    if (elf->e_type == ET_REL)
        flags |= HAS_RELOC;
    if (elf->e_type == ET_EXEC)
        flags |= EXEC_P;
    if (elf->e_type == ET_DYN)
        flags |= DYNAMIC;
    if (check_has_sht32(elf, buf, SHT_SYMTAB) == 1)
        flags |= HAS_SYMS;
    if (elf->e_phnum > 0)
        flags |= D_PAGED;
    return flags;
}

void print_header32(char *filename, Elf32_Ehdr *elf, void *buf)
{
    int flags = get_flag32(elf,buf);

    printf("\n%s:\tfile format elf32-i386\n", filename);
    printf("architecture: i386, flags 0x%08x\n", flags);
    print_flag(flags);
    printf("start address 0x%08x\n\n", elf->e_entry);
}

void objdump_32(void *buf, char *filename)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)(buf);
    Elf32_Shdr *sections = (Elf32_Shdr *)(buf + elf->e_shoff);
    char *str = (char *)(buf + sections[elf->e_shstrndx].sh_offset);

    print_header32(filename, elf, buf);
    for (int i = 0; i != elf->e_shnum; i++) {
        if (sections[i].sh_type != SHT_NOBITS &&
        sections[i].sh_type != SHT_NULL && sections[i].sh_type != SHT_STRTAB &&
        sections[i].sh_type != SHT_SYMTAB) {
            printf("Contents of section %s:\n", &str[sections[i].sh_name]);
            print_section_content32(sections[i], elf);
        }
    }
}