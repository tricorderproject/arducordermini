//************************************************************************
// *** usb.h
//************************************************************************
#define _USE_USB_IRQ_

#include	"wiring.h"

//************************************************************************
#define TF_LITTLE(x)  (x)
// enable SODEBUG to enable assert()s; ASSERT()s are always enabled
//#define SODEBUG  1
#define asm_halt()  asm("SDBBP");


#if SODEBUG
	#define assert(x)  do { if (! (x)) { asm_halt(); } } while (0)
#else
	#define assert(x)
#endif

#define ASSERT(x)  do { if (! (x)) { asm_halt(); } } while (0)

#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

//************************************************************************

typedef unsigned long uint32;
typedef unsigned char uint8;

#define SETUP_SIZE					8

#define SETUP_TYPE_STANDARD			0
#define SETUP_TYPE_CLASS			1
#define SETUP_TYPE_VENDOR			2

#define SETUP_RECIP_DEVICE			0
#define SETUP_RECIP_INTERFACE		1
#define SETUP_RECIP_ENDPOINT		2

#define REQUEST_CLEAR_FEATURE		0x01
#define REQUEST_SET_ADDRESS			0x05
#define REQUEST_GET_DESCRIPTOR		0x06
#define REQUEST_GET_CONFIGURATION	0x08
#define REQUEST_SET_CONFIGURATION	0x09

#define DEVICE_DESCRIPTOR			1
#define CONFIGURATION_DESCRIPTOR	2
#define STRING_DESCRIPTOR			3
#define ENDPOINT_DESCRIPTOR			5
#define DEVICE_QUALIFIER_DESCRIPTOR	6

#define TOKEN_STALL					0x0e	// for mst stall disaster

struct setup	{
					byte requesttype;  // 7:in, 6-5:type, 4-0:recip
					byte request;
					short value;
					short index;
					short length;
				};

extern volatile boolean usb_in_isr;		// set when in isr

extern boolean	gCdcacm_attached;		// set when cdcacm host is attached
extern uint32	gCdcacm_attached_count;

extern byte		bulk_in_ep;
extern byte		bulk_out_ep;
extern byte		int_ep;

#ifdef __cplusplus
	extern "C"{
#endif

	//*	call back function definitions
	typedef void	(*usb_reset_cbfn)(void);
	typedef int		(*usb_control_cbfn)(struct setup *setup, byte *buffer, int length);
	typedef int		(*usb_bulk_cbfn)(boolean in, byte *buffer, int length);
	typedef void	(*usb_interrupt_cbfn)(void);



	#define	kUSB_RCB_BuffSize	512
	extern	unsigned char	gRecevieBuffer[];
	extern	unsigned short	gRcbBuff_Head;
	extern	unsigned short	gRcbBuff_Tail;

	// *** device ***

	// enqueue a packet to the usb engine for transfer to/from the host
	void	usb_device_enqueue(int endpoint, boolean tx, byte *buffer, int length);

	void	usb_register(usb_reset_cbfn reset, usb_control_cbfn control_transfer, usb_bulk_cbfn bulk_transfer);
	void	usb_device_descriptor(const byte *descriptor, int length);
	void	usb_configuration_descriptor(const byte *descriptor, int length);
	void	usb_string_descriptor(const byte *descriptor, int length);

	// *** init ***
	void	usb_isr(void);
	void	usb_initialize(void);



#ifdef __cplusplus
} // extern "C"
#endif
