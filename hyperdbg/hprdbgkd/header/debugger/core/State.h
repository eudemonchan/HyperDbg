/**
 * @file State.h
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief Model-Specific Registers definitions
 *
 * @version 0.2
 * @date 2022-12-01
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//////////////////////////////////////////////////
//				    Structures					//
//////////////////////////////////////////////////

/**
 * @brief Use to modify Msrs or read MSR values
 *
 */
typedef struct _PROCESSOR_DEBUGGING_MSR_READ_OR_WRITE
{
    UINT64 Msr;   // Msr (ecx)
    UINT64 Value; // the value to write on msr

} PROCESSOR_DEBUGGING_MSR_READ_OR_WRITE, *PPROCESSOR_DEBUGGING_MSR_READ_OR_WRITE;

/**
 * @brief Use to trace the execution in the case of instrumentation step-in
 * command (i command)
 *
 */
typedef struct _DEBUGGEE_INSTRUMENTATION_STEP_IN_TRACE
{
    UINT16 CsSel; // the cs value to trace the execution modes

} DEBUGGEE_INSTRUMENTATION_STEP_IN_TRACE, *PDEBUGGEE_INSTRUMENTATION_STEP_IN_TRACE;

/**
 * @brief Structure to save the state of adding trace for threads
 * and processes
 *
 */
typedef struct _DEBUGGEE_PROCESS_OR_THREAD_TRACING_DETAILS
{
    BOOLEAN InitialSetProcessChangeEvent;
    BOOLEAN InitialSetThreadChangeEvent;

    BOOLEAN InitialSetByClockInterrupt;

    //
    // For threads
    //
    UINT64  CurrentThreadLocationOnGs;
    BOOLEAN DebugRegisterInterceptionState;
    BOOLEAN InterceptClockInterruptsForThreadChange;

    //
    // For processes
    //
    BOOLEAN IsWatingForMovCr3VmExits;
    BOOLEAN InterceptClockInterruptsForProcessChange;

} DEBUGGEE_PROCESS_OR_THREAD_TRACING_DETAILS, *PDEBUGGEE_PROCESS_OR_THREAD_TRACING_DETAILS;

/**
 * @brief The structure of storing breakpoints
 *
 */
typedef struct _DEBUGGEE_BP_DESCRIPTOR
{
    UINT64     BreakpointId;
    LIST_ENTRY BreakpointsList;
    BOOLEAN    Enabled;
    UINT64     Address;
    UINT64     PhysAddress;
    UINT32     Pid;
    UINT32     Tid;
    UINT32     Core;
    UINT16     InstructionLength;
    BYTE       PreviousByte;
    BOOLEAN    SetRflagsIFBitOnMtf;
    BOOLEAN    AvoidReApplyBreakpoint;

} DEBUGGEE_BP_DESCRIPTOR, *PDEBUGGEE_BP_DESCRIPTOR;

/**
 * @brief The status of NMI in the kernel debugger
 *
 */
typedef struct _KD_NMI_STATE
{
    volatile BOOLEAN NmiCalledInVmxRootRelatedToHaltDebuggee;
    volatile BOOLEAN WaitingToBeLocked;

} KD_NMI_STATE, *PKD_NMI_STATE;

/**
 * @brief Saves the debugger state
 * @details Each logical processor contains one of this structure which describes about the
 * state of debuggers, flags, etc.
 *
 */
typedef struct _PROCESSOR_DEBUGGING_STATE
{
    volatile LONG                              Lock;
    volatile BOOLEAN                           MainDebuggingCore;
    GUEST_REGS *                               Regs;
    UINT32                                     CoreId;
    BOOLEAN                                    ShortCircuitingEvent;
    BOOLEAN                                    WaitForStepTrap;
    PROCESSOR_DEBUGGING_MSR_READ_OR_WRITE      MsrState;
    PDEBUGGEE_BP_DESCRIPTOR                    SoftwareBreakpointState;
    DEBUGGEE_INSTRUMENTATION_STEP_IN_TRACE     InstrumentationStepInTrace;
    BOOLEAN                                    DisableTrapFlagOnContinue;
    BOOLEAN                                    DoNotNmiNotifyOtherCoresByThisCore;
    DEBUGGEE_PROCESS_OR_THREAD_TRACING_DETAILS ThreadOrProcessTracingDetails;
    KD_NMI_STATE                               NmiState;
    BOOLEAN                                    BreakStarterCore;
    UINT16                                     InstructionLengthHint;
    UINT64                                     HardwareDebugRegisterForStepping;
    UINT64 *                                   ScriptEngineCoreSpecificLocalVariable;
    UINT64 *                                   ScriptEngineCoreSpecificTempVariable;
    PKDPC                                      KdDpcObject;                       // DPC object to be used in kernel debugger
    CHAR                                       KdRecvBuffer[MaxSerialPacketSize]; // Used for debugging buffers (receiving buffers from serial devices)

} PROCESSOR_DEBUGGING_STATE, PPROCESSOR_DEBUGGING_STATE;
