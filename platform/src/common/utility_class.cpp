#include "utility_class.h"

EyerissMappingParamter::EyerissMappingParamter
(uint n, uint e , uint p, uint q, uint r, uint t, uint m) :
	proc_pass_ifmap_num(n),
	pe_set_width(e),
	pe_set_flt_num(p),
	pe_set_ch_num(q),
	diff_ch_pe_set_num(r),
	diff_flt_pe_set_num(t),
	stored_ofmap_ch_num(m)
{}

uint EyerissMappingParamter::EncodeParameter() const{
	const uint MaxVal2bit = 0x3;
	const uint MaxVal3bit = 0x7;
	const uint MaxVal5bit = 0x1F;
	const uint MaxVal7bit = 0x7F;
	assert(proc_pass_ifmap_num <= MaxVal3bit);
	assert(pe_set_width <= MaxVal5bit);
	assert(pe_set_flt_num <= MaxVal5bit);
	assert(pe_set_ch_num <= MaxVal3bit);
	assert(diff_ch_pe_set_num <= MaxVal2bit);
	assert(diff_flt_pe_set_num <= MaxVal3bit);
	assert(stored_ofmap_ch_num <= MaxVal7bit);
	auto hint = (proc_pass_ifmap_num & 0x7)
	             | ((pe_set_width & 0x1F) << 3)
	             | ((pe_set_flt_num & 0x1F) << 8)
	             | ((pe_set_ch_num & 0x7) << 13)
	             | ((diff_ch_pe_set_num & 0x3) << 16)
	             | ((diff_flt_pe_set_num & 0x7) << 18)
	             | ((stored_ofmap_ch_num & 0x7F) << 21);
	return hint;
}

shape_t::shape_t(uint n_, uint c_, uint h_, uint w_) :
	n(n_), c(c_), h(h_), w(w_)
{}

shape_t::shape_t() :
	n(1), c(1), h(1), w(1)
{}

shape_t::shape_t(int64_t* ptr, int num) :
	n(1), c(1)
{
	put(ptr, num);
}

std::string shape_t::to_str(std::string prefix) {
	std::stringstream ss;
	ss << prefix << "number:" << n << ", ";
	ss << prefix << "channel:" << c << ", ";
	ss << prefix << "height:" << h << ", ";
	ss << prefix << "width:" << w;
	return ss.str();
}

uint shape_t::size() {
	assert(n>=1);
	assert(c>=1);
	assert(h>=1);
	assert(w>=1);
	return n*c*h*w;
}

void shape_t::put(int64_t* ptr, int num) {
	if (num == 2) {
		h = ptr[0];
		w = ptr[1];
	} else if (num == 3) {
		c = ptr[0];
		put(ptr+1, num-1);
	} else if (num == 4) {
		n = ptr[0];
		put(ptr+1, num-1);
	} else {
		assert(0);
	}
}

shape_t shape_t::to_strides() {
	uint stride_w = 1;
	uint stride_h = w;
	uint stride_c = h * w;
	uint stride_n = c * h * w;
	return shape_t(stride_n, stride_c, stride_h, stride_w);
}

uint shape_t::Idx(uint ni, uint ci, uint hi, uint wi, shape_t* strides) {
	// If no given strides, then assume it is continue
	auto continue_stride = this->to_strides();
	shape_t stride = strides ? *strides : continue_stride;
	auto offset = ni * stride.n
		+ ci * stride.c
		+ hi * stride.h
		+ wi * stride.w;
	return offset;
}