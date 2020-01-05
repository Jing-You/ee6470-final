#pragma once

#include <systemc>
#include "common/config.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>

class HWDataType {
public:
	HWDataType(eDataType type = none) : mData_type(type) {}
	~HWDataType() {}

private:
	class type_value {
	public:
		int16          int_16;
		uint           uint_16;
		fixed16        fixed_16;
#ifdef USE_HALF_FLOAT
		_Float16 float_16;
#endif
		float          float_32;
	};
	
	type_value mData;
	eDataType  mData_type;

public:
	void CheckDataType();
	HWDataType operator*(HWDataType rhs);
	HWDataType operator/(HWDataType rhs);
	HWDataType operator+(HWDataType rhs);
	HWDataType operator-(HWDataType rhs);
	HWDataType operator+=(HWDataType rhs);
	bool operator==(HWDataType rhs);
	bool operator!=(HWDataType rhs);
	bool operator<(HWDataType rhs);
	bool operator>(HWDataType rhs);
	int16 operator=(int16 data_value);
	uint operator=(uint data_value);
	fixed16 operator=(fixed16 data_value);
#ifdef USE_HALF_FLOAT
	_Float16 operator=(_Float16 data_value);
#endif
	float operator=(float data_value);
	HWDataType Neg();
	bool isClose(HWDataType rhs);
	uint to_uint();
	std::string to_string();
	std::string AlignStr();
	void SetBitVec(eDataType type, uint bit_set_value);
	template<class T>
		void Set(eDataType type, T& data);
	template<class T>
		T Get();
	void Randomize(eDataType type);
	bool is_negative();
	void SetMaxValue();
	void SetMinValue();
	void* GetPtr();
	uint GetSize();
};

// handy type
using HWDataVec = std::vector<HWDataType>;

/* Useful methods */
int GetDataTypeLength(eDataType type);
