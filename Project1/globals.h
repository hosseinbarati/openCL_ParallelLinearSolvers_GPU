
#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif



cl::Context createContextFromIndex(int pidx, int didx, cl_device_type devtype) {
	std::vector < cl::Device > devices;
	std::vector < cl::Device > device;
	std::vector < cl::Platform > platforms;
	cl::Platform::get(&platforms);
	platforms[pidx].getDevices(devtype, &devices);
	cl_context_properties cps[3] =
	{ CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[pidx])(), 0 };
	device.push_back(devices[didx]);
	return cl::Context(device, cps, NULL, NULL);
}

cl_int SHOW_PLATFORMS_AND_DEVICES() {
	register cl_int i, j;
	std::vector < cl::Platform> platforms;
	std::vector < cl::Device > devices;
	cl::Platform::get(&platforms);
	cl_int numOfPlatforms, numOfDevices;
	numOfPlatforms = cl_int(platforms.size());
	std::cout << "Number of platforms: " << numOfPlatforms << std::endl;

	for (i = 0; i < numOfPlatforms; i++) {
		std::cout << "CL_PLATFORM_VENDOR: " <<
			platforms[i].getInfo <CL_PLATFORM_VENDOR>() << std::endl;
		std::cout << "CL_PLATFORM_NAME: " <<
			platforms[i].getInfo < CL_PLATFORM_NAME >() << std::endl;
		std::cout << "CL_PLATFORM_VERSION: " <<
			platforms[i].getInfo < CL_PLATFORM_VERSION >() << std::endl;
		std::cout << "CL_PLATFORM_PROFILE: " <<
			platforms[i].getInfo < CL_PLATFORM_PROFILE >() << std::endl;
		std::cout << "CL_PLATFORM_EXTENSIONS: " <<
			platforms[i].getInfo < CL_PLATFORM_EXTENSIONS >() << std::endl;
	}

	for (i = 0; i < numOfPlatforms; i++) {
		platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);
		numOfDevices = cl_int(devices.size());
		if (devices.size() > 0) {
			for (j = 0; j < numOfDevices; j++) {
				std::cout << std::endl << "Platform " << i << " , device " << j << std::endl;
				std::cout << "CL_DEVICE_NAME: " << devices[j].getInfo <CL_DEVICE_NAME>() << std::endl;
				std::cout << "CL_DEVICE_VENDOR: " <<
					devices[j].getInfo < CL_DEVICE_VENDOR >() << std::endl;
				std::cout << "CL_DEVICE_MAX_COMPUTE_UNITS: " <<
					devices[j].getInfo < CL_DEVICE_MAX_COMPUTE_UNITS >() << std::endl;
				std::cout << "CL_DEVICE_MAX_CLOCK_FREQUENCY: " <<
					devices[j].getInfo < CL_DEVICE_MAX_CLOCK_FREQUENCY >() << std::endl;
				std::cout << "CL_DEVICE_LOCAL_MEM_SIZE: " <<
					devices[j].getInfo < CL_DEVICE_LOCAL_MEM_SIZE >() << std::endl;
				std::cout << "CL_DEVICE_GLOBAL_MEM_SIZE: " <<
					devices[j].getInfo < CL_DEVICE_GLOBAL_MEM_SIZE >() << std::endl;
			}
		}
	}


	return 0;
}

cl_int SELECT_PLATFORMS_AND_DEVICES(cl_int &pidx, cl_int &didx) {

	std::vector < cl::Platform> platforms;
	std::vector < cl::Device > devices;
	cl::Platform::get(&platforms);
	cl_int maxNumDevices, maxNumPlatforms;
	cl_uint s;
	do {
		s = 0;
		SHOW_PLATFORMS_AND_DEVICES();
		std::cout << std::endl << "SELECT PLATFORM NUMBER: " << std::endl;
		std::cin >> pidx;
		std::cout << "SELECT DEVICE NUMBER: " << std::endl;
		std::cin >> didx;
		if (pidx > int(platforms.size()) - 1) {
			std::cout << "Platform is out of range." << std::endl;
			s = 1;
		} else{
			platforms[pidx].getDevices(CL_DEVICE_TYPE_GPU, &devices);
			if (didx > int(devices.size()) - 1) {
				std::cout << "Device is out of range." << std::endl;
				s = 1;
			}
		}
	} while (s);
	

	return 0;
}