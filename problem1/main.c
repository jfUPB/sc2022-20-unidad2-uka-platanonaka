#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eventList.h"

//#define DOLOG
#ifdef DOLOG
#define LOG(...) fprintf(log,__VA_ARGS__);
#else
#define LOG(...) 
#endif

int main(void)
{
    char commandBuf[64];

#ifdef DOLOG
    FILE *log = fopen("log","w");
    if(log == NULL){
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif
    
    EventList *eventList = NULL;
    eventList = CreateEventList();
    LOG("eventList object created\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "add", strlen("add")) == 0)
        {
            // ADICIONA UN EVENTO A LA LISTA
            LOG("running add\n");
            fgets(commandBuf, sizeof(commandBuf), stdin);
            commandBuf[strlen(commandBuf) - 1] = 0;
            AddEvent(eventList, CreateEvent(commandBuf));
            LOG("%s event added to eventList\n",commandBuf);
        }
        else if (strncmp(commandBuf, "ask", strlen("ask")) == 0)
        {
            // MUESTRA LOS EVENTOS EN LA LISTA
            LOG("running ask\n");
            ListEvents(eventList);

        }
        else if (strncmp(commandBuf, "rm", strlen("rm")) == 0)
        {
            // ELIMINA UN EVENTO DE LA LISTA
            LOG("running rm\n");
            fgets(commandBuf, sizeof(commandBuf), stdin);
            commandBuf[strlen(commandBuf) - 1] = 0;
            RemoveEvent(eventList, commandBuf);
            LOG("%s event removed from eventList\n",commandBuf);
        }
        else if (strncmp(commandBuf, "search", strlen("search")) == 0)
        {
            // BUSCA UN EVENTO EN LA LISTA
            LOG("running search\n");
            fgets(commandBuf, sizeof(commandBuf), stdin);
            commandBuf[strlen(commandBuf) - 1] = 0;

            Event *event = SearchEvent(eventList, commandBuf);
            if(event == NULL){
                LOG("event %s wasn't found\n",commandBuf);
                printf("NULL\n");
            }
            else{
                LOG("event %s was found\n",commandBuf);
                printf("%s\n",event->eventName);
            }
            
        }
        else if (strncmp(commandBuf, "destroyAdd", strlen("destroyAdd")) == 0)
        {
            // VERIFICA SI DESTRUYE UN EVENTO QUE YA EXISTA EN LA LISTA
            LOG("running destroy test\n");
            fgets(commandBuf, sizeof(commandBuf), stdin);
            commandBuf[strlen(commandBuf) - 1] = 0;

            Event *event = SearchEvent(eventList, commandBuf);
            if(event != NULL){
                Event *eventNew = CreateEvent(commandBuf);
                AddEvent(eventList, eventNew);
                event = SearchEvent(eventList, commandBuf);
                if(event == eventNew){
                    printf("fail\n");
                }
                else{
                    printf("pass\n");
                }
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            // TERMINA EL CICLO INTERACTIVO
            LOG("running exit\n");
            break;
        }
    }

    DestroyEventList(eventList);
    LOG("eventList destroyed\n");
    return EXIT_SUCCESS;
}