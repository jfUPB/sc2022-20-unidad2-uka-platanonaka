#include "eventList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

EventList *CreateEventList(void)
{
    EventList *eventList = malloc(sizeof(EventList));
    eventList->head = NULL;
    eventList->last = NULL;
    eventList->isEmpty = 1;
    return eventList;
}

void DestroyEventList(EventList *this)
{
    free(this);
}

Event *SearchEvent(EventList *this, char *name)
{
    Event *eventoActual = this->head;
    if (this->isEmpty == 0)
    {
        while (eventoActual != NULL)
        {
            if (strcmp(name, eventoActual->eventName)==0)
            return eventoActual;
            eventoActual = eventoActual->next;
        }
    }
    eventoActual = NULL;
    return eventoActual;
}

void AddEvent(EventList *this, Event *event)
{
    Event *eventoActual = this->head;
    while (eventoActual != NULL)
    {
        if(strcmp(event->eventName, eventoActual->eventName) == 0)
        return;

        eventoActual = eventoActual->next;
    }
    
   if(this->isEmpty == 0)
   {
        this->last->next = event;
        this->last=event;
   }
   else
   {
       this->head = event;
       this->last = event;
       this->isEmpty = 0;    
   }
}

void RemoveEvent(EventList *this, char *name)
{
    if (this->isEmpty == 0)
    {
       Event *eventoActual = this->head->next;  //USAMOS DOS EVENTOS PARA UBICARNOS EN EL ACTUAL Y ANTERIOR PARA MANEJAR MEJOR LA ELMINACION DE EVENTOS.
       Event *eventoAnterior = this->head;
       if(strcmp(name, eventoAnterior->eventName)==0)
       {
            if(eventoAnterior->next == NULL)
            {
                this->head = NULL;
                this->last = NULL;
                this->isEmpty = 1;
                DestroyEvent(eventoAnterior);
            }
            else
            {
                this->head=eventoActual;
                DestroyEvent(eventoAnterior);
            }
       }
       while (eventoActual != NULL)
       {
            if(strcmp(name, eventoActual->eventName)==0)
            {
                eventoAnterior->next = eventoActual->next;
                if (this->last->next == NULL)
                {
                    this->last = eventoAnterior;
                    DestroyEvent(eventoActual);
                }
            }
            eventoAnterior = eventoActual;
            eventoActual = eventoActual->next;
       }
    }
}

void ListEvents(EventList *this)
{
    if (this->isEmpty == 0)
    {
        Event *eventoActual = this->head;

        while (eventoActual != NULL)
        {
            printf("%s\n", eventoActual->eventName);
            eventoActual = eventoActual->next;
        }       
    }
    else
    {
        printf("empty\n");
    }

}