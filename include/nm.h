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

char get_sym_type(Elf64_Sym symtab, Elf64_Shdr *sections);
int get_elf(int fd, struct stat s, char *filename);
int get_stat_file(int fd, struct stat *s, char *filename, char *exec);
int check_type_file(char *buf, char *filename, char *exec);
int check_arch(char *buf);
void print_symtab(Elf64_Shdr *sections, char *str, Elf64_Sym *symtab, int size);
void nm_64(void *buf);

#endif /* !NM_H_ */
