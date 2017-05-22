/* CAN msgs
 * Warren W. Gay VE3WWG
 * Sat May 20 17:13:28 2017
 */
#ifndef CANMSGS_H
#define CANMSGS_H

#include <stdint.h>

#include <libopencm3/stm32/can.h>

#include "task.h"
#include "queue.h"

#define PARM_SJW	CAN_BTR_SJW_1TQ
#define PARM_TS1	CAN_BTR_TS1_6TQ
#define PARM_TS2	CAN_BTR_TS2_7TQ
#define PARM_BRP	78		// 33.333 kbps

struct s_canmsg {
	uint32_t	msgid;		// Message ID
	uint32_t	fmi;		// Filter index
	uint8_t		length;		// Data length
	uint8_t		data[8];	// Received data
	uint8_t		xmsgidf : 1;	// Extended message flag
	uint8_t		rtrf : 1;	// RTR flag
	uint8_t		fifo : 1;	// RX Fifo 0 or 1
};

enum MsgID {
	ID_LeftEn = 100,		// Left signals on/off (s_lamp_en)
	ID_RightEn,			// Right signals on/off (s_lamp_en)
	ID_ParkEn,			// Parking lights on/off (s_lamp_en)
	ID_HeartBeat = 200		// Heartbeat signal (s_lamp_status)
};

struct s_lamp_en {
	uint8_t		enable : 1;	// 1==on, 0==off
	uint8_t		reserved : 1;
};

struct s_lamp_status {
	uint8_t		left : 1;	// Left signal on
	uint8_t		right : 1;	// Right signal on
	uint8_t		park : 1;	// Parking lights on
	uint8_t		reserved : 5;
};

void initialize_can(bool nart,bool locked);
void can_recv(struct s_canmsg *msg);
void can_xmit(uint32_t id,bool ext,bool rtr,uint8_t length,void *data);

#endif // CANMSGS_H

// canmsgs.h
