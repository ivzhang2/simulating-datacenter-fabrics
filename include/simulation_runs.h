#include <stdio.h>
#include <string.h>

#include "topology.h"
#include "packet.h"


struct simulation_runs {
	struct packet_t** parr_arr; // 2D array of pointers to packet in same topo
	struct topology_t** topoarr; // pointer to array of topologies based on packet movement
};

/*
	Function: is_same_network_object

	@discussion 
	helper function for is_in_topology to check if two network objects are the same

	@params 
	struct network_object_t* a: pointer to network object to compare
	struct network_object_t* b: pointer to network object to compare

	@returns 
	1 if the objects are the same, otherwise 0
*/

int is_same_network_object(struct network_object_t* a, struct network_object_t* b);

/*
	Function: is_in_topology

	@discussion 
	check if network object is in topology

	@params 
	struct network_object_t* a: pointer to network object to check for
	struct topology_t* topo: pointer to topology to be compared to 

	@returns 
	1 if the network object in topology, otherwise 0
*/

int is_in_topology(struct network_object_t* a, struct topology_t* topo);

/*
	Function: create_new_topology

	@discussion 
	creates new topology object based on given network path

	@params 
	struct network_object_t **path: pointer to array of network_objects that make up path
	size_t n_path: size of the network path

	@returns 
	struct topology_t* topo: pointer to the new topology object created
*/

struct topology_t* create_new_topology(struct network_object_t **path, size_t n_path);

/*
	Function: union_topology

	@discussion 
	performs an union operation on the given topology, topo, and network path, path.

	@params 
	struct topology_t* topo: pointer to topology object to be unioned
	struct network_object_t **path: pointer to array of network_objects to be unioned
	size_t n_path: size of the network path

	@returns
	!frees the given pointer to the previous topology object (topo)
	struct topology_t* temp: pointer to the new topology object created
*/
struct topology_t*  union_topology(struct topology_t* topo, struct network_object_t **path, size_t n_path);

/*
	Function: generate_sim_runs

	@discussion 
	generates an object containing the isolated/pruned network structure

	@params 
	packet_t** p_arr: pointer to an array of pointers to packets 
	size_t num_packets: number of packets passed

	@returns 
	struct simulation_runs*: a simulation_runs object of isolated topologies where
	parr_arr[i] is an array of packets corresponding to topoarr[i]
*/

struct simulation_runs* generate_sim_runs(struct packet_t** p_arr, size_t num_packets); 




