/*
 * USB_CDC_Buffer.c
 *
 *  Created on: Jan 22, 2023
 *      Author: codek
 */

#include "main.h"
#include "USB_CDC_Buffer.h"


USB_CDC_MsgStruct usbRxMsg = {0};
USB_CDC_MsgStruct usbTxMsg = {0};

USB_CDC_ReceiveStatus usbRecStatus = {0};

extern uint8_t UserRxBufferFS;


int USB_CDC_DataIsRdy(USB_CDC_MsgStruct *msg)
{
	int status = 0;

	if(usbRecStatus.dataRdy)
	{
		usbRecStatus.dataRdy = false;
		USB_CDC_AddRxMsg(msg, &UserRxBufferFS, usbRecStatus.dataSize);
	}

	return status;
}

int USB_CDC_AddRxMsg(USB_CDC_MsgStruct *msg, uint8_t *data, uint32_t size)
{
	int status = 0;
	int i;

	if(msg->ptr.iCnt_OverFlow > 0)
	{
		return 1; // overflow
	}

	msg->msgQueue[msg->ptr.iIndexIN].Status.size = size;
	for(i = 0; i < size; i++)
	{
		msg->msgQueue[msg->ptr.iIndexIN].Byte.data[i] = data[i];
	}

	DRV_RingBuffPtr__Input(&msg->ptr, USB_CDC_QUEUE_SIZE);

	return status;
}

int USB_CDC_MsgRdy(USB_CDC_MsgStruct *msg, USB_CDC_Data *msgOut)
{
	int status = 1;
	int i;

	if(msg->ptr.iCnt_Handle)
	{
		msgOut->Status.size = msg->msgQueue[msg->ptr.iIndexOUT].Status.size;
		for(i = 0 ; i < msg->msgQueue[msg->ptr.iIndexOUT].Status.size; i++)
		{
			msgOut->Byte.data[i] = msg->msgQueue[msg->ptr.iIndexOUT].Byte.data[i];
		}
		DRV_RingBuffPtr__Output(&msg->ptr, USB_CDC_QUEUE_SIZE);
	}
	else
	{
		status = 0;
	}

	return status;
}


int USB_CDC_AddTxMsg(USB_CDC_MsgStruct *msg, USB_CDC_Data *msgIn)
{
	int status = 0;
	int i;

	if(msg->ptr.iCnt_OverFlow > 0)
	{
		return 1;
	}

	msg->msgQueue[msg->ptr.iIndexIN].Status.size = msgIn->Status.size;
	for(i = 0; i < msgIn->Status.size; i++)
	{
		msg->msgQueue[msg->ptr.iIndexIN].Byte.data[i] = msgIn->Byte.data[i];
	}
	DRV_RingBuffPtr__Input(&msg->ptr, USB_CDC_QUEUE_SIZE);

	return status;
}

int USB_CDC_SendMsg(USB_CDC_MsgStruct *msg)
{
	int status = 0;

	if(msg->ptr.iCnt_Handle)
	{
		if(CDC_Transmit_FS(&msg->msgQueue[msg->ptr.iIndexOUT].Byte.data, msg->msgQueue[msg->ptr.iIndexOUT].Status.size) == 0)
		{
			DRV_RingBuffPtr__Output(&msg->ptr, USB_CDC_QUEUE_SIZE);
		}
	}

	return status;
}

