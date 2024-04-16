/*
 * PollingRoutine.c
 *
 *  Created on: Jan 22, 2023
 *      Author: codek
 */


#include "main.h"
#include "PollingRoutine.h"

extern USB_CDC_MsgStruct usbRxMsg;
extern USB_CDC_MsgStruct usbTxMsg;

void PollingInit(void)
{

}

void PollingRoutine(void)
{
	USB_CDC_DataIsRdy(&usbRxMsg); // saves data to message buffer

	USB_CDC_ParseMsg(&usbRxMsg);

	USB_CDC_SendMsg(&usbTxMsg);
}


void USB_CDC_ParseMsg(USB_CDC_MsgStruct *msg)
{
	USB_CDC_Data msgOut = {0};

	if(USB_CDC_MsgRdy(msg, &msgOut))
	{
		USB_CDC_AddTxMsg(&usbTxMsg, &msgOut);
	}
}

