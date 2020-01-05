#include "reg_set.h"

#define SINGLE_REG_NUM 3
#define DOUBLE_REG_NUM 5

void Initialize();
void CBSetOPEnable();
void ClearOPEnable();
void SetStatusReg(const sc_uint<32> &status);
void CBSetWritable();
void CBGetReadable();
void GetOPEnable();
void EgSetWritable();
void EgGetReadable();

Reg_set reg(DOUBLE_REG_NUM);

int sc_main(int argc, char* argv[]) {
	Initialize();         /* simulating config flow below */
	CBGetReadable();      /* micro-controller checks config-ready before writes 1st config */
	CBSetWritable();      /* micro-controller writes 1st config */
	CBSetOPEnable();      /* micro-controller enables 1st config */
	GetOPEnable();        /* engine reads 1st OP_Enable */
	EgGetReadable();      /* engine get 1st config */
	SetStatusReg(0x1010); /* engine starts computing and set status according to the enabled 1st config */
	EgSetWritable();      /* engine sets writable for some reason */
	CBGetReadable();      /* micro-controller checks config-ready before writes 2nd config */
	CBSetWritable();      /* micro-controller writes 2nd config */
	CBSetOPEnable();      /* micro-controller enables 2nd config */
	SetStatusReg(0x0);    /* engine ends computing and set status to 1st config */
	ClearOPEnable();      /* engine disables 1st config */
	GetOPEnable();        /* engine reads 2nd OP_Enable */
	EgGetReadable();      /* engine get 2nd config */
	SetStatusReg(0x1100); /* engine starts computing and set status according to the enabled 2nd config */
	SetStatusReg(0x0);    /* engine ends computing and set status to 2nd config */
	ClearOPEnable();      /* engine disables 2nd config */

	sc_start();
	return 0;
}

void Initialize(){
	cout << "== Initial ==\n\n";
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();
}

void CBSetOPEnable(){
	cout << "== Set_OP_Enable ==\n\n";
	reg.CBSetOPEnable();
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();
}

void ClearOPEnable(){
	cout << "== Clear_OP_Enable ==\n\n";
	reg.ClearOPEnable();
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();

}

void SetStatusReg(const sc_uint<32> &status){
	cout << "== Set_Status ==\n\n";
	reg.SetStatusReg(status);
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();
}

void CBSetWritable(){
	cout << "== CB_Set_Writable ==\n\n";
	for(uint i = SINGLE_REG_NUM + 1; i < SINGLE_REG_NUM + DOUBLE_REG_NUM; i++) {
		sc_uint<32> data(1 << i);
		reg.CBSetWritable(i, data);
	}
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();
}

void CBGetReadable(){
	cout << "== CB_Get_Readable ==\n\n";
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	for(uint i = 0; i < SINGLE_REG_NUM + DOUBLE_REG_NUM; i++) {
		sc_uint<32> data(0);
		reg.CBGetReadable(i, data);

		if(i == 0)
			cout << "\tSingle_Group(" << SINGLE_REG_NUM << ")\n";
		else if (i == SINGLE_REG_NUM) {
			if(reg.GetConfigGrp() == 0)
				cout << "\n\tDouble_Group_0(" << DOUBLE_REG_NUM << ")\n";
			else
				cout << "\n\tDouble_Group_1(" << DOUBLE_REG_NUM << ")\n";
		}
		
		if(i < SINGLE_REG_NUM)
			cout << "\t[" << setw(2) << i << "] " << data.to_string(SC_HEX) << '\n';
		else
			cout << "\t[" << setw(2) << i - SINGLE_REG_NUM << "] " << data.to_string(SC_HEX) << '\n';
	}
	cout << endl;
}

void GetOPEnable() {
	cout << "== Get_OP_Enable ==\n\n";
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	if(reg.GetSourceGrp() == 0)
		cout << "\tOP_Enable_0 = " << reg.GetOPEnable() << '\n';
	else
		cout << "\tOP_Enable_1 = " << reg.GetOPEnable() << '\n';
	cout << endl;
}

void EgSetWritable() {
	cout << "== Engine_Set_Writable ==\n\n";
	
	sc_uint<32> data(0x1111);
	reg.EgSetWritable(7, data);

	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	reg.PrintRegValue();
}

void EgGetReadable() {
	cout << "== Engine_Get_Readable ==\n\n";
	cout << "\tConfig_Group = " << reg.GetConfigGrp() << "\n\tSource_Group = " << reg.GetSourceGrp() << "\n\n";
	for(uint i = 0; i < SINGLE_REG_NUM + DOUBLE_REG_NUM; i++) {
		sc_uint<32> data(0);
		reg.EgGetReadable(i, data);

		if(i == 0)
			cout << "\tSingle_Group(" << SINGLE_REG_NUM << ")\n";
		else if (i == SINGLE_REG_NUM) {
			if(reg.GetSourceGrp() == 0)
				cout << "\n\tDouble_Group_0(" << DOUBLE_REG_NUM << ")\n";
			else
				cout << "\n\tDouble_Group_1(" << DOUBLE_REG_NUM << ")\n";
		}
		
		if(i < SINGLE_REG_NUM)
			cout << "\t[" << setw(2) << i << "] " << data.to_string(SC_HEX) << '\n';
		else
			cout << "\t[" << setw(2) << i - SINGLE_REG_NUM << "] " << data.to_string(SC_HEX) << '\n';
	}
	cout << endl;
}
