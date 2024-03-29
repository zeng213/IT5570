/***********************************************************************/
/*  This file is part of the C51 Compiler package                      */
/*  Copyright KEIL ELEKTRONIK GmbH 1990 - 2002                         */
/***********************************************************************/
/*                                                                     */
/*  PUTCHAR.C:  This routine is the general character output of C51.   */
/*  You may add this file to a uVision2 project.                       */
/*                                                                     */
/*  To translate this file use C51 with the following invocation:      */
/*     C51 PUTCHAR.C <memory model>                                    */
/*                                                                     */
/*  To link the modified PUTCHAR.OBJ file to your application use the  */
/*  following Lx51 invocation:                                         */
/*     Lx51 <your object file list>, PUTCHAR.OBJ <controls>            */
/*                                                                     */
/***********************************************************************/
#include <CORE_INCLUDE.H>
#include <OEM_INCLUDE.H>

#ifdef UART1_DEBUG
#if (UART1_DEBUG != FALSE)
/*
 * putchar (basic version): expands '\n' into CR LF
 */
char putchar (char c)  {
  if (c == '\n')  {
    while((UART1_LSR & BIT5) == 0);
    UART1_RBR = 0x0d;                         /* output CR  */
  }
    while((UART1_LSR & BIT5) == 0);
  return (UART1_RBR = c);
}
#endif
#endif

#ifdef UART2_DEBUG
#if (UART2_DEBUG != FALSE)
/*
 * putchar (basic version): expands '\n' into CR LF
 */
char putchar (char c)  {
  if (c == '\n')  {
    while((UART2_LSR & BIT5) == 0);
    UART2_RBR = 0x0d;                         /* output CR  */
  }
    while((UART2_LSR & BIT5) == 0);
  return (UART2_RBR = c);
}
#endif
#endif
