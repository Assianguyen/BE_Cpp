/*!
 * @file DFRobot_LIS2DH12.h
 * @brief DFRobot's Read LIS2DH12 data
 * @n This example achieve receiving LIS2DH12  data via serial
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2016-10-13
 * @https://github.com/DFRobot/DFRobot_LIS2DH12
 */


#ifndef ACCELERO_h
#define ACCELERO_h

#include <stdlib.h>
#include <stdint.h>

const int  lengthTab=100;

class Accelero {
 protected:

  bool isFalling;
  static int16_t deltaValue;
  static int16_t meanValue;
  
public:

  Accelero();
	static uint8_t sensorAddress; ///< IIC address of the sensor
	int8_t init(); ///< Initialization function
	void readZ(int16_t&); ///< read x, y, z data
  int16_t getZ();
  void mgScale(int16_t&);
	uint8_t readValue(uint8_t);
	void fillTab(uint8_t, uint8_t *, uint8_t,bool autoIncrement = true);
	uint8_t writeValue(uint8_t, uint8_t);
	uint8_t writeTab(uint8_t, uint8_t *, size_t, bool autoIncrement = true);
  //void calculateMean();
  //void calculateMean(int16_t&);
  int16_t calculateMean();//THIS ONE WORKS
  int16_t getMeanValue();
  //void calculateDelta();
  int16_t calculateDelta();
  int16_t getDelta();
  bool detectFall();
};	
#endif
