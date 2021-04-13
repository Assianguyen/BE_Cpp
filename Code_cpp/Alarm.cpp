#include "Alarm.h"

Alarm::Alarm(){
  alarmOn = false;
}

Alarm::Alarm(bool state){
  alarmOn = state;
}

void Alarm::setAlarmOn(bool state){
	alarmOn = state;
}

bool Alarm::isAlarmOn() {
	return alarmOn;
}
