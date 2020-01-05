#include "HardwareDataType.h"
#include <cmath>

#ifdef USE_HALF_FLOAT
#define FLOAT16ArithmeticOperation(DstVar, OP) \
		{RetVal = this->mData.float_16 OP rhs.mData.float_16;}
#else
#define FLOAT16ArithmeticOperation(DstVar, OP) {assert(0 && "not support float16");}
#endif

#define ArithmeticOperationBase(DstVar, OP, FLOAT16MACRO) \
{\
	switch(this->mData_type) {\
	case is_int16: \
		RetVal = static_cast<int16>(this->mData.int_16 OP rhs.mData.int_16); \
		RetVal.mData.int_16 &= 0xFFFF; \
		break; \
	case is_uint16: \
		RetVal = static_cast<uint>(this->mData.uint_16 OP rhs.mData.uint_16); \
		RetVal.mData.uint_16 &= 0xFFFF; \
		break; \
	case is_fixed16: \
		RetVal = static_cast<fixed16>(this->mData.fixed_16 OP rhs.mData.fixed_16);  \
		break; \
	case is_float16: \
        	FLOAT16MACRO \
		break; \
	case is_float32: \
		RetVal = this->mData.float_32 OP rhs.mData.float_32; \
		break; \
	default: assert(0 && "incorrect data type");\
	}\
}
#define ArithmeticOperation(DstVar, OP) ArithmeticOperationBase(DstVar, OP, FLOAT16ArithmeticOperation(DstVar, OP))

#define RelationalOperationBase(DstVar, OP, FLOAT16MACRO) \
{\
	switch(this->mData_type) {\
	case is_int16:\
		DstVar = (this->mData.int_16 OP rhs.mData.int_16); \
		break; \
	case is_uint16: \
		DstVar = (this->mData.uint_16 OP rhs.mData.uint_16); \
		break; \
	case is_fixed16: \
		DstVar = (this->mData.fixed_16 OP rhs.mData.fixed_16); \
		break; \
	case is_float16: \
        	FLOAT16MACRO \
		break; \
	case is_float32: \
		DstVar = (this->mData.float_32 OP rhs.mData.float_32); \
		break; \
	default: assert(0 && "incorrect data type");\
	}\
}

#define RelationalOperation(DstVar, OP) RelationalOperationBase(DstVar, OP, FLOAT16ArithmeticOperation(DstVar, OP))

void HWDataType::CheckDataType() {
	bool type_condition = (mData_type == is_int16)
	                       || (mData_type == is_uint16)
	                       || (mData_type == is_fixed16)
	                       || (mData_type == is_float32);
#ifdef USE_HALF_FLOAT
	type_condition = type_condition || (mData_type == is_float16);
#endif
	assert(type_condition);
}

HWDataType HWDataType::operator*(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	HWDataType RetVal;
	ArithmeticOperation(RetVal, *)
	return RetVal;
}

HWDataType HWDataType::operator/(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	HWDataType RetVal;
	ArithmeticOperation(RetVal, /)
	return RetVal;
}

HWDataType HWDataType::operator-(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	HWDataType RetVal;
	ArithmeticOperation(RetVal, -)
	return RetVal;
}

HWDataType HWDataType::Neg() {
	CheckDataType();
	HWDataType RetVal;
	int zero = 0;
	RetVal.Set<int>(mData_type, zero);
	RetVal = RetVal - *this;
	return RetVal;
}
HWDataType HWDataType::operator+(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	HWDataType RetVal;
	ArithmeticOperation(RetVal, +)
	return RetVal;
}
bool HWDataType::operator==(HWDataType rhs) {
	if (this->mData_type != rhs.mData_type) {
		cout << "type different\n";
		return false;
	}
	bool eq = false;
	RelationalOperation(eq, ==)
	return eq;
}
bool HWDataType::operator!=(HWDataType rhs) {
	const bool ret = (!(this->operator==(rhs)));
	return ret;
}

bool HWDataType::operator<(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	bool less = false;
	RelationalOperation(less, <)
	return less;
}

bool HWDataType::operator>(HWDataType rhs) {
	assert(mData_type == rhs.mData_type);
	CheckDataType();
	bool bigger = false;
	RelationalOperation(bigger, >)
	return bigger;
}

HWDataType HWDataType::operator+=(HWDataType rhs) {
	*this = this->operator+(rhs);
	return *this;
}

int16 HWDataType::operator=(int16 data_value) {
	mData.int_16 = data_value;
	mData_type   = is_int16;
	return data_value;
}

uint HWDataType::operator=(uint data_value) {
	mData.uint_16 = data_value;
	mData_type    = is_uint16;
	return data_value;
}

fixed16 HWDataType::operator=(fixed16 data_value) {
	mData.fixed_16 = data_value;
	mData_type     = is_fixed16;
	return data_value;
}

#ifdef USE_HALF_FLOAT
_Float16 HWDataType::operator=(_Float16 data_value) {
	mData.float_16 = data_value;
	mData_type     = is_float16;
	return data_value;
}
#endif

float HWDataType::operator=(float data_value) {
	mData.float_32 = data_value;
	mData_type     = is_float32;
	return data_value;
}

uint HWDataType::to_uint() {
	CheckDataType();
	uint data(0);
	switch(mData_type) {
	case is_int16:
		data = mData.int_16(15, 0).to_uint();
		break;
	case is_uint16:
		data = mData.uint_16;
		break;
	case is_fixed16:
		data = mData.fixed_16(15, 0).to_uint();
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		data = *reinterpret_cast<uint*>(&mData.float_16);
		break;
#endif
	case is_float32:
		data = *reinterpret_cast<uint*>(&mData.float_32);
		break;
	default: assert(0 && "incorrect data type");
	}
	return data;
}

std::string HWDataType::to_string() {
	CheckDataType();
	stringstream ss;
	string output_string;
	switch(mData_type) {
	case is_int16:
		output_string = mData.int_16.to_string();
		break;
	case is_uint16:
		ss << mData.uint_16;
		output_string = ss.str();
		break;
	case is_fixed16:
		output_string = mData.fixed_16.to_string();
			break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		ss << mData.float_16;
		output_string = ss.str();
		break;
#endif
	case is_float32:
		ss << mData.float_32;
		output_string = ss.str();
		break;
	default: assert(0 && "incorrect data type");
	}
	return output_string;
}

std::string HWDataType::AlignStr() {
	stringstream ss;
	switch(mData_type) {
		case is_int16:
			ss << setw(4);
			break;
		case is_uint16:
			ss << setw(3);
			break;
		case is_fixed16:
			ss << setw(12);
			break;
#ifdef USE_HALF_FLOAT
		case is_float16:
#endif
		case is_float32:
			ss << setw(12);
			break;
		default: assert(0);
	}
	ss << this->to_string();
	return ss.str();
}

void HWDataType::SetBitVec(eDataType type, uint bit_set_value) {
	mData_type = type;
	CheckDataType();
	uint raw_data = bit_set_value;
	switch(type) {
	case is_int16:
		mData.int_16(15, 0) = raw_data & 0xFFFF;
		break;
	case is_uint16:
		mData.uint_16 = raw_data & 0xFFFF;
		break;
	case is_fixed16:
		mData.fixed_16(15, 0) = raw_data & 0xFFFF;
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		mData.float_16 = *reinterpret_cast<_Float16*>(&raw_data);
		break;
#endif
	case is_float32:
		mData.float_32 = *reinterpret_cast<float*>(&raw_data);
		break;
	default: assert(0 && "incorrect data type");
	}
}

template<class T>
void HWDataType::Set(eDataType type, T& data) {
	mData_type = type;
	CheckDataType();
	auto temp_data = static_cast<double>(data);
	switch(type) {
	case is_int16:
		operator=(static_cast<int16>(temp_data));
		break;
	case is_uint16:
		operator=(static_cast<uint>(temp_data));
		break;
	case is_fixed16:
		operator=(static_cast<fixed16>(temp_data));
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		operator=(static_cast<_Float16>(temp_data));
		break;
#endif
	case is_float32:
		operator=(static_cast<float>(temp_data));
		break;
	default: assert(0 && "incorrect data type");
	}
}
template void HWDataType::Set <int16>   (eDataType type, int16& data);
template void HWDataType::Set <uint>    (eDataType type, uint& data);
template void HWDataType::Set <fixed16> (eDataType type, fixed16& data);
#ifdef USE_HALF_FLOAT
template void HWDataType::Set <_Float16>(eDataType type, _Float16& data);
#endif
template void HWDataType::Set <float>   (eDataType type, float& data);
template void HWDataType::Set <double>  (eDataType type, double& data);

template<class T>
T HWDataType::Get() {
	CheckDataType();
	T data;
	switch(mData_type) {
	case is_int16:
		data = static_cast<T>(mData.int_16.to_int());
		break;
	case is_uint16:
		data = static_cast<T>(mData.uint_16);
		break;
	case is_fixed16:
		data = static_cast<T>(mData.fixed_16.to_float());
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		data = static_cast<T>(mData.float_16);
		break;
#endif
	case is_float32:
		data = static_cast<T>(mData.float_32);
		break;
	default: assert(0 && "incorrect data type");
	}
	return data;
}
template int16    HWDataType::Get<int16>();
template uint     HWDataType::Get<uint>();
template fixed16  HWDataType::Get<fixed16>();
#ifdef USE_HALF_FLOAT
template _Float16 HWDataType::Get<_Float16>();
#endif
template float    HWDataType::Get<float>();
template double   HWDataType::Get<double>();

void HWDataType::Randomize(eDataType type) {
	mData_type = type;
	CheckDataType();
	switch(type) {
	case is_int16:
		/* between -9 and 9 */
		operator=(static_cast<int16>((rand() - RAND_MAX / 2) % 10));
		break;
	case is_uint16:
		/* between 0 and 9 */
		operator=(static_cast<uint>(rand() % 10));
		break;
	case is_fixed16:
		/* between -5.0 and 5.0 */
		operator=(static_cast<fixed16>((static_cast<double>(rand() - RAND_MAX / 2) / RAND_MAX) * 2));
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		operator=(static_cast<_Float16>(round((static_cast<double>(rand() - RAND_MAX / 2) / RAND_MAX) * 100) / 100));
		break;
#endif
	/* Preven discard error while computing float data */
	case is_float32:
		operator=(static_cast<float>((rand() - RAND_MAX / 2) % 10));
		break;
	default: assert(0 && "incorrect data type");
	}
}

bool HWDataType::isClose(HWDataType rhs) {
	HWDataType diff = (*this - rhs);
	auto abs_error = std::abs(diff.Get<float>());
	const float error_limit = 1e-5;
	return (abs_error < error_limit);
}

bool HWDataType::is_negative() {
	CheckDataType();
	bool is_neg(false);
	switch(mData_type) {
	case is_int16:
		is_neg = ((mData.int_16 < 0) ? true : false);
		break;
	case is_uint16:
		is_neg = false;
		break;
	case is_fixed16:
		is_neg = mData.fixed_16.is_neg();
	break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		is_neg = ((mData.float_16 < 0.0) ? true : false);
		break;
#endif
	case is_float32:
		is_neg = ((mData.float_32 < 0.0) ? true : false);
		break;
	default: assert(0 && "incorrect data type");
	}
	return is_neg;
}

void HWDataType::SetMaxValue() {
	CheckDataType();
	switch(mData_type) {
	case is_int16:
		mData.int_16(15, 0) = 0x7FFF;
		break;
	case is_uint16:
		mData.uint_16 = 0xFFFF;
		break;
	case is_fixed16:
		mData.fixed_16(15, 0) = 0x7FFF;
	break;
// #ifdef USE_HALF_FLOAT
// 	case is_float16:
// 		mData.float_16 = ;
// 		break;
// #endif
	case is_float32:
		mData.float_32 = std::numeric_limits<float>::max();
		break;
	default: assert(0 && "incorrect data type");
	}
}

void HWDataType::SetMinValue() {
	CheckDataType();
	switch(mData_type) {
	case is_int16:
		mData.int_16(15, 0) = 0x8000;
		break;
	case is_uint16:
		mData.uint_16 = 0;
		break;
	case is_fixed16:
		mData.fixed_16(15, 0) = 0x8000;
	break;
// #ifdef USE_HALF_FLOAT
// 	case is_float16:
// 		mData.float_16 = ;
// 		break;
// #endif
	case is_float32:
		mData.float_32 = std::numeric_limits<float>::lowest();
		break;
	default: assert(0 && "incorrect data type");
	}
}

uint HWDataType::GetSize() {
	return static_cast<uint>(GetDataTypeLength(this->mData_type));
}

void* HWDataType::GetPtr() {
	void* ptr = nullptr;
	switch(mData_type) {
	case is_int16:
		ptr = static_cast<void*>(&(mData.int_16));
		break;
	case is_uint16:
		ptr = static_cast<void*>(&(mData.uint_16));
		break;
	case is_fixed16:
		ptr = static_cast<void*>(&(mData.fixed_16));
		break;
#ifdef USE_HALF_FLOAT
	case is_float16:
		ptr = static_cast<void*>(&(mData.float_16));
		break;
#endif
	case is_float32:
		ptr = static_cast<void*>(&(mData.float_32));
		break;
	default: assert(0 && "incorrect data type");
	}
	return ptr;
}

int GetDataTypeLength(eDataType type) {
	int data_length(0);
	switch(type) {
	case is_int16:
	case is_uint16:
	case is_fixed16:
#ifdef USE_HALF_FLOAT
	case is_float16:
#endif
		data_length = 2;
		break;
	case is_float32:
		data_length = 4;
		break;
	default: assert(0 && "incorrect data type");
	}
	return data_length;
}
