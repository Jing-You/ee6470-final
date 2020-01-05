#include <iostream>
#include <cstring>
#include <iomanip>
#include "common/config.h"
#include "ctrler_api/ctrler_api.h"

int main(int argc, char *argv[]) {
	ControllerAPI controller;

	eActFunction act_function(is_relu);
	eDataType HWDtype(is_int16);
	uint data_channel(3);
	uint data_width(2);
	uint data_height(2);

	uint test_data_num(data_channel * data_width * data_height);
	short test_data[test_data_num] =
		{12, 56, -32, -5, 5, -55, 56, 90, 75, 10, -11, -5};
	short result_data[test_data_num];

	/* Load test data to act. buffer */
	controller.DebugWriteData(ACT_BUFFER_0_ADDRESS,
	                          reinterpret_cast<unsigned char*>(&test_data),
	                          test_data_num * sizeof(short));

	/* Check config ready */
	while(controller.ReadConfigReady(is_act_engine_0) == 0) {}

	/* Program config registers */
	controller.ProgramActReg(is_act_engine_0, act_function, HWDtype,
	                         ACT_BUFFER_0_ADDRESS, ACT_BUFFER_0_ADDRESS,
	                         data_channel, data_height, data_width);
	
	/* Set OP_Enable */
	controller.SetOPEnable(is_act_engine_0);

	/* Check status till process is done */
	while(controller.ReadStatus(is_act_engine_0) != 0) {}

	/* Get result data */
	controller.DebugReadData(ACT_BUFFER_0_ADDRESS,
	                         reinterpret_cast<unsigned char*>(&result_data),
	                         test_data_num * sizeof(short));

	/* Print result data */
	for(int i = 0; i < test_data_num; i++) {
		cout << setw(2) << i + 1 << ". " << setw(3) << test_data[i]
		     << " -> " << setw(3) << result_data[i] << '\n';
	}
	cout << endl;

	return 0;
}
