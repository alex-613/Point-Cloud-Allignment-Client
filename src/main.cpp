/**
* @file main.cpp
* @author Alex Ranne/Hisham Iqbal
* @date 18th of September, 2019
* @brief This is the main file of the project
*
* \mainpage Description
* In the field of Augmented Reality and mixed reality, where lots of decives are involved in creating a believable interavtive environment for the user, it is important that engineers and programmers create a program that
* enables interaction between those devices. In this program, a connectionless UDP (user datagram protocol) is use to transmit small amounts of critical data, in order to optimize the hologram projections by the hololens.
* The optimization is done through the use of the method of least squares. This is a common method used for coordinate mapping and optimizing positions of various coordinate systems within a 3D space. Given two or more point clouds, expressed in their coordinate system
* and the geometric relation between them is unknown, then a mamized rotation matrix and translation vector must be found using quaternion mathematics, SVD and matrix algebra, eigen value method, or iteration(trial and error).
* This program is written to weave the sending/receiving and calculation process together. Note that this is the client (sending) side of the connection.
*
* \section library_sec Libraries used in this project
* \subsection library1 The Winsock WS2tcpip.h library
* This library enables the program to utilize the powerful windows sockets functions, such as socket binding, conversion from big to little endian, sending and receiving char arrays from specific ip addresses and more.
*
* \subsection library2 Eigen
* The Eigen library is a very powerful, header only library that has lots of built in matrix manipulation tools. Such as transposing, inversing, conducting SVD, enabling functions to return the Matrix type, etc etc.
*
*
* \section code_sec Code in main.cpp breakdown
* @code
*	std::vector<std::string> strvect1 = functions::mat2str(R1);
*	std::vector<std::string> strvect2 = functions::mat2str(R2);
* @endcode
* This function turns any matrix into a string vector, with each element of the matrix turned into a string, stored in an element in the vector
*
* @code
*std::string bufstr1= "";
*std::string bufstr2 = "";
*
*for (int i = 0; i < strvect1.size(); i++) {
*	bufstr1.append(strvect1[i]);
*	bufstr1.append(",");
*	bufstr2.append(strvect2[i]);
*	bufstr2.append(",");
*}
*@endcode
* Takes each element within the string vector and append it onto a string, seperated by delimeters.
*
*@code
*	char buf1[512];
*	char buf2[512];
*	int buflen = 512;
*	memset(buf1, NULL, 512);
*	memset(buf2, NULL, 512);
*
*	for (int i = 0; i < 512;i++){
*		buf1[i] = bufstr1[i];
*		buf2[i] = bufstr2[i];
*	}
*@endcode
* Turning the buffer strings into character arrays, which is the format that the send and recv functions in winsock accepts.
*
* @code
* functions::initialization();
* @endcode
* Call the init function which starts winsock, allowing us to create, bind sockets. See functions.cpp
*
* @code
*	sockaddr_in server;
*
*	server.sin_family = AF_INET; // AF_INET = IPv4 addresses
*	server.sin_port = htons(54000); // Little to big endian conversion
*	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // Convert from string to byte array
* @endcode
* Initialize the sockaddr structure called server which is needed for sending messages
* Then since the server is big endian and the PC is little endian, we will use htons on channel 54000 to do this conversion.
*
*@code
*	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
*@endcode
*  Create a UDP style socket called out.
*
*@code
*	sendto(out, buf1, buflen + 1, 0, (sockaddr*)& server, sizeof(server));
*	sendto(out, buf2, buflen + 1, 0, (sockaddr*)& server, sizeof(server));
*@endcode
*Use the built in sendto function with winsock that sends the buffer messages
*
*@code
*	functions::termination(out);
*@endcode
*Close everything and end the program
*
*/
#include <iostream>
#include <WS2tcpip.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <stdio.h>
#include <vector>
#include <string>
#include "functions.h"

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")

int main() 
{
	// Testing with random matrix

	Eigen::Matrix3d R1;
	R1 << 0.3, 0.5, 0.7,
		0.1, 0.9, 0.4,
		0.3, 0.6, 0.1;

	Eigen::Matrix3d R2;
	R2 << 0.8, 0.1, 0.2,
		0.1, 0.4, 0.3,
		0.5, 0.5, 0.2;

	std::cout << R1 << std::endl;
	std::cout << "\n" << R2 << std::endl;

	std::vector<std::string> strvect1 = functions::mat2str(R1);
	std::vector<std::string> strvect2 = functions::mat2str(R2);


	//Turn it into a single string
	std::string bufstr1 = "";
	std::string bufstr2 = "";

	for (int i = 0; i < strvect1.size(); i++) {
		bufstr1.append(strvect1[i]);
		bufstr1.append(",");
		bufstr2.append(strvect2[i]);
		bufstr2.append(",");

	}

	//std::cout << bufstr1<< std::endl;
	//std::cout << bufstr2 << std::endl;

	char buf1[512];
	char buf2[512];
	int buflen = 512;
	memset(buf1, NULL, 512);
	memset(buf2, NULL, 512);

	for (int i = 0; i < bufstr1.length(); i++) {
		buf1[i] = bufstr1[i];		
	}

	for (int i = 0; i < bufstr2.length(); i++)
	{
		buf2[i] = bufstr2[i];
	}

	////////////////////////////////////////////////////////////
	// INITIALIZE WINSOCK
	////////////////////////////////////////////////////////////

	functions::initialization();

	////////////////////////////////////////////////////////////
	// CONNECT TO THE SERVER
	////////////////////////////////////////////////////////////

	// Create a hint structure for the server

	sockaddr_in server;

	server.sin_family = AF_INET; // AF_INET = IPv4 addresses
	server.sin_port = htons(54000); // Little to big endian conversion
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // Convert from string to byte array

	// Socket creation, note that the socket type is datagram
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	// Send
	sendto(out, buf1, buflen + 1, 0, (sockaddr*)& server, sizeof(server));
	sendto(out, buf2, buflen + 1, 0, (sockaddr*)& server, sizeof(server));


	functions::termination(out);

	system("PAUSE");
}