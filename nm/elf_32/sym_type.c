/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** sym_type
*/

#include "nm.h"

static char get_sym_type_shndx32(Elf32_Sym symtab, Elf32_Shdr *sections)
{
    if (symtab.st_shndx == SHN_ABS)
        return 'A';
    if (symtab.st_shndx == SHN_COMMON)
        return 'C';
    if (sections[symtab.st_shndx].sh_type == SHT_NOBITS &&
    sections[symtab.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'B';
    if (sections[symtab.st_shndx].sh_type == SHT_PROGBITS &&
    sections[symtab.st_shndx].sh_flags == SHF_ALLOC)
        return 'R';
    if (sections[symtab.st_shndx].sh_type == SHT_PROGBITS &&
    sections[symtab.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'D';
    if (sections[symtab.st_shndx].sh_type == SHT_PROGBITS &&
    sections[symtab.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        return 'T';
    if (sections[symtab.st_shndx].sh_type == SHT_DYNAMIC)
        return 'D';
    return '?';
}

static char get_sym_type_st_bind32(Elf32_Sym symtab)
{
    if (ELF32_ST_BIND(symtab.st_info) == STB_GNU_UNIQUE)
        return 'u';
    if (ELF32_ST_BIND(symtab.st_info) == STB_WEAK) {
        if (symtab.st_shndx == SHN_UNDEF)
            return 'w';
        return 'W';
    }
    if (ELF32_ST_BIND(symtab.st_info) == STB_WEAK &&
    ELF32_ST_TYPE(symtab.st_info) == STT_OBJECT) {
        if (symtab.st_shndx == SHN_UNDEF)
            return 'v';
        return 'V';
    }
    if (symtab.st_shndx == SHN_UNDEF)
        return 'U';
    return '?';
}

char get_sym_type32(Elf32_Sym symtab, Elf32_Shdr *sections)
{
    char c = get_sym_type_st_bind32(symtab);

    if (c == '?')
        c = get_sym_type_shndx32(symtab, sections);
    if (ELF32_ST_BIND(symtab.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}