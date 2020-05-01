#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPATHLENGTH 22
#define MAXPATHSIZE 4

// struct containing the path between 2 hosts, 
// includes an array of all possible paths (paths) and n_paths (size of the array)
struct packet_path {
	int n_paths;
	char *paths[MAXPATHSIZE][MAXPATHLENGTH];
};

// Given 2 hosts, this function will return the object packet_path 
// containing the array of all possible paths and size of the array
struct packet_path *get_path (char *host1, char *host2);