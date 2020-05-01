#include "packet.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// Read packet from file
struct packet_t** packet_read(char *filename) {

    struct packet_t** packets;

    // Get number of packets from file
    FILE *f = fopen(filename, "r");
    if(f == NULL)
    {
        printf("\nfile opening failed ");
        return packets;
    }
    char c;
    int count = 0;
    for (c = getc(f); c != EOF; c = getc(f)) 
        if (c == '\n')
            count += 1; 
    fclose(f);
    free(f);

    // Read packets
    packets = malloc(sizeof(struct packet_t *) * count);
    assert(packets != NULL);
    char buffer[32] ;
    char *record,*line;
    int i=0,j=0;
    FILE *fstream = fopen(filename,"r");
    if(fstream == NULL)
    {
        printf("\nfile opening failed ");
        return packets;
    }
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
        packets[i] = malloc(sizeof(struct packet_t));
        record = strtok(line,",");
        
        while(record != NULL)
        {
        if (j==0){
            packets[i]->send_id = atoi(record);
        }
        else if (j==1){
            packets[i]->receive_id = atoi(record);
        }
        else if(j==2){
            packets[i]->curr_time = (uint64_t) (atof(record)*pow(10,6) + .5);
        }
        else {
            packets[i]->size = (uint64_t) atof(record);
        }
        record = strtok(NULL,",");
        j += 1;
        }
        ++i;
        j = 0;
    }
    return packets;
}