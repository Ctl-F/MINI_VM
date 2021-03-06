#pragma once
#include "pch.h"

#include <bitset>

#ifdef MINIVM_EXPORTS
#define MINI_API __declspec(dllexport)
#else
#define MINI_API __declspec(dllimport)
#endif

using std::bitset;

namespace mini {

	MINI_API struct iReg {
		union {
			int8   hx;
			int16   x;
			int32  dx;
			int64 edx;
		};
	};

	

	typedef double fpReg;

	MINI_API enum CSP_BITS {
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
	*		A    (AH, A, AX, EAX) { HalfA, A, DoubleA, FullA }
	*		B
	*		C
	*		D
	*		E
	*		F
	*		R0
	*		R1
	*		R2
	*		R3
	*		R4
	*		ERR  (Program Error)
	*		JLP  (jump link pointer)
	*		IP
	*		SH   (Stack Head)
	*		SB   (Stack Base)
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
	* 
	*	ERROR Index
	*		An array of 64 addresses that can be assigned to label (needs to be done at assembly time)
	*		Then, if an error occurs the error index can be written to the ERP and the CSP error bit can be set.
	*		When the csp error bit is set the program will jump to the assigned label (which defaults to be out of the memory scope causing a crash if an unregistered error is called)
	* 
	*	Interrupt Registry:
	*		Interrupt codes can be registered to function pointers to allow for extensability and integration into the vm
	*		
	*		Interrupt Callback Signature:
	*			int32 callback(int32[16] registers, bitset<8> CSP, byte* heapPointer)
	*/
	MINI_API class MiniVm {
	public:
		MiniVm(int64 memorySize);
		~MiniVm();

	private:
		iReg m_reg[16];
		bitset<8> m_CSP;

		fpReg m_freg[8];
	};
}