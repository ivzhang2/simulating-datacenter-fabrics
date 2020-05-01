#include "path.h"

#define MAXCHAR 1000 
#define MAXPATHLENGTH 22
#define MAXPATHSIZE 4

// Given 2 hosts, this function will return the object packet_path 
// containing the array of paths and size of the array
struct packet_path *get_path (char *host1, char *host2)
{
	// char *host1 = "h1";
	// char *host2 = "h3";
	char *filename = "path.txt";
	char row[MAXCHAR];

	int n_path;
	char *path_string[MAXPATHSIZE];
	
	struct packet_path *packet = malloc(sizeof(struct packet_path));

	FILE *fp = fopen(filename, "r");
	while (fgets(row, MAXCHAR, fp) != NULL){
	    char *element = strtok(row, " "); 

	    // Returns first element: host1  
	    char *h1 = element;
	    element = strtok(NULL, " "); 

	    // Returns second element: host2
    	char *h2 = element; 
    	element = strtok(NULL, " ");

    	if (((strcmp(host1,h1) == 0) && (strcmp(host2,h2) == 0)) 
    		|| ((strcmp(host1,h2) == 0) && (strcmp(host2,h1) == 0)))
    	{
	    	// Returns third element: size
	    	n_path = atol(element);
	    	element = strtok(NULL, " ");

		    // Returns rest of elements: a list of paths
		    for (int i=0; i<n_path; i++)
		    { 	
		        path_string[i] = element;
		        element = strtok(NULL, " "); 
		    }

		    // parse the paths as string to list of switches
		    for(int i=0; i<n_path; i++){
		    	char *ptr = strtok(path_string[i],",");
		    	int j = 0;
		    	while(ptr != NULL){
		    		packet->paths[i][j] = ptr;
		    		printf("%s ", packet->paths[i][j]);
		    		j++;
		    		ptr = strtok(NULL,",");
		    	}
		    	printf("\n");
    }
	    }
	}
	fclose(fp);

    packet->n_paths = n_path;
    printf("%d\n", packet->n_paths);
	return packet;
}

int main(){
	struct packet_path *p = get_path("h10", "h5");
	return 0;
}




