#include"mOpenCL.h"


int main() {

	cl_device_type devtype = CL_DEVICE_TYPE_GPU;
	//cl_device_type devtype = CL_DEVICE_TYPE_GPU || CL_DEVICE_TYPE_ACCELERATOR;
	mOpenCL openCL_obj(devtype);




	cl_char slp;
	std::cout << "Enter a key to end the program." << std::endl;
	std::cin >> slp;
	return 0;
}

