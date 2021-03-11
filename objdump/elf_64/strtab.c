/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** strtab
*/

#include "objdump.h"

int check_has_sht64(Elf64_Ehdr *elf, void *buf, unsigned int sht)
{
    Elf64_Shdr *sections = (Elf64_Shdr *)(buf + elf->e_shoff);

    for (int i = 0; i < elf->e_shnum; i++)
        if (sections[i].sh_type == sht)
            return 1;
    return 0;
}

int get_flag64(Elf64_Ehdr *elf, void *buf)
{
    int flags = 0;

    if (elf->e_type == ET_REL)
        flags |= HAS_RELOC;
    if (elf->e_type == ET_EXEC)
        flags |= EXEC_P;
    if (elf->e_type == ET_DYN)
        flags |= DYNAMIC;
    if (check_has_sht64(elf, buf, SHT_SYMTAB) == 1)
        flags |= HAS_SYMS;
    if (elf->e_phnum > 0)
        flags |= D_PAGED;
    return flags;
}

void print_flag(int flags)
{
    const char *flags_n[] = {"HAS_RELOC", "EXEC_P",
    "HAS_LINENO", "HAS_DEBUG", "HAS_SYMS", "HAS_LOCALS", "DYNAMIC", "D_PAGED"};
    const int flags_v[] = {HAS_RELOC, EXEC_P, HAS_LINENO,
    HAS_DEBUG, HAS_SYMS, HAS_LOCALS, DYNAMIC, D_PAGED};
    int comma = 0;

    for (int i = 0; i != 8; i++) {
        if ((flags & flags_v[i]) == flags_v[i] && comma)
            printf(", ");
        if ((flags & flags_v[i]) == flags_v[i]) {
            printf("%s", flags_n[i]);
            comma = 1;
        }
    }
    if (flags == 0)
        printf("BFD_NO_FLAGS");
    printf("\n");
}

void print_header64(char *filename, Elf64_Ehdr *elf, void *buf)
{
    int flags = get_flag64(elf, buf);

    printf("\n%s:\tfile format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags 0x%08x\n", flags);
    print_flag(flags);
    printf("start address 0x%016lx\n\n", elf->e_entry);
}

void objdump_64(void *buf, char *filename)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(buf);
    Elf64_Shdr *sections = (Elf64_Shdr *)(buf + elf->e_shoff);
    char *str = (char *)(buf + sections[elf->e_shstrndx].sh_offset);

    print_header64(filename, elf, buf);
    for (int i = 0; i != elf->e_shnum; i++) {
        if (sections[i].sh_type != SHT_NOBITS &&
        sections[i].sh_type != SHT_NULL && sections[i].sh_type != SHT_STRTAB &&
        sections[i].sh_type != SHT_SYMTAB) {
            printf("Contents of section %s:\n", &str[sections[i].sh_name]);
            print_section_content64(sections[i], elf);
        }
    }
}