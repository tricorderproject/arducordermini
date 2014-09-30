/************************************************************************/
/*																		*/
/*	task_manager.c -- Periodic Task Management							*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/* This module contains code to manage periodic tasks. This allows a	*/
/* user to register functions that will be called periodically as part	*/
/* of the main execution loop.											*/
/*																		*/
/************************************************************************/
//*	This module is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	12/08/2011(GeneApperson): Created									*/
/*	12/20/2011(GeneApperson): Modified to support multiple tasks using	*/
/*		the same task function, and made the task var be a void * rather*/
/*		than an unsigned short.											*/
/*	02/06/2013(GeneApperson): Removed dependencies on Microchip plib	*/
/*																		*/
/************************************************************************/

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#define	OPT_SYSTEM_INTERNAL
#include	<System_Defs.h>
#include	<pins_arduino.h>

#include	"wiring.h"

/* ------------------------------------------------------------ */
/*				Local Type Definitions							*/
/* ------------------------------------------------------------ */

typedef struct {
	taskFunc	pfnTask;		// pointer to the task function
	uint32_t	tmsPeriod;		// task period in milliseconds
	uint32_t	tmsNext;		// next event time for this task
	void *		varTask;		// task user variable
	uint16_t	stTask;			// task enable status
	uint16_t	fsFlags;		// task flags
} TASK;

/* The following bits used in the fsFlags member of the TASK structure.
*/
#define	fsBusy	0x0001			// task is currently executing

#define	fFalse	0;
#define	fTrue	!fFalse;

/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Local Variables									*/
/* ------------------------------------------------------------ */

static TASK	rgtaskTable[NUM_TASKS];

static int		cntActiveTask = 0;	//number of tasks currently active

static uint32_t	tmsNextEvent  = 0;	//time when last task event occured
static uint32_t	tmsLastEvent  = 0;	//time for next task event to occur

/* ------------------------------------------------------------ */
/*				Forward Declarations							*/
/* ------------------------------------------------------------ */

void	_updateTaskEvent(unsigned long tms);

/* ------------------------------------------------------------ */
/*				Public Interface Functions						*/
/* ------------------------------------------------------------ */
/***	createTask
**
**	Parameters:
**		task		- pointer to the task function
**		period		- period in milliseconds for the task
**		state		- initial task enable state
**		var			- task user variable
**
**	Return Value:
**		task id of the ceated task
**
**	Errors:
**		Returns the task id of the created task, or -1 if error
**
**	Description:
**		Add this task to the currently active tasks. This function
**		will fail if there is no room in the task table.
**		This function is not allowed to be called from within an
**		interrupt service routine.
*/

int
createTask(taskFunc task, unsigned long period, unsigned short state, void * var) {
	int				id;
	int				idSet;
	int				idFree;
	unsigned long	tmsCur;
	unsigned int	st;

	/* Search the table looking for an empty slot.
	*/
	st = disableInterrupts();
	tmsCur = millis();
	idSet  = -1;
	for (id = 0; id < NUM_TASKS; id++) {
		/* If this is the first vacant slot in the table.
		*/
		if (rgtaskTable[id].pfnTask == 0) {
			idSet = id;
			break;
		}
	}

	/* We should have the index of the appropriate slot in the table
	** in idSet. If idSet == -1, then the table is full.
	*/
	if (idSet != -1) {
		/* Store the task values into this slot in the task table.
		*/
		rgtaskTable[idSet].pfnTask   = task;
		rgtaskTable[idSet].tmsNext   = tmsCur + period;
		rgtaskTable[idSet].tmsPeriod = period;
		rgtaskTable[idSet].varTask	 = var;
		rgtaskTable[idSet].stTask	 = state;
		rgtaskTable[idSet].fsFlags	 = 0;
	}
	restoreInterrupts(st);

	if (idSet != -1) {
		/* Update our notion of when the next task event should occur.
		*/
		st = disableInterrupts();
		_updateTaskEvent(tmsCur);
		restoreInterrupts(st);
	}

	/* All done. Return the task id.
	*/
	return (idSet);

}

/* ------------------------------------------------------------ */
/***	destroyTask
**
**	Parameters:
**		id		- task id of task to destroy
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Remove the specified task from the active task table.
**		This function is not allowed to be called from within an
**		interrupt service routine.
*/

void
destroyTask(int id) {
	int				itask;
	unsigned int	st;

	/* Remove the specified task from the table.
	*/
	if (id < NUM_TASKS) {
		rgtaskTable[id].pfnTask = 0;
		rgtaskTable[id].tmsPeriod = 0;
		rgtaskTable[id].stTask = 0;
		rgtaskTable[id].varTask = 0;
		rgtaskTable[id].fsFlags = 0;
	}

	/* Update when the next task event should occur.
	*/
	st = disableInterrupts();
	_updateTaskEvent(millis());
	restoreInterrupts(st);

	return;
}

/* ------------------------------------------------------------ */
/***	getTaskId
**
**	Parameters:
**		task		- pointer to task function
**
**	Return Value:
**		returns task id
**
**	Errors:
**		Returns -1 if not a valid task
**
**	Description:
**		Search the task table for the specified task
*/

int
getTaskId(taskFunc task) {
	int	id;

	for (id = 0; id < NUM_TASKS; id++) {
		if (rgtaskTable[id].pfnTask == task) {
			return id;
		}
	}

	return -1;

}

/* ------------------------------------------------------------ */
/***	startTaskAt
**
**	Parameters:
**		id		- task id
**		tms		- task start time (millis tick value)
**		st		- task run state
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Schedule the specified task to start running at the specified
**		time. The time is given as the system millis() tick time.
*/

void
startTaskAt(int id, unsigned long tms, unsigned short st) {

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		rgtaskTable[id].tmsNext = tms;
		rgtaskTable[id].stTask = st;
		_updateTaskEvent(millis());
	}
}

/* ------------------------------------------------------------ */
/***	getTaskNextExec
**
**	Parameters:
**		id		- task id
**
**	Return Value:
**		returns the next scheduled execution time for the task
**
**	Errors:
**		returns 0 if invalid task
**
**	Description:
**		Return the next scheduled execution time for the task.
*/

unsigned long
getTaskNextExec(int id) {

	if ((id < NUM_TASKS) &&
		(rgtaskTable[id].pfnTask != 0) && 
		(rgtaskTable[id].stTask != TASK_DISABLE)) {
		return rgtaskTable[id].tmsNext;
	}

	return 0;
}

/* ------------------------------------------------------------ */
/***	setTaskState
**
**	Parameters:
**		id		- task id
**		st		- execution state to set
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Sets the enable state of the specified task. If the
**		task is being enabled, update the task event schedule
**		if necessary. The enable state is one of:
**			TASK_ENABLE		- run the task continuously
**			TASK_DISABLE	- stop running the task
**			TASK_RUN_ONCE	- run the task 1 time and then disable
**			'n'				- run the task n times and then disable
*/

void
setTaskState(int id, unsigned short st) {
	unsigned long tms;

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		rgtaskTable[id].stTask = st;
		if (rgtaskTable[id].stTask != TASK_DISABLE) {
			/* Update when the task should next become active.
			*/
			tms = millis();
			rgtaskTable[id].tmsNext = tms + rgtaskTable[id].tmsPeriod;
			_updateTaskEvent(tms);
		}
	}
}

/* ------------------------------------------------------------ */
/***	getTaskState
**
**	Parameters:
**		id		- task id
**
**	Return Value:
**		returns the current run state of the specified task
**
**	Errors:
**		Returns 0 if the task id is invalid
**
**	Description:
**		Returns the current run state of the specified task.
*/

unsigned short
getTaskState(int id) {

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		return rgtaskTable[id].stTask;
	}

	return 0;
}

/* ------------------------------------------------------------ */
/***	setTaskPeriod
**
**	Parameters:
**		id		- task id
**		tmsSet	- task period to set
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Set the scheduling period for the specified task. If the
**		task is currently active, update the next task event.
*/

void
setTaskPeriod(int id, unsigned long tmsSet)	{
	unsigned long tmsCur;

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		/* Set the new scheculing period for this task.
		*/
		rgtaskTable[id].tmsPeriod = tmsSet;

		/* If the task is active, update the task schedule.
		*/
		if (rgtaskTable[id].stTask != TASK_DISABLE) {
			/* Update when the task should next become active.
			*/
			tmsCur = millis();
			rgtaskTable[id].tmsNext = tmsCur + tmsSet;
			_updateTaskEvent(tmsCur);
		}
	}
}

/* ------------------------------------------------------------ */
/***	getTaskPeriod
**
**	Parameters:
**		id		- task id
**
**	Return Value:
**		Returns current task scheduling period
**
**	Errors:
**		returns 0 if invalid task
**
**	Description:
**		Returns the task scheduling period.
*/

unsigned long
getTaskPeriod(int id) {

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		return rgtaskTable[id].tmsPeriod;
	}

	return 0;
}

/* ------------------------------------------------------------ */
/***	setTaskVar
**
**	Parameters:
**		id		- task identifier
**		var		- task variable value to set
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Set the task user variable.
*/

void
setTaskVar(int id, void * var) {

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		rgtaskTable[id].varTask = var;
	}

}

/* ------------------------------------------------------------ */
/***	getTaskVar
**
**	Parameters:
**		id		- task id
**
**	Return Value:
**		Returns current value of task user variable
**
**	Errors:
**		returns 0 if invalid task
**
**	Description:
**		Returns the task user variable.
*/

void *
getTaskVar(int id) {

	if ((id < NUM_TASKS) && (rgtaskTable[id].pfnTask != 0)) {
		return rgtaskTable[id].varTask;
	}

	return 0;
}

/* ------------------------------------------------------------ */
/*					Internal System Functions					*/
/* ------------------------------------------------------------ */
/***	_initTaskManager
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the periodic task manager.
*/

void
_initTaskManager() {
	int		id;

	for (id = 0; id < NUM_TASKS; id++) {
		rgtaskTable[id].pfnTask = 0;
	}

	tmsLastEvent = 0;
	tmsNextEvent = 0;

}

/* ------------------------------------------------------------ */
/***	_scheduleTask
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Scan the task table and call all tasks whose next event
**		time has expired. Remove tasks that have exhausted their
**		repeat count, and update the time for the next task
**		event.
**
**		The following timing diagrams illustrate the three cases
**		for when the next event has timed out allowing for the fact
**		that either the next event time or the current time has
**		wrapped due to overflow. In these, L is the last event time
**		N is the next scheduled event time, and C is the current
**		time.
**
**	...............................LxxxxxxxxN..C........
**		usual case: (N >= L) && (C >= N)
**
**	.C.......................................LxxxxxxxxN.
**		current time has wrapped: (N >= L) && (C < L)
**
**	xxxN..C..........................................Lxx
**		current time and next time have wrapped: (N < L) && (C >= N)
*/

void
_scheduleTask() {
	int				id;
	unsigned long	tmsCur;		//current system time
	unsigned long	tmsNxt;		//time for next event for this task
	unsigned long	dtmsNext;
	unsigned long	dtms;

	if (cntActiveTask == 0) {
		return;
	}

	tmsCur = millis();

	/* The system millisecond timer will overflow every 49.71 days. The complexity of
	** this conditional is to account for the cases where either the next event time has
	** wrapped around or the current time has wrapped around.
	*/
	if ( ((tmsNextEvent >= tmsLastEvent) &&
				((tmsCur >= tmsLastEvent) && (tmsCur < tmsNextEvent))) ||
		 ((tmsNextEvent < tmsLastEvent) &&
				((tmsCur >= tmsLastEvent) || (tmsCur < tmsNextEvent))) ) {

		return;
	}

	/* The next periodic task event time has occured. We need to search
	** the table for all events that have elapsed and call their
	** associated functions, update their next event timers, and then
	** figure out when the next event time is.
	*/
	dtmsNext = 0xFFFFFFFF;
	for (id = 0; id < NUM_TASKS; id++) {
		/* If this isn't an active task, go to the next one.
		*/
		if ((rgtaskTable[id].pfnTask == 0) || 
			(rgtaskTable[id].stTask == TASK_DISABLE)) {
			continue;
		}

		/* If this task is busy, go to the next one. This case can
		** occur if a user task function calls delay() or any other
		** function that causes _scheduleTask to be called recursively.
		** This prevents the task function from being called recursively
		** until the system crashes.
		*/
		if ((rgtaskTable[id].fsFlags & fsBusy) != 0) {
			continue;
		}

		/* Check if this task's period has timed out.
		*/
		tmsNxt = rgtaskTable[id].tmsNext;
		if ( ((tmsNxt >= tmsLastEvent) && 
						((tmsCur >= tmsNxt) || (tmsCur < tmsLastEvent))) ||
			 ((tmsNxt <  tmsLastEvent) && 
						((tmsCur >= tmsNxt) && (tmsCur < tmsLastEvent))) ) {

			/* This task event has timed out. Update the event time for the
			** next event on this task.
			*/
			rgtaskTable[id].tmsNext += rgtaskTable[id].tmsPeriod;

			/* Call the event function.
			*/
			rgtaskTable[id].fsFlags |= fsBusy;
			(*rgtaskTable[id].pfnTask)(id, rgtaskTable[id].varTask);
			rgtaskTable[id].fsFlags &= ~fsBusy;

			/* Decrement the repeat count.
			*/
			if ((rgtaskTable[id].stTask > 0) &&
				(rgtaskTable[id].stTask != TASK_ENABLE)) {

				rgtaskTable[id].stTask -= 1;

				/* The task state counter has gone to 0. This task is now
				** disabled.
				*/
				if (rgtaskTable[id].stTask == 0) {
					rgtaskTable[id].tmsNext = 0;
					cntActiveTask -= 1;
					continue;
				}
			}
		}

		/* Compute delta of this event time from the current time and
		** remember it if it is less than the current delta.
		*/
		dtms = rgtaskTable[id].tmsNext - tmsCur;
		if (dtms < dtmsNext) {
			dtmsNext = dtms;
		}
	}

	/* All done with event tasks. Update the last event time with
	** the current time.
	*/
	tmsLastEvent = tmsCur;

	/* Compute when the next event time will be by adding the event
	** time delta to the current time.
	*/
	tmsNextEvent = tmsCur + dtmsNext;
}

/* ------------------------------------------------------------ */
/***	_updateTaskEvent
**
**	Parameters:
**		tmsCur		- current system tick time
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Scan the task table and find the event time for the next
**		event that should occur. If the table is empty, ensure
**		that the active count task is cleared.
*/

void
_updateTaskEvent(unsigned long tmsCur) {
	int				id;
	unsigned long	dtmsTmp;
	unsigned long	dtms;

	/* Scan the table for the smallest next task time that is greater
	** than the current system time.
	*/
	dtms = 0xFFFFFFFF;
	cntActiveTask = 0;
	for (id = 0; id < NUM_TASKS; id++) {
		/* Ignore empty slots in the table and inactive tasks.
		*/
		if ((rgtaskTable[id].pfnTask != 0) && (rgtaskTable[id].stTask != TASK_DISABLE)) {

			/* Compute delta of this event time from the current time and
			** remember it if it is less than the current delta.
			*/
			cntActiveTask += 1;
			dtmsTmp = rgtaskTable[id].tmsNext - tmsCur;
			if (dtmsTmp < dtms) {
				dtms = dtmsTmp;
			}
		}
	}

	/* Compute when the next event time will be by adding the event
	** time delta to the current time.
	*/
	if (cntActiveTask != 0) {
		tmsNextEvent = tmsCur + dtms;
	}
}

/* ------------------------------------------------------------ */
/***	ProcName
**
**	Parameters:
**
**	Return Value:
**
**	Errors:
**
**	Description:
**
*/

/* ------------------------------------------------------------ */

/************************************************************************/

