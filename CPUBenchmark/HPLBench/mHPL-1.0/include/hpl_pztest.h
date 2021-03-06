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
#ifndef HPL_PTEST_H
#define HPL_PTEST_H
/*
 * ---------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------
 */
#include "hpl_zmisc.h"
#include "hpl_zblas.h"
#include "hpl_zauxil.h"
#include "hpl_zgesv.h"

#include "hpl_pzmisc.h"
#include "hpl_pzauxil.h"
#include "hpl_zpanel.h"
#include "hpl_pzgesv.h"

#include "hpl_ptimer.h"
#include "hpl_pzmatgen.h"
/*
 * ---------------------------------------------------------------------
 * Data Structures
 * ---------------------------------------------------------------------
 */
typedef struct HPL_S_test
{
   double              epsil;                      /* epsilon machine */
   double              thrsh;                            /* threshold */
   FILE *              outfp;       /* output stream (only in proc 0) */
   int                 kfail;                    /* # of tests failed */
   int                 kpass;                    /* # of tests passed */
   int                 kskip;                   /* # of tests skipped */
   int                 ktest;                /* total number of tests */
} HPL_T_test;

/*
 * ---------------------------------------------------------------------
 * #define macro constants for testing only
 * ---------------------------------------------------------------------
 */
#define    HPL_LINE_MAX         256
#define    HPL_MAX_PARAM         20
#define    HPL_ISEED            100
/*
 * ---------------------------------------------------------------------
 * global timers for timing analysis only
 * ---------------------------------------------------------------------
 */
#ifdef HPL_DETAILED_TIMING
#define    HPL_TIMING_BEG        11 /* timer 0 reserved, used by main */
#define    HPL_TIMING_N           6 /* number of timers defined below */
#define    HPL_TIMING_RPFACT     11 /* starting from here, contiguous */
#define    HPL_TIMING_PFACT      12
#define    HPL_TIMING_MXSWP      13
#define    HPL_TIMING_UPDATE     14
#define    HPL_TIMING_LASWP      15
#define    HPL_TIMING_PTRSV      16
#endif
/*
 * ---------------------------------------------------------------------
 * Function prototypes
 * ---------------------------------------------------------------------
 */
void                             HPL_pzinfo
STDC_ARGS( (
   HPL_T_test *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_ORDER *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_FACT *,
   int *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_FACT *,
   int *,
   HPL_T_TOP *,
   int *,
   int *,
   HPL_T_SWAP *,
   int *,
   int *,
   int *,
   int *,
   int *
) );
void                             HPL_pztest
STDC_ARGS( (
   HPL_T_test *,
   HPL_T_grid *,
   HPL_ZT_palg *,
   const int,
   const int
) );

#endif
/*
 * End of hpl_pztest.h
 */
