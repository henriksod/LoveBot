#include "serial_thread.h"

int create_serial_thread(char* filename)
{
	if (!strcmp(filename, "/dev/(null)")) {
		serial_fd = -1;
	} else {
		serial_fd = serialport_init(filename, 9600);
		if (serial_fd < 0) {
			fprintf(stderr, "error %d opening %s: %s\n", errno,
			filename, strerror(errno));
			return -1;
		}
	}

	set_fd(serial_fd);

	serial_running = true;

	if (pthread_create(&serial_thread, NULL, &start_serial_thread, NULL) != 0) {
		perror("pthread_create\n");
		serial_running = false;
		return -1;
	}

	return 0;
}

int remove_serial_thread() {
	serial_running = false;

	int errorcode = pthread_join(serial_thread, NULL);
	if (serial_fd != STDOUT_FILENO) close(serial_fd);

	return errorcode;
}

void *start_serial_thread(void* arg) {
	fprintf(stdout, "Sleeping for 5 seconds to initialize serial communications\n");
	usleep(5000000);

	while(serial_running) {

		for (int i = 0; i < BUTTON_NO + AXIS_NO - 2; i++) {
			serial_state[i] = controller_state_[i];
		}
		write_state(serial_state, BUTTON_NO + AXIS_NO - 2, 35000);
		
		char buf[50];
		int status = read_ack(buf, 50, 50000);
		switch (status) {
			case -2: // fd not open
				fprintf(stderr, "ACK ERROR: FD not open!\n");
			case -1: // String could not be read
				fprintf(stderr, "ACK ERROR: Ack could not be read!\n");
			case 1: // Timeout
				fprintf(stderr, "ACK ERROR: Timeout!\n");
			default:
				fprintf(stdout, "%s\n", buf);
		}
		
#ifdef DEBUG
		for (uint i = 0; i < BUTTON_NO + AXIS_NO - 2; i++) {
			fprintf(stderr, "%d ", (int)serial_state[i]);
		}
		fprintf(stderr, "\n");
#endif
	}

	return serial_state;
}

void set_controller_state(unsigned char *state) {
        controller_state_ = state;
}

unsigned char *get_serial_state() {
        return serial_state;
}
