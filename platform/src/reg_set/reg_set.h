#ifndef REG_SET_H
#define REG_SET_H

#include <systemc>
#include <vector>
#include <iomanip>
#include "common/config.h"

class Reg_set {
public:
	Reg_set(const uint &double_reg_num, const uint &single_reg_num = 3);

public:
	/* config bus access */
	void CBSetOPEnable();
	void CBSetWritable(const uint index, const sc_uint<32> &data);
	void CBGetReadable(const uint index, sc_uint<32> &data);
	
	/* engine access*/
	uint GetOPEnable();
	void ClearOPEnable();
	void SetStatusReg(const sc_uint<32> &status);
	void EgSetWritable(const uint index, const sc_uint<32> &data);
	void EgGetReadable(const uint index, sc_uint<32> &data);
	
	/* both can access */
	uint GetConfigGrp();
	uint GetSourceGrp();
	void PrintRegValue();

private:
	void ResetAllReg();

private:
	const uint single_reg_num;
	const uint double_reg_num;

	/*single group*/
	vector<sc_uint<32>> single_reg_set;
	/*duplicated group*/
	vector<sc_uint<32>> double_reg_set_0;
	vector<sc_uint<32>> double_reg_set_1;
};

#endif /*REG_SET_H*/
