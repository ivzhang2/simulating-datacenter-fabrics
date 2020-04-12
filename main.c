#include <stdio.h>
#include "flow.c"

int main()
{
    char* filename = "test_cdf.txt";

    // Read and save CDF of flow distribution
    struct FlowNode* flow_dist = init_flow(filename);

    // Generate 100 flows
    float flowsizes[100];
    int i;
    for (i = 0; i < 100; i++)
    {
        flowsizes[i] = get_next_flow(flow_dist);
        printf("%f ", flowsizes[i]);
    }

    return 0;
}