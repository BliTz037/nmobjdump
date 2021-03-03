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
int check_type_file(uint16_t e_type, char *filename);

#endif /* !NM_H_ */
