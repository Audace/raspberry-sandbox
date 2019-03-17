/*
 * main.c
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{
	inquiry_info *ii = NULL;
	
	int max_rsp, num_rsp;
	int dev_id, sock, len, flags;
	int i;
	
	char addr[19] = { 0 };
	char name[248] = { 0 };
		
	/*
	 * Local Bluetooth adapters are assigned identifying numbers starting
	 * at 0. A program must specify which adapter to use. Usually there's
	 * only one adapter (or it doesn't matter), so passing NULL will
	 * retreive the resource number of the first adapter available.
	*/ 
	dev_id = hci_get_route(NULL);
	printf("Using bluetooth adapter with id %i\n", dev_id);
	
	/*
	 * The below is a convenience function that opens a Bluetooth socket
	 * with the specified adapter. The socket isn't a connection to a
	 * remote device but to the microcontroller on the Raspberry Pi's
	 * Bluetooth adapter.
	*/
	sock = hci_open_dev( dev_id );
	printf("Opened socket to bluetooth microcontroller\n");
	
	if (dev_id < 0 || sock < 0) {
	  perror("Opening socket"); // Prints textual description of error
	  exit(1);
	}
	
	len = 8; // Length of time in s (* 1.24) to wait for inquiry results
	max_rsp = 255; // Maximum number of devices to be returned
	flags = IREQ_CACHE_FLUSH; // Flush cache of previously found devices
	ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info)); // Alloc enough memory for max_resp
	
	printf("Searching for bluetooth devices...\n");
	num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
	printf("Found %d devices\n", num_rsp);
	
	if (num_rsp < 0) perror("HCI Inquiry");
	
	for (i = 0; i < num_rsp; i++) {
		ba2str(&(ii+i)->bdaddr, addr); // Convert bdaddr to string and set addr
		memset(name, 0, sizeof(name)); // Overwrite value of name to all 0's
		if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
		    name, 0) < 0) strcpy(name, "[unknown]");
		printf("%s  %s\n", addr, name); // Print out addr and name for device found
	}
	
	free( ii ); // Free memory from inquiry information
	close( sock ); // Close socket to microcontroller
	return 0;
}

