/* 
 * -- High Performance Computing Linpack Benchmark (HPL)                
 *    HPL - 1.0a - January 20, 2004                          
 *    Antoine P. Petitet                                                
 *    University of Tennessee, Knoxville                                
 *    Innovative Computing Laboratories                                 
 *    (C) Copyright 2000-2004 All Rights Reserved                       
 *                                                                      
 * -- Copyright notice and Licensing terms:                             
 *                                                                      
 * Redistribution  and  use in  source and binary forms, with or without
 * modification, are  permitted provided  that the following  conditions
 * are met:                                                             
 *                                                                      
 * 1. Redistributions  of  source  code  must retain the above copyright
 * notice, this list of conditions and the following disclaimer.        
 *                                                                      
 * 2. Redistributions in binary form must reproduce  the above copyright
 * notice, this list of conditions,  and the following disclaimer in the
 * documentation and/or other materials provided with the distribution. 
 *                                                                      
 * 3. All  advertising  materials  mentioning  features  or  use of this
 * software must display the following acknowledgement:                 
 * This  product  includes  software  developed  at  the  University  of
 * Tennessee, Knoxville, Innovative Computing Laboratories.             
 *                                                                      
 * 4. The name of the  University,  the name of the  Laboratory,  or the
 * names  of  its  contributors  may  not  be used to endorse or promote
 * products  derived   from   this  software  without  specific  written
 * permission.                                                          
 *                                                                      
 * -- Disclaimer:                                                       
 *                                                                      
 * THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
 * OR  CONTRIBUTORS  BE  LIABLE FOR ANY  DIRECT,  INDIRECT,  INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES  (INCLUDING,  BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT,  STRICT LIABILITY,  OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */ 
#ifndef HPL_MATGEN_H
#define HPL_MATGEN_H
/*
 * ---------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------
 */
#include "hpl_zmisc.h"
#include "hpl_zblas.h"
#include "hpl_zauxil.h"
/*
 * ---------------------------------------------------------------------
 * #define macro constants
 * ---------------------------------------------------------------------
 */
#define    HPL_MULT0         20077
#define    HPL_MULT1         16838
#define    HPL_IADD0         12345
#define    HPL_IADD1         0
#define    HPL_DIVFAC        2147483648.0
#define    HPL_POW16         65536.0
#define    HPL_HALF          0.5
/*
 * ---------------------------------------------------------------------
 * Function prototypes
 * ---------------------------------------------------------------------
 */
void                             HPL_zmatgen
STDC_ARGS( (
   const int,
   const int,
   zcomplex *,
   const int,
   const int
) );
void                             HPL_lmul
STDC_ARGS( (
   int *,
   int *,
   int *
) );
void                             HPL_ladd
STDC_ARGS( (
   int *,
   int *,
   int *
) );
void                             HPL_zjumpm
STDC_ARGS( (
   const int,
   int *,
   int *,
   int *,
   int *,
   int *,
   int *
) );
void                             HPL_setran
STDC_ARGS( (
   const int,
   int *
) );
void                             HPL_jumpit
STDC_ARGS( (
   int *,
   int *,
   int *,
   int *
) );
zcomplex HPL_zrand STDC_ARGS( ( void ) );

#endif
/*
 * End of hpl_zmatgen.h
 */
