/*
 * PollingRoutine.h
 *
 *  Created on: Jan 22, 2023
 *      Author: codek
 */

#ifndef INC_POLLINGROUTINE_H_
#define INC_POLLINGROUTINE_H_


void PollingInit(void);
void PollingRoutine(void);

void USB_CDC_ParseMsg(USB_CDC_MsgStruct *msg);


#endif /* INC_POLLINGROUTINE_H_ */
