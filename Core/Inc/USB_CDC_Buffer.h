/*
 * USB_CDC_Buffer.h
 *
 *  Created on: Jan 22, 2023
 *      Author: codek
 */

#ifndef INC_USB_CDC_BUFFER_H_
#define INC_USB_CDC_BUFFER_H_


#define USB_CDC_QUEUE_SIZE 8


typedef union
{
	struct
	{
		uint8_t data[24];
	}Byte;
	struct
	{
		uint8_t id;
		uint8_t data[24 - 1];
		uint32_t size;
	}Status;
}USB_CDC_Data;


typedef struct
{
	USB_CDC_Data msgQueue[USB_CDC_QUEUE_SIZE];
	RING_BUFF_INFO ptr;
}USB_CDC_MsgStruct;


typedef struct
{
	bool dataRdy;
	uint32_t dataSize;
}USB_CDC_ReceiveStatus;


int USB_CDC_DataIsRdy(USB_CDC_MsgStruct *msg);
int USB_CDC_AddRxMsg(USB_CDC_MsgStruct *msg, uint8_t *data, uint32_t size);
int USB_CDC_MsgRdy(USB_CDC_MsgStruct *msg, USB_CDC_Data *msgOut);

int USB_CDC_AddTxMsg(USB_CDC_MsgStruct *msg, USB_CDC_Data *msgIn);
int USB_CDC_SendMsg(USB_CDC_MsgStruct *msg);


#endif /* INC_USB_CDC_BUFFER_H_ */
