#pragma once
#include "pch.h"

#include <bitset>

using std::bitset;

namespace mini {

	struct iReg {
		union {
			int8   hx;
			int16   x;
			int32  dx;
			int64 edx;
		};
	};

	

	typedef double fpReg;

	enum CSP_BITS {
		SIGN = 0,
		EQ,
		GTH,
		LTH,
		GE,
		LE,
		CPU_ON,
		PGM_ERR
	};

	/*
	*	REGISTERS:
	*		A    (HA, A, DA, EAX) { HalfA, A, DoubleA, FullA }
	*		B
	*		C
	*		D
	*		E
	*		F
	*		R0
	*		R1
	*		R2
	*		R3
	* 
	*		IP
	*		JLP  (jump link pointer)
	*		SH   (Stack Head)
	*		SB   (Stack Base)
	*		
	*		
	* 
	*		CSP
	*	
	*		F0 // floating point (double width)
	*		F1
	*		F2
	*		F3
	*		F4
	*		F5
	*		F6
	*		F7
	*		
	*	MEM Layout
	* 
	*		[PROGRAM HEADER : FIXED ]
	*		[ERR INDEX : FIXED 64 Addresses { 256 bytes }]
	*		[STATIC DATA]
	*		[PROGRAM DATA]
	*		[PADDING]
	*		[HEAP]
	*		[STACK HEAD]
	*		[STACK BASE]
	*
	*	PROGRAM HEADER
	*		[0x01][0x03][0x06][VM_MAJOR][VM_MINOR]{DATA WIDTH (4bytes)}{PROGRAM WIDTH (4bytes)}{HEAPSTACK_WIDTH (4bytes)}[0x00][0x00][0x00]   20 bytes
	*/
	class MiniVm {
	public:
		MiniVm(int64 memorySize);
		~MiniVm();

	private:
		iReg reg[16];
		bitset<8> CSP;
	};
}