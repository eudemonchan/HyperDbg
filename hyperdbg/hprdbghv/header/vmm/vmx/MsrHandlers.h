/**
 * @file MsrHandlers.h
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief Headers to Handle for MSR-related tasks in VMX-root
 *
 * @version 0.1
 * @date 2021-12-24
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//////////////////////////////////////////////////
//				    Functions					//
//////////////////////////////////////////////////

VOID
MsrHandleRdmsrVmexit(PGUEST_REGS GuestRegs);

VOID
MsrHandleWrmsrVmexit(PGUEST_REGS GuestRegs);

BOOLEAN
MsrHandleSetMsrBitmap(VIRTUAL_MACHINE_STATE * VCpu, UINT64 Msr, BOOLEAN ReadDetection, BOOLEAN WriteDetection);

BOOLEAN
MsrHandleUnSetMsrBitmap(VIRTUAL_MACHINE_STATE * VCpu, UINT64 Msr, BOOLEAN ReadDetection, BOOLEAN WriteDetection);

VOID
MsrHandlePerformMsrBitmapReadChange(VIRTUAL_MACHINE_STATE * VCpu, UINT64 MsrMask);

VOID
MsrHandlePerformMsrBitmapReadReset(VIRTUAL_MACHINE_STATE * VCpu);

VOID
MsrHandlePerformMsrBitmapWriteChange(VIRTUAL_MACHINE_STATE * VCpu, UINT64 MsrMask);

VOID
MsrHandlePerformMsrBitmapWriteReset(VIRTUAL_MACHINE_STATE * VCpu);
