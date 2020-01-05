#include "reg_set.h"

Reg_set::Reg_set(const uint &double_reg_num, const uint &single_reg_num) :
	single_reg_num(single_reg_num),
	double_reg_num(double_reg_num),
	single_reg_set(single_reg_num),
	double_reg_set_0(double_reg_num),
	double_reg_set_1(double_reg_num)
{
	ResetAllReg();
}

uint Reg_set::GetConfigGrp() {
	return CONFIG_GROUP_REG;
}

uint Reg_set::GetSourceGrp() {
	return SOURCE_GROUP_REG;
}

uint Reg_set::GetOPEnable() {
	if(SOURCE_GROUP_REG == 0) {
		return GROUP_0_OP_ENABLE;
	} else {
		return GROUP_1_OP_ENABLE;
	}
}

void Reg_set::CBSetOPEnable() {
	if(CONFIG_GROUP_REG == 0)
		GROUP_0_OP_ENABLE = 1;
	else
		GROUP_1_OP_ENABLE = 1;

	if((GROUP_0_OP_ENABLE == 1) && (GROUP_1_OP_ENABLE == 1))
		CONFIG_READY_REG = 0;

	CONFIG_GROUP_REG = ~CONFIG_GROUP_REG;
}

void Reg_set::ClearOPEnable() {
	if(SOURCE_GROUP_REG == 0)
		GROUP_0_OP_ENABLE = 0;
	else
		GROUP_1_OP_ENABLE = 0;

	if(CONFIG_READY_REG == 0)
		CONFIG_READY_REG = 1;

	SOURCE_GROUP_REG = ~SOURCE_GROUP_REG;
}

void Reg_set::SetStatusReg(const sc_uint<32> &status) {
	// if(SOURCE_GROUP_REG == 0)
	// 	GROUP_0_STATUS_REG = status;
	// else
	// 	GROUP_1_STATUS_REG = status;
	STATUS_REG = status;
}

void Reg_set::CBSetWritable(const uint index, const sc_uint<32> &data) {
	if(index < single_reg_num)
		single_reg_set[index] = data;
	else {
		if(CONFIG_GROUP_REG == 0)
			double_reg_set_0[index - single_reg_num] = data;
		else
			double_reg_set_1[index - single_reg_num] = data;
	}
}
	
void Reg_set::CBGetReadable(const uint index, sc_uint<32> &data) {
	if(index < single_reg_num)
		data = single_reg_set[index];
	else {
		if(CONFIG_GROUP_REG == 0)
			data = double_reg_set_0[index - single_reg_num];
		else
			data = double_reg_set_1[index - single_reg_num];
	}
}

void Reg_set::EgSetWritable(const uint index, const sc_uint<32> &data) {
	if(index < single_reg_num)
		single_reg_set[index] = data;
	else {
		if(SOURCE_GROUP_REG == 0)
			double_reg_set_0[index - single_reg_num] = data;
		else
			double_reg_set_1[index - single_reg_num] = data;
	}
}

void Reg_set::EgGetReadable(const uint index, sc_uint<32> &data) {
	if(index < single_reg_num)
		data = single_reg_set[index];
	else {
		if(SOURCE_GROUP_REG == 0)
			data = double_reg_set_0[index - single_reg_num];
		else
			data = double_reg_set_1[index - single_reg_num];
	}
}

void Reg_set::PrintRegValue() {
	cout << "\tSingle_Group(" << single_reg_set.size() << ")" << '\n';
	for(uint i = 0; i != single_reg_num; i++) {
		cout << "\t[" << setw(2) << i << "] " << single_reg_set[i].to_string(SC_HEX) << '\n';
	}

	cout << "\n\tDouble_Group_0(" << double_reg_set_0.size() << ")" << '\n';
	for(uint i = 0; i != double_reg_num; i++) {
		cout << "\t[" << setw(2) << i << "] " << double_reg_set_0[i].to_string(SC_HEX) << '\n';
	}

	cout << "\n\tDouble_Group_1(" << double_reg_set_1.size() << ")" << '\n';
	for(uint i = 0; i != double_reg_num; i++) {
		cout << "\t[" << setw(2) << i << "] " << double_reg_set_1[i].to_string(SC_HEX) << '\n';
	}
	cout << endl;
}

void Reg_set::ResetAllReg() {
	if((double_reg_num != 0) && (single_reg_num >= 3)) {
		for(uint i = 0; i != single_reg_num; i++) {
			single_reg_set[i] = (i != 1)? 0 : 1;
		}
	} else {
		for(uint i = 0; i != single_reg_num; i++)
			single_reg_set[i] = 0;
	}

	for(uint i = 0; i != double_reg_num; i++) {
		double_reg_set_0[i] = 0;
		double_reg_set_1[i] = 0;
	}
}
