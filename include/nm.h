/*
** EPITECH PROJECT, 2021
** B-PSU-400-PAR-4-1-nmobjdump-tom.rives
** File description:
** nm
*/

#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef NM_H_
#define NM_H_

char get_sym_type64(Elf64_Sym symtab, Elf64_Shdr *sections);
void print_symtab64(Elf64_Shdr *sections, char *str, Elf64_Sym *symtab, int size);
void nm_64(void *buf);

int get_elf(int fd, struct stat s, char *filename);
int get_stat_file(int fd, struct stat *s, char *filename, char *exec);
int check_type_file(char *buf, char *filename, char *exec);
int check_arch(char *buf);

char get_sym_type32(Elf32_Sym symtab, Elf32_Shdr *sections);
void print_symtab32(Elf32_Shdr *sections, char *str, Elf32_Sym *symtab, int size);
void nm_32(void *buf);

#endif /* !NM_H_ */
