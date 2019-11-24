/*
 * OledDisplay.h
 *
 * Created: 11/23/2019 8:45:55 PM
 *  Author: nxf29631
 */ 

#ifndef OLEDDISPLAY_H_
#define OLEDDISPLAY_H_

#define OLED_EN_128_32		1

#define OLED_THREAD_DELAY	1000	

class OledDisplay
{
	public:
		static void OledTaskInit();
		//static void OLEDDisplayTask(void *pvParameters);
	private:
		OledDisplay()
		{}
};


#endif /* OLEDDISPLAY_H_ */