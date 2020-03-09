/******************************************************************************
* File Name: FSM.h
*
* Version: Beta
*
* Description: This file contains the definition of the Finite State Machine,
* part of the firmware for the HappyCow/EasyMoo Electronic Design (EEC136)
* Capstone Project.
*
* Related Document: HappyCowReport.pdf
* Hardware Dependency: CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*
* Author(s):
*	Yousef H. Akbar & Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
*******************************************************************************
* The current list of states in our FSM are:
* 	0) OFF:		    Default starting state, switched off using button.
* 	1) SENSOR:	    When PSoC switched on; active sensor reading mode.
* 	2) SLEEP:	    When inactivity detected; use minimal resources.
* 	3) CRITICAL:	When sensors read critical info; alert user until off.
* 	4) TALK:	    When connected to BLE; send info to CySmart.
* States are either 0 or 1; One state will always be 1, others must be 0.
* As mentioned, OFF is the starting state.
******************************************************************************/

#include "stdio.h"

#define NUM_STATES      (5)
#define CRIT_INACTIVE   (600)

enum STATES{OFF, SENSOR, SLEEP, CRITICAL, TALK};

struct State {
	int id;
	int val;
	int prev;
};

typedef struct FSM {
	struct State states[5];
	struct State *curr;
} FSM;

/* Function Name: toggleState
 *
 * Summary:
 * This function toggles the value (0 or 1, off or on) of the state specified
 * by the @target argument. It saves its value pre-toggle to the `prev`
 * variable.
 *
 * Parameters:
 * 	@*target:	pointer to state we would like to toggle.
 *
 * Return:
 * 	None.
 */
void toggleState(struct State *target)
{
	int *previous = &(target->prev);
	int *value = &(target->val);
	
	*previous = target->val;
	if (*value == 1)
		*value = 0;
	else
		*value = 1;
}

/* Function Name: setCurrState
 *
 * Summary:
 * This function changes the current active state of the FSM. It toggles
 * whatever the current active state is and sets the state specified by @id as
 * the new active state. Both changes are done using toggleState()
 *
 * Parameters:
 * 	@*machine:	global state machine struct variable.
 * 	@id:		target state id number. refer to enum for order.
 *
 * Return:
 * 	None.
 */
void setCurrState(FSM *machine, int id)
{
	if (machine->curr)
		toggleState(machine->curr);
	toggleState(&(machine->states[id]));
	machine->curr = &(machine->states[id]);
}

void updateFSM(FSM *machine, int accInactive, int lightFlag, int tempFlag)
{
	switch(machine->curr->id)
    {
        case OFF:       
            setCurrState(machine, SENSOR);
            break;
        case SENSOR:
            if (accInactive)
                setCurrState(machine, SLEEP);
            if (lightFlag || tempFlag)
                setCurrState(machine, CRITICAL);
            break;
        case SLEEP:
            if (!accInactive)
                setCurrState(machine, SENSOR);
            if (lightFlag || tempFlag)
                setCurrState(machine, CRITICAL);
            break;
        case CRITICAL:
            if (!lightFlag && !tempFlag)
                setCurrState(machine, SLEEP);
            break;
        case TALK:
            if (1) // when BLE disconnects FIXME
                setCurrState(machine, SLEEP);
            break;
    }
}

void printFSM(FSM machine)
{
    printf("\r\n");
    for (int i=OFF; i <= TALK; i++) {
        printf("ID: %d      Value: %d       Previous: %d\r\n",
	    machine.states[i].id, machine.states[i].val,
	    machine.states[i].prev);
    }
}

/* Function Name: initFSM
 *
 * Summary:
 * This function initializes the 5(?) states in the finite state machine (FSM).
 * OFF is the default state. Therefore, all states should start 0, OFF 1.
 *
 * Parameters:
 * 	@*machine:	global state machine struct variable
 *
 * Return:
 * 	None.
 */
void initFSM(FSM *machine)
{
	for (int i=0; i<NUM_STATES; i++) {
		machine->states[i].id = i;
		machine->states[i].prev = 0;
		machine->states[i].val = 0;
	}
	setCurrState(machine, OFF);
}
