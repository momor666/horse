/* Copyright (c) 2016-2017, Eder Leao Fernandes
 * All rights reserved.
 *
 * The contents of this file are subject to the license defined in
 * file 'doc/LICENSE'.
 *
 *
 * Author: Eder Leao Fernandes <e.leao@qmul.ac.uk>
 */

#ifndef UTIL_H
#define UTIL_H 1

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void out_of_memory(void);
void *xmalloc(int size);
void *xrealloc(void *v, int size);


#endif