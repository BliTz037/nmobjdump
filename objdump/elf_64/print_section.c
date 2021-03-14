/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** print_section
*/

#include "objdump.h"

void print_adress(int *adr, int *len_adr)
{
    int i = 0;

    for (; i < 4 && &adr[i] < len_adr; i++)
        printf(" %08x", bswap_32(adr[i]));
    for (; i < 4; i++)
        printf(" %-8.8s", " ");
    printf("  ");
}

void print_section_content64(Elf64_Shdr section, void *elf)
{
    int *adr = (int *)(elf + section.sh_offset);
    char *str = (char *)(elf + section.sh_offset);
    int *len_adr = (int *)(elf + section.sh_offset + section.sh_size);
    char *len_str = (char *)(elf + section.sh_offset + section.sh_size);
    unsigned long len_addr = section.sh_addr + section.sh_size;

    for (unsigned long n = section.sh_addr; n < len_addr; n += 16) {
        printf(" %lx", n);
        print_adress(adr, len_adr);
        for (int c = 0; c < 16 && &str[c] < len_str; c++)
            if (isprint(str[c]))
                printf("%c", str[c]);
            else
                printf(".");
        printf("\n");
        adr += 4;
        str += 16;
    }
}