/**
* @file functions.cpp
* @author Alex Ranne/Hisham Iqbal
* @data 18th of September, 2019
* @brief This file consists of all the function definitions. Most definitions uses the Eigen library to manipulate
* martices and performs matrix algebra. Or uses Winsock library to initialize a UDP connection.
*
*
*
*/



#include "functions.h"
#include <string>

std::vector<std::string> functions::mat2str(Eigen::MatrixXd Mat) {
	std::vector<std::string> matvect;

	for (int i = 0; i < Mat.rows(); i++) {
		for (int j = 0; j < Mat.cols(); j++) {
			matvect.push_back(std::to_string(Mat(i, j)));
		}
	}

	return matvect;
}

void functions::initialization() {
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOK = WSAStartup(version, &data);

	if (wsOK != 0) {
		//Error check
		std::cout << "Can't start Winsock!" << wsOK << std::endl;
		return;
	}
}

void functions::termination(SOCKET out) {
	closesocket(out);
	WSACleanup();
}