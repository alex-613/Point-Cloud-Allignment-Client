/**
* @file functions.h
* @author Alex Ranne/Hisham Iqbal
* @date 18th of September, 2019
* @brief Functions header file of the project, declears all functions used.
*
*
*
*
*/

#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <WS2tcpip.h>

class functions 
{
public:
	static std::vector<std::string> mat2str(Eigen::MatrixXd Mat);
	static void initialization();
	static void termination(SOCKET out);
};