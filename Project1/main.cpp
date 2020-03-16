#include<vector>
#include<string>
#include<iostream>


#include"openCL_Host.h"




int main() {

	register cl_int i, j;
	cl_int pidx, didx;
	cl_device_type devtype = CL_DEVICE_TYPE_GPU;
	//cl_device_type devtype = CL_DEVICE_TYPE_GPU || CL_DEVICE_TYPE_ACCELERATOR;
	std::string platformName, deviceName;
	SELECT_PLATFORMS_AND_DEVICES(pidx, didx, devtype);
	cl::Context context1;
	context1 = createContextFromIndex(pidx, didx, devtype);
	ContextDevice(context1);
	try {
		cl::CommandQueue queue = cl::CommandQueue(context1, context1.getInfo<CL_CONTEXT_DEVICES>()[0], CL_QUEUE_PROFILING_ENABLE);
	} catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}




	cl_char slp;
	std::cout << "Enter a key to end the program." << std::endl;
	std::cin >> slp;
	return 0;
}

