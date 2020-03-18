#pragma once

#define __CL_ENABLE_EXCEPTIONS
//#define __CL_USER_OVERRIDE_ERROR_STRINGS


#include <cstdlib>
#include <iostream>
#include<vector>
#include<string>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif


class mOpenCL
{
public:
	mOpenCL(cl_device_type devtype);
	~mOpenCL();

	cl::Context createContextFromIndex(int pidx, int didx, cl_device_type devtype);
	cl_int SHOW_PLATFORMS_AND_DEVICES();
	cl_int SELECT_PLATFORMS_AND_DEVICES(cl_int &pidx, cl_int &didx, cl_device_type devtype);
	cl_int ContextDevice(cl::Context & context);

private:
	cl::Context context1;
	cl_device_type devtype;
	//std::string platformName, deviceName;
	cl_int pidx, didx;
};

