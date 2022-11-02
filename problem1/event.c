#include "event.h"
#include <string.h>
#include <stdlib.h>

Event *CreateEvent(char *name)
{
    Event *event = malloc(sizeof(Event));
    name[15] = 0;
    strncpy(event->eventName, name, strlen(name)+1);
    event->next = NULL;
   
    return event;
}

void DestroyEvent(Event *this)
{
    free(this);
}
