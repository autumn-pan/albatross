/*
ALBATROSS uses DMD (Dynamic Module Dispatcher) to decide which nonessential services to enable.
For now, the only service is Priority Demotion which is a stopgap for preemption meant to prevent starvation.
Simply set the value of a macro to 1 or 0 to determine whether its associated module should be active.
*/ 

#define PRIORITY_DEMOTION 1