#pragma once

#include <string>
#include <sstream>
#include <assert.h>

using uint = unsigned int;

class EyerissMappingParamter {
public:
	EyerissMappingParamter(uint n = 1, uint e = 14 , uint p = 1, uint q = 1,
	                       uint r = 1, uint t = 1, uint m = 1);

	uint EncodeParameter() const;
	
	/*n*/ uint proc_pass_ifmap_num;
	/*e*/ uint pe_set_width;
	/*p*/ uint pe_set_flt_num;
	/*q*/ uint pe_set_ch_num;
	/*r*/ uint diff_ch_pe_set_num;
	/*t*/ uint diff_flt_pe_set_num;
	/*m*/ uint stored_ofmap_ch_num;
};

class shape_t {
public:
	uint n;
	uint c;
	uint h;
	uint w;

	shape_t(uint n_, uint c_, uint h_, uint w_);
	shape_t();
	shape_t(int64_t* ptr, int num);

	std::string to_str(std::string prefix="");
	uint size();
	void put(int64_t* ptr, int num);
	shape_t to_strides();
	uint Idx(uint ni, uint ci, uint hi, uint wi, shape_t* strides=nullptr);
};
