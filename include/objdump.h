/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** objdump
*/

#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <byteswap.h>

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#define BFD_NO_FLAGS 0x00
#define HAS_RELOC 0x01
#define EXEC_P 0x02
#define HAS_LINENO 0x04
#define HAS_DEBUG 0x08
#define HAS_SYMS 0x10
#define HAS_LOCALS 0x20
#define DYNAMIC 0x40
#define WP_TEXT 0x80
#define D_PAGED 0x100

int get_stat_file(int fd, struct stat *s, char *filename, char *exec);
int check_type_file(char *buf, char *filename, char *exec);
int check_arch(char *buf);
int get_elf(int fd, struct stat s, char *filename);
void print_flag(int flags);

void objdump_64(void *buf, char *filename);
void objdump_32(void *buf, char *filename);

int check_has_sht32(Elf32_Ehdr *elf, void *buf, unsigned int sht);
int check_has_sht64(Elf64_Ehdr *elf, void *buf, unsigned int sht);
void print_header64(char *filename, Elf64_Ehdr *elf, void *buf);
void print_header32(char *filename, Elf32_Ehdr *elf, void *buf);
void print_adress(int *adr, int *len_adr);
void print_section_content64(Elf64_Shdr section, void *elf);
void print_section_content32(Elf32_Shdr section, void *elf);
int get_flag32(Elf32_Ehdr *elf, void *buf);
int get_flag64(Elf64_Ehdr *elf, void *buf);

#endif /* !OBJDUMP_H_ */
