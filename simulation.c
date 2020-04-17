#include <time.h>
#include <stdlib.h>

#include "flow.h"
#include "arrival.h"

/* 
	Given: filename of the CDF, interarrival time between flows, and the total simulation time (milliseconds)
	Returns large csv ("simulation.csv") with interarrival times
*/
void simulation(char* filename, double interarrival_time, double total_simulation_time){
	FILE *fp;
	fp=fopen("simulation.csv","w+");


	srand(time(NULL));
	double seed = rand();
	double lambda = total_simulation_time/interarrival_time;

	poissonProcess arrival_times = init_poissonProcess(seed, lambda);
	struct FlowNode* data_flows = init_flow(filename);

	double next_arrival;
	double next_data_flow;

	while(total_simulation_time > 0){
		next_arrival = get_arrival_time(&arrival_times);
		next_data_flow = get_next_flow(data_flows);
		total_simulation_time -= next_arrival;
		fprintf(fp,"%f,%f\n", next_arrival, next_data_flow); // write to csv in format "arrival time, data size \n"
	}

	fclose(fp);


}


int main(){
	simulation("test_cdf.txt", 5, 100);
	return 0;
}