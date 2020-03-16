#include<vector>
#include<string>
#include<iostream>


#include"globals.h"




int main() {

	register cl_int i, j;
	cl_int pidx, didx;
	std::string platformName, deviceName;
	SELECT_PLATFORMS_AND_DEVICES(pidx, didx);
	cl::Context context1;
	context1 = createContextFromIndex(pidx, didx, CL_DEVICE_TYPE_GPU);
	ContextDevice(context1);
	
	


	cl_char slp;
	std::cout << "Enter a key to end the program." << std::endl;
	std::cin >> slp;
	return 0;
}

