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
 * ---------------------------------------------------------------------
 */ 
/*
 * Include files
 */
#include "zhpl.h"

#ifndef HPL_ztrsm

#ifdef HPL_CALL_VSIPL

#ifdef STDC_HEADERS
static void HPL_ztrsmLLNN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLLNN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iaik, ibij, ibkj, j, jak, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, ibij= jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = 0, jak  = 0, ibkj = jbj; k < M; k++, jak += LDA, ibkj += 1 )
      {
         B[ibkj] /= A[k+jak];
         for( i = k+1,    iaik  = k+1+jak, ibij  = k+1+jbj;
              i < M; i++, iaik +=1,        ibij += 1 )
         { B[ibij] -= B[ibkj] * A[iaik]; }
      }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsmLLNU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLLNU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iaik, ibij, ibkj, j, jak, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, ibij= jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = 0, jak  = 0, ibkj = jbj; k < M; k++, jak += LDA, ibkj += 1 )
      {
         for( i = k+1,    iaik  = k+1+jak, ibij  = k+1+jbj;
              i < M; i++, iaik +=1,        ibij += 1 )
         { B[ibij] -= B[ibkj] * A[iaik]; }
      }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsmLLTN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLLTN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iaki, ibij, ibkj, j, jai, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = M-1,     jai  = (M-1)*LDA, ibij  = M-1+jbj;
           i >= 0; i--, jai -= LDA,       ibij -= 1 )
      {
         t0 = ALPHA * B[ibij];
         for( k = i+1,    iaki  = i+1+jai, ibkj  = i+1+jbj;
              k < M; k++, iaki += 1,       ibkj += 1 )
         { t0 -= A[iaki] * B[ibkj]; }
         t0 /= A[i+jai];
         B[ibij] = t0;
      }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsmLLTU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLLTU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iaki, ibij, ibkj, j, jai, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = M-1,     jai  = (M-1)*LDA, ibij  = M-1+jbj;
           i >= 0; i--, jai -= LDA,       ibij -= 1 )
      {
         t0 = ALPHA * B[ibij];
         for( k = i+1,    iaki  = i+1+jai, ibkj  = i+1+jbj;
              k < M; k++, iaki += 1,       ibkj += 1 )
         { t0 -= A[iaki] * B[ibkj]; }
         B[ibij] = t0;
      }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsmLUNN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLUNN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iaik, ibij, ibkj, j, jak, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = M-1,     jak  = (M-1)*LDA, ibkj  = M-1+jbj;
           k >= 0; k--, jak -= LDA,       ibkj -= 1 )
      {
         B[ibkj] /= A[k+jak];
         for( i = 0,      iaik  = jak, ibij  = jbj;
              i < k; i++, iaik += 1,   ibij += 1 )
         { B[ibij] -= B[ibkj] * A[iaik]; }
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmLUNU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLUNU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iaik, ibij, ibkj, j, jak, jbj, k;

   for( j = 0, jbj = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = M-1,     jak  = (M-1)*LDA, ibkj  = M-1+jbj;
           k >= 0; k--, jak -= LDA,       ibkj -= 1 )
      {
         for( i = 0,      iaik  = jak, ibij  = jbj;
              i < k; i++, iaik += 1,   ibij += 1 )
         { B[ibij] -= B[ibkj] * A[iaik]; }
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmLUTN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLUTN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iaki, ibij, ibkj, j, jai, jbj, k;
   register zcomplex            t0;

   for( j = 0, jbj  = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, jai  = 0, ibij = jbj; i < M; i++, jai += LDA, ibij += 1 )
      {
         t0 = ALPHA * B[ibij];
         for( k = 0, iaki = jai, ibkj = jbj; k < i; k++, iaki += 1, ibkj += 1 )
         { t0 -= A[iaki] * B[ibkj]; }
         t0 /= A[i+jai];
         B[ibij] = t0;
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmLUTU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmLUTU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iaki, ibij, ibkj, j, jai, jbj, k;

   for( j = 0, jbj  = 0; j < N; j++, jbj += LDB )
   {
      for( i = 0, jai  = 0, ibij = jbj; i < M; i++, jai += LDA, ibij += 1 )
      {
         t0 = ALPHA * B[ibij];
         for( k = 0, iaki = jai, ibkj = jbj; k < i; k++, iaki += 1, ibkj += 1 )
         { t0 -= A[iaki] * B[ibkj]; }
         B[ibij] = t0;
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRLNN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRLNN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

   for( j = N-1,      jaj  = (N-1)*LDA, jbj  = (N-1)*LDB;
        j >= 0;  j--, jaj -= LDA,       jbj -= LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = j+1,    iakj  = j+1+jaj, jbk  = (j+1)*LDB;
           k < N; k++, iakj += 1,       jbk += LDB )
      {
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= A[iakj] * B[ibik]; }
      }
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] /= A[j+jaj]; }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRLNU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRLNU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

   for( j = N-1,      jaj  = (N-1)*LDA, jbj  = (N-1)*LDB;
        j >= 0;  j--, jaj -= LDA,       jbj -= LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = j+1,    iakj  = j+1+jaj, jbk  = (j+1)*LDB;
           k < N; k++, iakj += 1,       jbk += LDB )
      {
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= A[iakj] * B[ibik]; }
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRLTN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRLTN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

   for( k = 0, jak = 0, jbk = 0; k < N; k++, jak += LDA, jbk += LDB )
   {
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] /= A[k+jak]; }
      for( j = k+1,    iajk  = (k+1)+jak, jbj  = (k+1)*LDB;
           j < N; j++, iajk += 1,         jbj += LDB )
      {
         t0 = A[iajk];
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= t0 * B[ibik]; }
      }
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] *= ALPHA; }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRLTU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRLTU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

   for( k = 0, jak = 0, jbk = 0; k < N; k++, jak += LDA, jbk += LDB )
   {
      for( j = k+1,    iajk  = (k+1)+jak, jbj  = (k+1)*LDB;
           j < N; j++, iajk += 1,         jbj += LDB )
      {
         t0 = A[iajk];
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= t0 * B[ibik]; }
      }
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] *= ALPHA; }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRUNN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRUNN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

   for( j = 0, jaj = 0, jbj = 0; j < N; j++, jaj += LDA, jbj += LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = 0, iakj = jaj, jbk = 0; k < j; k++, iakj += 1, jbk += LDB )
      {
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= A[iakj] * B[ibik]; }
      }
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] /= A[j+jaj]; }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRUNU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRUNU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   int                        i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

   for( j = 0, jaj = 0, jbj = 0; j < N; j++, jaj += LDA, jbj += LDB )
   {
      for( i = 0, ibij = jbj; i < M; i++, ibij += 1 ) { B[ibij] *= ALPHA; }
      for( k = 0, iakj = jaj, jbk = 0; k < j; k++, iakj += 1, jbk += LDB )
      {
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= A[iakj] * B[ibik]; }
      }
   }
}


#ifdef STDC_HEADERS
static void HPL_ztrsmRUTN
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRUTN( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

   for( k = N-1,     jak  = (N-1)*LDA, jbk  = (N-1)*LDB;
        k >= 0; k--, jak -= LDA,       jbk -= LDB )
   {
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] /= A[k+jak]; }
      for( j = 0, iajk = jak, jbj = 0; j < k; j++, iajk += 1, jbj += LDB )
      {
         t0 = A[iajk];
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= t0 * B[ibik]; }
      }
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] *= ALPHA; }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsmRUTU
(
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsmRUTU( M, N, ALPHA, A, LDA, B, LDB )
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{
   register zcomplex            t0;
   int                        i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

   for( k = N-1,     jak  = (N-1)*LDA, jbk  = (N-1)*LDB;
        k >= 0; k--, jak -= LDA,       jbk -= LDB )
   {
      for( j = 0, iajk = jak, jbj = 0; j < k; j++, iajk += 1, jbj += LDB )
      {
         t0 = A[iajk];
         for( i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1 )
         { B[ibij] -= t0 * B[ibik]; }
      }
      for( i = 0, ibik = jbk; i < M; i++, ibik += 1 ) { B[ibik] *= ALPHA; }
   }
}

#ifdef STDC_HEADERS
static void HPL_ztrsm0
(
   const enum HPL_SIDE        SIDE,
   const enum HPL_UPLO        UPLO,
   const enum HPL_TRANS       TRANS,
   const enum HPL_DIAG        DIAG,
   const int                  M,
   const int                  N,
   const zcomplex               ALPHA,
   const zcomplex               * A,
   const int                  LDA,
   zcomplex                     * B,
   const int                  LDB
)
#else
static void HPL_ztrsm0( SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB )
   const enum HPL_SIDE        SIDE;
   const enum HPL_UPLO        UPLO;
   const enum HPL_TRANS       TRANS;
   const enum HPL_DIAG        DIAG;
   const int                  LDA, LDB, M, N;
   const zcomplex               ALPHA;
   const zcomplex               * A;
   zcomplex                     * B;
#endif
{ 
   int                        i, j;

   if( ( M == 0 ) || ( N == 0 ) ) return;
 
   if( ALPHA == HPL_rzero )
   {
      for( j = 0; j < N; j++ )
      {  for( i = 0; i < M; i++ ) *(B+i+j*LDB) = HPL_rzero; }
      return;
   }

   if( SIDE == HplLeft )
   {
      if( UPLO == HplUpper )
      {
         if( TRANS == HplNoTrans )
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmLUNN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmLUNU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
         else
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmLUTN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmLUTU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
      }
      else
      {
         if( TRANS == HplNoTrans )
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmLLNN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmLLNU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
         else
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmLLTN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmLLTU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
      }
   }
   else
   {
      if( UPLO == HplUpper )
      {
         if( TRANS == HplNoTrans )
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmRUNN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmRUNU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
         else
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmRUTN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmRUTU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
      }
      else
      {
         if( TRANS == HplNoTrans )
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmRLNN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmRLNU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
         else
         {
            if( DIAG == HplNonUnit )
            {      HPL_ztrsmRLTN( M, N, ALPHA, A, LDA, B, LDB ); }
            else { HPL_ztrsmRLTU( M, N, ALPHA, A, LDA, B, LDB ); }
         }
      }
   }
}

#endif

#ifdef STDC_HEADERS
void HPL_ztrsm
(
   const enum HPL_ORDER             ORDER,
   const enum HPL_SIDE              SIDE,
   const enum HPL_UPLO              UPLO,
   const enum HPL_TRANS             TRANS,
   const enum HPL_DIAG              DIAG,
   const int                        M,
   const int                        N,
   const zcomplex                     ALPHA,
   const zcomplex *                   A,
   const int                        LDA,
   zcomplex *                         B,
   const int                        LDB
)
#else
void HPL_ztrsm
( ORDER, SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB )
   const enum HPL_ORDER             ORDER;
   const enum HPL_SIDE              SIDE;
   const enum HPL_UPLO              UPLO;
   const enum HPL_TRANS             TRANS;
   const enum HPL_DIAG              DIAG;
   const int                        M;
   const int                        N;
   const zcomplex                     ALPHA;
   const zcomplex *                   A;
   const int                        LDA;
   zcomplex *                         B;
   const int                        LDB;
#endif
{
/* 
 * Purpose
 * =======
 *
 * HPL_ztrsm solves one of the matrix equations
 *  
 *    op( A ) * X = alpha * B,   or  X * op( A ) = alpha * B,
 *  
 * where alpha is a scalar, X and B are m by n matrices, A is a unit, or
 * non-unit, upper or lower triangular matrix and op(A) is one of
 *  
 *    op( A ) = A   or   op( A ) = A^T.
 *  
 * The matrix X is overwritten on B.
 *  
 * No test for  singularity  or  near-singularity  is included  in  this
 * routine. Such tests must be performed before calling this routine.
 *
 * Arguments
 * =========
 *
 * ORDER   (local input)                 const enum HPL_ORDER
 *         On entry, ORDER  specifies the storage format of the operands
 *         as follows:                                                  
 *            ORDER = HplRowMajor,                                      
 *            ORDER = HplColumnMajor.                                   
 *
 * SIDE    (local input)                 const enum HPL_SIDE
 *         On entry, SIDE  specifies  whether  op(A) appears on the left
 *         or right of X as follows:
 *            SIDE==HplLeft    op( A ) * X = alpha * B,
 *            SIDE==HplRight   X * op( A ) = alpha * B.
 *
 * UPLO    (local input)                 const enum HPL_UPLO
 *         On  entry,   UPLO   specifies  whether  the  upper  or  lower
 *         triangular  part  of the array  A  is to be referenced.  When
 *         UPLO==HplUpper, only  the upper triangular part of A is to be
 *         referenced, otherwise only the lower triangular part of A is 
 *         to be referenced. 
 *
 * TRANS   (local input)                 const enum HPL_TRANS
 *         On entry, TRANSA  specifies the form of  op(A)  to be used in
 *         the matrix-matrix operation follows:                         
 *            TRANSA==HplNoTrans    : op( A ) = A,                     
 *            TRANSA==HplTrans      : op( A ) = A^T,                   
 *            TRANSA==HplConjTrans  : op( A ) = A^T.                   
 *
 * DIAG    (local input)                 const enum HPL_DIAG
 *         On entry,  DIAG  specifies  whether  A  is unit triangular or
 *         not. When DIAG==HplUnit,  A is assumed to be unit triangular,
 *         and otherwise, A is not assumed to be unit triangular.
 *
 * M       (local input)                 const int
 *         On entry,  M  specifies  the number of rows of the  matrix B.
 *         M must be at least zero.
 *
 * N       (local input)                 const int
 *         On entry, N  specifies the number of columns of the matrix B.
 *         N must be at least zero.
 *
 * ALPHA   (local input)                 const zcomplex
 *         On entry, ALPHA specifies the scalar alpha.   When  ALPHA  is
 *         supplied  as  zero then the elements of the matrix B need not
 *         be set on input.
 *
 * A       (local input)                 const zcomplex *
 *         On entry,  A  points  to an array of size equal to or greater
 *         than LDA * k,  where  k is m  when  SIDE==HplLeft  and  is  n
 *         otherwise.  Before  entry  with  UPLO==HplUpper,  the leading
 *         k by k upper triangular  part of the array A must contain the
 *         upper triangular  matrix and the  strictly  lower  triangular
 *         part of A is not referenced.  When  UPLO==HplLower on  entry,
 *         the  leading k by k lower triangular part of the array A must
 *         contain the lower triangular matrix  and  the  strictly upper
 *         triangular part of A is not referenced.
 *          
 *         Note that  when  DIAG==HplUnit,  the  diagonal elements of  A
 *         not referenced  either,  but are assumed to be unity.
 *
 * LDA     (local input)                 const int
 *         On entry,  LDA  specifies  the  leading  dimension  of  A  as
 *         declared  in  the  calling  (sub) program.  LDA  must  be  at
 *         least MAX(1,m) when SIDE==HplLeft, and MAX(1,n) otherwise.
 *
 * B       (local input/output)          zcomplex *
 *         On entry,  B  points  to an array of size equal to or greater
 *         than LDB * n.  Before entry, the leading  m by n  part of the
 *         array B must contain the matrix  B, except when beta is zero,
 *         in which case B need not be set on entry.  On exit, the array
 *         B is overwritten by the m by n solution matrix.
 *
 * LDB     (local input)                 const int
 *         On entry,  LDB  specifies  the  leading  dimension  of  B  as
 *         declared  in  the  calling  (sub) program.  LDB  must  be  at
 *         least MAX(1,m).
 *
 * ---------------------------------------------------------------------
 */ 
#ifdef HPL_CALL_CBLAS
   cblas_ztrsm( ORDER, SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB );
#endif
#ifdef HPL_CALL_VSIPL
   if( ORDER == HplColumnMajor )
   {
      HPL_ztrsm0( SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB );
   }
   else
   {
      HPL_ztrsm0( ( SIDE == HplRight ? HplLeft  : HplRight ),
                  ( UPLO == HplLower ? HplUpper : HplLower ),
                  TRANS, DIAG, N, M, ALPHA, A, LDA, B, LDB );
   }
#endif
#ifdef HPL_CALL_FBLAS
   zcomplex                    alpha = ALPHA;
#ifdef StringSunStyle
#if defined( HPL_USE_F77_INTEGER_DEF )
   F77_INTEGER               IONE = 1;
#else
   int                       IONE = 1;
#endif
#endif
#ifdef StringStructVal
   F77_CHAR                  fside;
   F77_CHAR                  fuplo;
   F77_CHAR                  ftran;
   F77_CHAR                  fdiag;
#endif
#ifdef StringStructPtr
   F77_CHAR                  fside;
   F77_CHAR                  fuplo;
   F77_CHAR                  ftran;
   F77_CHAR                  fdiag;
#endif
#ifdef StringCrayStyle
   F77_CHAR                  fside;
   F77_CHAR                  fuplo;
   F77_CHAR                  ftran;
   F77_CHAR                  fdiag;
#endif
#ifdef HPL_USE_F77_INTEGER_DEF
   const F77_INTEGER         F77M   = M,   F77N   = N,
                             F77lda = LDA, F77ldb = LDB;
#else
#define  F77M                M
#define  F77N                N
#define  F77lda              LDA
#define  F77ldb              LDB
#endif
   char                      cside, cuplo, ctran, cdiag;

   if(      TRANS == HplNoTrans ) ctran = 'N';
   else if( TRANS == HplTrans   ) ctran = 'T';
   else                           ctran = 'C';
   cdiag = ( DIAG == HplUnit  ? 'U' : 'N' );

   if( ORDER == HplColumnMajor )
   {
      cside = ( SIDE == HplRight ? 'R' : 'L' );
      cuplo = ( UPLO == HplLower ? 'L' : 'U' );
#ifdef StringSunStyle
      F77ztrsm( &cside, &cuplo, &ctran, &cdiag, &F77M, &F77N, &alpha,
                A, &F77lda, B, &F77ldb, IONE, IONE, IONE, IONE );
#endif
#ifdef StringCrayStyle
      fside = HPL_C2F_CHAR( cside ); fuplo = HPL_C2F_CHAR( cuplo );
      ftran = HPL_C2F_CHAR( ctran ); fdiag = HPL_C2F_CHAR( cdiag );
      F77ztrsm( fside,  fuplo,  ftran,  fdiag,  &F77M, &F77N, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
#ifdef StringStructVal
      fside.len = 1; fside.cp = &cside; fuplo.len = 1; fuplo.cp = &cuplo;
      ftran.len = 1; ftran.cp = &ctran; fdiag.len = 1; fdiag.cp = &cdiag;
      F77ztrsm( fside,  fuplo,  ftran,  fdiag,  &F77M, &F77N, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
#ifdef StringStructPtr
      fside.len = 1; fside.cp = &cside; fuplo.len = 1; fuplo.cp = &cuplo;
      ftran.len = 1; ftran.cp = &ctran; fdiag.len = 1; fdiag.cp = &cdiag;
      F77ztrsm( &fside, &fuplo, &ftran, &fdiag, &F77M, &F77N, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
   }
   else
   {
      cside = ( SIDE == HplRight ? 'L' : 'R' );
      cuplo = ( UPLO == HplLower ? 'U' : 'L' );
#ifdef StringSunStyle
      F77ztrsm( &cside, &cuplo, &ctran, &cdiag, &F77N, &F77M, &alpha,
                A, &F77lda, B, &F77ldb, IONE, IONE, IONE, IONE );
#endif
#ifdef StringCrayStyle
      fside = HPL_C2F_CHAR( cside ); fuplo = HPL_C2F_CHAR( cuplo );
      ftran = HPL_C2F_CHAR( ctran ); fdiag = HPL_C2F_CHAR( cdiag );
      F77ztrsm( fside,  fuplo,  ftran,  fdiag,  &F77N, &F77M, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
#ifdef StringStructVal
      fside.len = 1; fside.cp = &cside; fuplo.len = 1; fuplo.cp = &cuplo;
      ftran.len = 1; ftran.cp = &ctran; fdiag.len = 1; fdiag.cp = &cdiag;
      F77ztrsm( fside,  fuplo,  ftran,  fdiag,  &F77N, &F77M, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
#ifdef StringStructPtr
      fside.len = 1; fside.cp = &cside; fuplo.len = 1; fuplo.cp = &cuplo;
      ftran.len = 1; ftran.cp = &ctran; fdiag.len = 1; fdiag.cp = &cdiag;
      F77ztrsm( &fside, &fuplo, &ftran, &fdiag, &F77N, &F77M, &alpha,
                A, &F77lda, B, &F77ldb );
#endif
   }
#endif
/*
 * End of HPL_ztrsm
 */
}

#endif
