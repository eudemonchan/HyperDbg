﻿/**
 * @file Debugger.h
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief General debugger headers
 * @details
 * @version 0.1
 * @date 2020-04-14
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//////////////////////////////////////////////////
//              Debugger Internals              //
//////////////////////////////////////////////////

/**
 * @brief debug register for step-over
 */
#define DEBUGGER_DEBUG_REGISTER_FOR_STEP_OVER 0

/**
 * @brief debug register to monitor thread changes
 */
#define DEBUGGER_DEBUG_REGISTER_FOR_THREAD_MANAGEMENT 1

/**
 * @brief debug register get entrypoint of user-mode process
 */
#define DEBUGGER_DEBUG_REGISTER_FOR_USER_MODE_ENTRY_POINT 1

//////////////////////////////////////////////////
//					Structures					//
//////////////////////////////////////////////////

/**
 * @brief List of all the different events
 *
 */
typedef struct _DEBUGGER_CORE_EVENTS
{
    //
    // Warnings : Only list entries should be in this list, nothing else
    //

    //
    // Do not add varialbe to this this list, just LIST_ENTRY is allowed
    //
    LIST_ENTRY HiddenHookReadAndWriteEventsHead;     // HIDDEN_HOOK_READ_AND_WRITE  [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY HiddenHookReadEventsHead;             // HIDDEN_HOOK_READ  [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY HiddenHookWriteEventsHead;            // HIDDEN_HOOK_WRITE  [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY EptHook2sExecDetourEventsHead;        // HIDDEN_HOOK_EXEC_DETOURS [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY EptHookExecCcEventsHead;              // HIDDEN_HOOK_EXEC_CC [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY SyscallHooksEferSyscallEventsHead;    // SYSCALL_HOOK_EFER_SYSCALL [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY SyscallHooksEferSysretEventsHead;     // SYSCALL_HOOK_EFER_SYSRET [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY CpuidInstructionExecutionEventsHead;  // CPUID_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY RdmsrInstructionExecutionEventsHead;  // RDMSR_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY WrmsrInstructionExecutionEventsHead;  // WRMSR_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY ExceptionOccurredEventsHead;          // EXCEPTION_OCCURRED [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY TscInstructionExecutionEventsHead;    // TSC_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY PmcInstructionExecutionEventsHead;    // PMC_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY InInstructionExecutionEventsHead;     // IN_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY OutInstructionExecutionEventsHead;    // OUT_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY DebugRegistersAccessedEventsHead;     // DEBUG_REGISTERS_ACCESSED [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY ExternalInterruptOccurredEventsHead;  // EXTERNAL_INTERRUPT_OCCURRED [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY VmcallInstructionExecutionEventsHead; // VMCALL_INSTRUCTION_EXECUTION [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]
    LIST_ENTRY ControlRegisterModifiedEventsHead;    // CONTROL_REGISTER_MODIFIED [WARNING : MAKE SURE TO INITIALIZE LIST HEAD , Add it to DebuggerRegisterEvent, Add it to DebuggerTriggerEvents, Add termination to DebuggerTerminateEvent ]

} DEBUGGER_CORE_EVENTS, *PDEBUGGER_CORE_EVENTS;

/**
 * @brief The structure of actions in HyperDbg
 *
 */
typedef struct _DEBUGGER_EVENT_ACTION
{
    UINT64                          Tag;                       // Action tag is same as Event's tag
    UINT32                          ActionOrderCode;           // The code for this action (it also shows the order)
    LIST_ENTRY                      ActionsList;               // Holds the link list of next actions
    DEBUGGER_EVENT_ACTION_TYPE_ENUM ActionType;                // What action we wanna perform
    BOOLEAN                         ImmediatelySendTheResults; // should we send the results immediately
                                                               // or store them in another structure and
                                                               // send multiple of them each time

    DEBUGGER_EVENT_ACTION_RUN_SCRIPT_CONFIGURATION
    ScriptConfiguration; // If it's run script

    DEBUGGER_EVENT_REQUEST_BUFFER
    RequestedBuffer; // if it's a custom code and needs a buffer then we use
                     // this structs

    UINT32 CustomCodeBufferSize;    // if null, means it's not custom code type
    PVOID  CustomCodeBufferAddress; // address of custom code if any

} DEBUGGER_EVENT_ACTION, *PDEBUGGER_EVENT_ACTION;

/* ==============================================================================================
 */

/**
 * @brief The structure of events in HyperDbg
 *
 */
typedef struct _DEBUGGER_EVENT
{
    UINT64              Tag;
    LIST_ENTRY          EventsOfSameTypeList; // Linked-list of events of a same type
    VMM_EVENT_TYPE_ENUM EventType;
    BOOLEAN             Enabled;
    UINT32              CoreId; // determines the core index to apply this event to, if it's
                                // 0xffffffff means that we have to apply it to all cores

    UINT32
    ProcessId; // determines the pid to apply this event to, if it's
               // 0xffffffff means that we have to apply it to all processes

    LIST_ENTRY ActionsListHead; // Each entry is in DEBUGGER_EVENT_ACTION struct
    UINT32     CountOfActions;  // The total count of actions

    BOOLEAN EnableShortCircuiting; // indicates whether the short-circuiting event
                                   // is enabled or not for this event

    VMM_CALLBACK_EVENT_CALLING_STAGE_TYPE EventMode; // reveals the execution mode
    // of the event (whether it's a pre- or post- event)

    UINT64 OptionalParam1; // Optional parameter to be used differently by events
    UINT64 OptionalParam2; // Optional parameter to be used differently by events
    UINT64 OptionalParam3; // Optional parameter to be used differently by events
    UINT64 OptionalParam4; // Optional parameter to be used differently by events

    UINT32 ConditionsBufferSize;   // if null, means uncoditional
    PVOID  ConditionBufferAddress; // Address of the condition buffer (most of the
                                   // time at the end of this buffer)

} DEBUGGER_EVENT, *PDEBUGGER_EVENT;

/* ==============================================================================================
 */

//////////////////////////////////////////////////
//					Data Type					//
//////////////////////////////////////////////////

/**
 * @brief The prototype that Condition codes are called
 *
 * @param Regs Guest registers
 * @param Context Optional parameter which is different
 * for each event and shows a unique description about
 * the event
 * @return UINT64 if return 0 then the event is not allowed
 * to trigger and if any other value then the event is allowed
 * to be triggered
 * return value should be on RAX
 */
typedef UINT64
DebuggerCheckForCondition(PGUEST_REGS Regs, PVOID Context);

/**
 * @brief The prototype that Custom code buffers are called
 *
 * @param PreAllocatedBufferAddress The address of a pre-allocated non-paged pool
 * if the user-requested for it
 * @param Regs Guest registers
 * @param Context Optional parameter which is different
 * for each event and shows a unique description about
 * the event
 * @return PVOID A pointer to a buffer that should be delivered to the user-mode
 * if returns null or an invalid address then nothing will be delivered
 * return address should be on RAX
 */
typedef PVOID
DebuggerRunCustomCodeFunc(PVOID PreAllocatedBufferAddress, PGUEST_REGS Regs, PVOID Context);

//////////////////////////////////////////////////
//					Functions					//
//////////////////////////////////////////////////

UINT64
DebuggerGetRegValueWrapper(PGUEST_REGS GuestRegs, UINT32 /* REGS_ENUM */ RegId);

UINT32
DebuggerGetLastError();

VOID
DebuggerSetLastError(UINT32 LastError);

BOOLEAN
DebuggerInitialize();

VOID
DebuggerUninitialize();

PDEBUGGER_EVENT
DebuggerCreateEvent(BOOLEAN Enabled, UINT32 CoreId, UINT32 ProcessId, VMM_EVENT_TYPE_ENUM EventType, UINT64 Tag, UINT64 OptionalParam1, UINT64 OptionalParam2, UINT64 OptionalParam3, UINT64 OptionalParam4, UINT32 ConditionsBufferSize, PVOID ConditionBuffer);

PDEBUGGER_EVENT_ACTION
DebuggerAddActionToEvent(PDEBUGGER_EVENT Event, DEBUGGER_EVENT_ACTION_TYPE_ENUM ActionType, BOOLEAN SendTheResultsImmediately, PDEBUGGER_EVENT_REQUEST_CUSTOM_CODE InTheCaseOfCustomCode, PDEBUGGER_EVENT_ACTION_RUN_SCRIPT_CONFIGURATION InTheCaseOfRunScript);

BOOLEAN
DebuggerRegisterEvent(PDEBUGGER_EVENT Event);

VMM_CALLBACK_TRIGGERING_EVENT_STATUS_TYPE
DebuggerTriggerEvents(VMM_EVENT_TYPE_ENUM                   EventType,
                      VMM_CALLBACK_EVENT_CALLING_STAGE_TYPE CallingStage,
                      PVOID                                 Context,
                      BOOLEAN *                             PostEventRequired,
                      GUEST_REGS *                          Regs);

PDEBUGGER_EVENT
DebuggerGetEventByTag(UINT64 Tag);

BOOLEAN
DebuggerRemoveEvent(UINT64 Tag);

BOOLEAN
DebuggerQueryDebuggerStatus();

BOOLEAN
DebuggerParseEventFromUsermode(PDEBUGGER_GENERAL_EVENT_DETAIL EventDetails, UINT32 BufferLength, PDEBUGGER_EVENT_AND_ACTION_REG_BUFFER ResultsToReturnUsermode);

BOOLEAN
DebuggerParseActionFromUsermode(PDEBUGGER_GENERAL_ACTION Action, UINT32 BufferLength, PDEBUGGER_EVENT_AND_ACTION_REG_BUFFER ResultsToReturnUsermode);

BOOLEAN
DebuggerParseEventsModificationFromUsermode(PDEBUGGER_MODIFY_EVENTS DebuggerEventModificationRequest);

BOOLEAN
DebuggerTerminateEvent(UINT64 Tag);

BOOLEAN
DebuggerEnableOrDisableAllEvents(BOOLEAN IsEnable);

BOOLEAN
DebuggerRemoveAllEvents();

BOOLEAN
DebuggerTerminateAllEvents();

UINT32
DebuggerEventListCount(PLIST_ENTRY TargetEventList);

UINT32
DebuggerEventListCountByCore(PLIST_ENTRY TargetEventList, UINT32 TargetCore);

UINT32
DebuggerEventListCountByEventType(VMM_EVENT_TYPE_ENUM EventType, UINT32 TargetCore);

UINT32
DebuggerExceptionEventBitmapMask(UINT32 CoreIndex);

BOOLEAN
DebuggerIsTagValid(UINT64 Tag);

BOOLEAN
DebuggerEnableEvent(UINT64 Tag);

BOOLEAN
DebuggerQueryStateEvent(UINT64 Tag);

BOOLEAN
DebuggerDisableEvent(UINT64 Tag);

VOID
DebuggerPerformActions(PROCESSOR_DEBUGGING_STATE * DbgState, PDEBUGGER_EVENT Event, PVOID Context);

VOID
DebuggerPerformBreakToDebugger(PROCESSOR_DEBUGGING_STATE * DbgState, UINT64 Tag, PDEBUGGER_EVENT_ACTION Action, PVOID Context);

BOOLEAN
DebuggerPerformRunScript(PROCESSOR_DEBUGGING_STATE * DbgState, UINT64 Tag, PDEBUGGER_EVENT_ACTION Action, PDEBUGGEE_SCRIPT_PACKET ScriptDetails, PVOID Context);

VOID
DebuggerPerformRunTheCustomCode(PROCESSOR_DEBUGGING_STATE * DbgState, UINT64 Tag, PDEBUGGER_EVENT_ACTION Action, PVOID Context);

PLIST_ENTRY
DebuggerGetEventListByEventType(VMM_EVENT_TYPE_ENUM EventType);
