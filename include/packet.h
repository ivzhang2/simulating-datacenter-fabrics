/* Network packet object */
struct packet{
	int send_id; // ID of the sending host
	int receive_id; // ID of the receiving host
	double start_time; // start time of packet
	double wait_time; // wait time of packet
	double size; // size of packet in bytes
}
