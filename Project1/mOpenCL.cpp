#include "mOpenCL.h"




mOpenCL::mOpenCL(cl_device_type devtype)
{
	//register cl_int i, j;
	this->devtype = devtype;
	SELECT_PLATFORMS_AND_DEVICES(pidx, didx, devtype);
	
	context1 = createContextFromIndex(pidx, didx, devtype);
	ContextDevice(context1);

	try {
		cl::CommandQueue queue = cl::CommandQueue(context1, context1.getInfo<CL_CONTEXT_DEVICES>()[0], CL_QUEUE_PROFILING_ENABLE);
	}
	catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}

}


mOpenCL::~mOpenCL(){}

cl::Context mOpenCL::createContextFromIndex(int pidx, int didx, cl_device_type devtype) {
	std::vector < cl::Device > devices;
	std::vector < cl::Device > device;
	std::vector < cl::Platform > platforms;
	try {
		cl::Platform::get(&platforms);
	}
	catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}
	try {
		platforms[pidx].getDevices(devtype, &devices);
	}
	catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}
	cl_context_properties cps[3] =
	{ CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[pidx])(), 0 };
	device.push_back(devices[didx]);
	cl::Context context;
	try {
		context = cl::Context(device, cps, NULL, NULL);
	}
	catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}

	return context;
}

cl_int mOpenCL::SHOW_PLATFORMS_AND_DEVICES() {
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
				std::cout << std::endl << "Platform " << i << " , Device " << j << std::endl;
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

cl_int mOpenCL::SELECT_PLATFORMS_AND_DEVICES(cl_int &pidx, cl_int &didx, cl_device_type devtype) {

	std::vector < cl::Platform> platforms;
	std::vector < cl::Device > devices;
	try {
		cl::Platform::get(&platforms);
	}
	catch (cl::Error &e) {
		std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
	}

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
		}
		else {
			try {
				platforms[pidx].getDevices(devtype, &devices);

			}
			catch (cl::Error &e) {
				std::cout << "Error in function " << e.what() << ": " << e.err() << std::endl;
			}
			if (didx > int(devices.size()) - 1) {
				std::cout << "Device is out of range." << std::endl;
				s = 1;
			}
		}
	} while (s);


	return 0;
}

cl_int mOpenCL::ContextDevice(cl::Context & context) {
	std::vector < cl::Device > devices = context.getInfo<CL_CONTEXT_DEVICES>();
	if (devices.size() > 0) {
		for (size_t i = 0; i < devices.size(); i++) {
			std::cout << "Device " << i << std::endl;
			std::cout << "CL_DEVICE_NAME: " <<
				devices[i].getInfo <CL_DEVICE_NAME>() << std::endl;
			std::cout << "CL_DEVICE_VENDOR: " <<
				devices[i].getInfo < CL_DEVICE_VENDOR >() << std::endl;
		}
	}
	return 0;
}







