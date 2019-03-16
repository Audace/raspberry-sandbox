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
#include <time.h>

int main(int argc, char **argv)
{
	/*
	 * A variable is a memory location and every memory location has its
	 * address defined which can be accessed using ampersand (&) operator,
	 * which denotes an address in memory.
	 * 
	 * A pointer is a variable whose value is the address of another
	 * variable, i.e., direct address of the memory location. Like any
	 * variable or constant, you must declare a pointer before using it
	 * to store any variable address. 
	*/
	time_t rawtime; // Declare variable "rawtime" of type "time_t"
	struct tm *timeinfo; // Declare pointer to time tm
	
	time(&rawtime); // Returns time measured in seconds stored in rawtime
	timeinfo = localtime(&rawtime); // Assigns formatted value of rawtime
	
	printf("Hello, Raspberry Pi!\n");
	printf("Currently, the time is %s", asctime(timeinfo));
	return 0;
}

