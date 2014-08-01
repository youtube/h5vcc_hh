/*
 * Copyright (C) 2014 FactorY Media Production GmbH
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted.
 *
 * THIS SOFTWARE IS PROVIDED BY FACTORY MEDIA PRODUCTION GMBH AND ITS CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL FACTORY MEDIA PRODUCTION GMBH OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* FYWEBKITMOD BEGIN */

#ifndef PPCAssembler_h
#define PPCAssembler_h

#if ENABLE(ASSEMBLER) && CPU(PPC)

	#include "AssemblerBuffer.h"
	#include <wtf/Assertions.h>
	#include <wtf/SegmentedVector.h>

// Enable this switch to allow longer branches!
#define _RVL_INVERTED_BRANCH_CONDITION

namespace JSC
	{

	typedef uint32_t PPCWord;

	namespace PPCRegisters
		{
		typedef enum
			{
			r0 = 0,
			r1,
			r2,
			r3,
			r4,
			r5,
			r6,
			r7,
			r8,
			r9,
			r10,
			r11,
			r12,
			r13,
			r14,
			r15,
			r16,
			r17,
			r18,
			r19,
			r20,
			r21,
			r22,
			r23,
			r24,
			r25,
			r26,
			r27,
			r28,
			r29,
			r30,
			r31,
			zero = r0,
			ra = r0,	// Language Specific, copy of link register
			sp = r1,	// stack
			} RegisterID;

		typedef enum
			{
			f0,
			f1,
			f2,
			f3,
			f4,
			f5,
			f6,
			f7,
			f8,
			f9,
			f10,
			f11,
			f12,
			f13,
			f14,
			f15,
			f16,
			f17,
			f18,
			f19,
			f20,
			f21,
			f22,
			f23,
			f24,
			f25,
			f26,
			f27,
			f28,
			f29,
			f30,
			f31
			} FPRegisterID;

		typedef enum
			{
			lr  = 8,
			ctr = 9,
			} SPRRegisterID;

		} // namespace PPCRegisters

	class PPCAssembler
		{
	public:
		typedef PPCRegisters::RegisterID RegisterID;
		typedef PPCRegisters::FPRegisterID FPRegisterID;
		typedef SegmentedVector<int, 64> Jumps;

		PPCAssembler()
			{
			}

		enum ConditionBit
			{
			COND_lt = 0, // msb of CR
			COND_gt = 1,
			COND_eq = 2,
			COND_so = 3, // lsb of CR
			COND_un = 3,
			};
	
		// this is the BO field in condition instructions
		enum ConditionOption
			{
			#ifndef _RVL_INVERTED_BRANCH_CONDITION
				BO_true = 12, 	// branch if true  = 011zy = Branch if the condition is TRUE (y = branch prediction hint)
				BO_false = 4, 	// branch if false = 001zy = Branch if the condition is FALSE (y = branch prediction hint)
			#else
				// enable branch prediction!!!
				BO_true = 13,
				BO_false = 5,
			#endif

			BO_always = 20, // branch always = 1z1zz = Branch always
			};

		// PPC instruction opcode field position
		enum
			{
			OP_SH_RD = 21,
			OP_SH_RS = 21,
			OP_SH_RA = 16,
			OP_SH_RB = 11,
			OP_SH_RC = 6,

			OP_SH_BO = 21,
			OP_SH_BI = 16,
			OP_SH_BD = 2,
			
			};


		class JmpSrc
			{
			friend class PPCAssembler;
		public:
			JmpSrc()
			: m_offset(-1)
				{
				}

		private:
			JmpSrc(int offset)
			: m_offset(offset)
				{
				}

			int m_offset;
			};


		class JmpDst
			{
			friend class PPCAssembler;
		public:
			JmpDst()
			: m_offset(-1)
			, m_used(false)
				{
				}

			bool isUsed() const
				{
				return m_used;
				}
			void used()
				{
				m_used = true;
				}
		private:
			JmpDst(int offset)
			: m_offset(offset)
			, m_used(false)
				{
				ASSERT(m_offset == offset);
				}

			int m_offset : 31;
			int m_used : 1;
			};


		void emitInst(PPCWord op)
			{
			void* oldBase = m_buffer.data();

			m_buffer.putInt(op);

			void* newBase = m_buffer.data();
			if(oldBase != newBase)
				relocateJumps(oldBase, newBase);
			}

		// -----------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------
		
		void nop()
			{
			emitInst(0x60000000); // ori
			}

		void codeMarker(u32 value)
			{
			emitInst(0x60000000); // ori
			emitInst(0x48000000 | (2)<<2); // SKIP the next word
			// we can place some arbitraty value here for marking code locations
			emitInst(value);
			emitInst(0x60000000); // ori
			}

		void dcb_w(u32 markerWord)
			{
			emitInst(markerWord);
			}

		void bkpt()
			{
			//lwz r0, 0(r0)
			emitInst(0x80000000);
			}


		// -----------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------


		// If rA == PPCRegister::zero, we just move a 0 to rd
		void move(RegisterID rd, RegisterID ra)
			{
			// Using addi rD,rA,SIMM here, because of rA = 0 case..
			emitInst(0x38000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA));
			}

		// Set an immediate value to a register.  This may generate 1 or 2 instructions
		void li(RegisterID dest, int imm)
			{
			if(imm >= -32768 && imm <= 32767)
				{
				addi(dest, PPCRegisters::zero, imm);
				}
			else if(imm >= 0 && imm < 65536)
				{
				xorx(dest, dest, dest); // zero!
				ori(dest, dest, imm);
				}
			else
				{
				lis(dest, imm>>16);
				ori(dest, dest, imm);
				}
			}
		
		void lis(RegisterID rt, int imm)
			{
			// addis
			emitInst(0x3C000000 | (rt << OP_SH_RD) | (imm & 0xffff)); 
			}

		void addi(RegisterID rd, RegisterID ra, int imm)
			{
			emitInst(0x38000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (imm & 0xffff));
			}
		
		// Add Immediate Carrying and Record. Mostly used for adding 0 and just checking the result
		void addiC(RegisterID rd, RegisterID ra, int imm)
			{
			emitInst(0x34000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (imm & 0xffff));
			}

		void addx(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C000214 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void addC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C000214 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | 1);
			}

		// Move to Condition Register from XER to CR0
		// !!!and CLEAR XER (which is required for upoming overflow-aware operations)!!
		void mcrxr(void)
			{
			emitInst(0x7C000400);
			}
		
		void addOC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			// Set OE and RC bit
			emitInst(0x7C000214 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | (1<<10) | 1 );
			}
		
		void andx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000038 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | 1);
			}
		
		void andC(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			//and. i swith update of CR0 field
			emitInst(0x7C000038 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | 1);
			}
		
		void andi(RegisterID ra, RegisterID rs, int uimm)
			{
			emitInst(0x70000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (uimm & 0xffff));
			}

		void slwi(RegisterID ra, RegisterID rs, int shamt)
			{
			//rlwinm rA,rS,n,0,31–n
			emitInst(0x54000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (shamt)<<11 | 0<<6 | (31-(shamt))<<1 );
			}

		void slwx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000030 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}


		// logical
		void srwi(RegisterID ra, RegisterID rs, int shamt)
			{
			//rlwinm rA,rS,32 – n,n,31
			emitInst(0x54000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (32-(shamt))<<11 | (shamt)<<6 | (31<<1) );
			}

		// logical
		void srwx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000430 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}


		// arthimetic 
		void srawi(RegisterID ra, RegisterID rs, int shamt)
			{
			emitInst(0x7C000670 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (shamt << OP_SH_RB));
			}

		// arthimetic 
		void sraw(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000630 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}




		void subx(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			// sub rD,rA,rB <=> subf rD,rB,rA
			emitInst(0x7C000050 | (rd << OP_SH_RD) | (rb << OP_SH_RA) | (ra << OP_SH_RB));
			}

		void subC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			// sub rD,rA,rB <=> subf rD,rB,rA
			emitInst(0x7C000050 | (rd << OP_SH_RD) | (rb << OP_SH_RA) | (ra << OP_SH_RB) | 1);
			}

		void subOC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			// sub rD,rA,rB <=> subf rD,rB,rA
			emitInst(0x7C000050 | (rd << OP_SH_RD) | (rb << OP_SH_RA) | (ra << OP_SH_RB) | (1<<10) | 1 );
			}
		
		// ----------------------------------------------------------------------

		JmpSrc newJmpSrc()
			{
			return JmpSrc(m_buffer.size());
			}

		void appendJump()
			{
			m_jumps.append(m_buffer.size());
			}

		// ----------------------------------------------------------------------
		
		void lwz(RegisterID rd, RegisterID ra, int offset)
			{
			emitInst(0x80000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		void lhz(RegisterID rd, RegisterID ra, int offset)
			{
			emitInst(0xA0000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		void lbz(RegisterID rd, RegisterID ra, int offset)
			{
			emitInst(0x88000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		// ----------------------------------------------------------------------

		void stw(RegisterID rs, RegisterID ra, int offset)
			{
			emitInst(0x90000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		void mullw(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C0001D6 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB) );
			}

		void mullwC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C0001D6 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | 1);
			}

		void mullwOC(RegisterID rd, RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C0001D6 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB) | (1<<10) | 1);
			}
		
		void orx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000378 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void ori(RegisterID ra, RegisterID rs, int uimm)
			{
			emitInst(0x60000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (uimm & 0xffff));
			}

		void xorx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C000278 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}
			
		void xoris(RegisterID ra, RegisterID rs, int uimm)
			{
			emitInst(0x6c000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (uimm & 0xffff));
			}

		void norx(RegisterID ra, RegisterID rs, RegisterID rb)
			{
			emitInst(0x7C0000F8 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		// ----------------------------------------------------------------------

		void cmpl(RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C000040 | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void cmp(RegisterID ra, RegisterID rb)
			{
			emitInst(0x7C000000 | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void bne(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_false << OP_SH_BO) | (COND_eq << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		void beq(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_true << OP_SH_BO) | (COND_eq << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		void blt(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_true << OP_SH_BO) | (COND_lt << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		void bgt(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_true << OP_SH_BO) | (COND_gt << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		void bge(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_false << OP_SH_BO) | (COND_lt << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}
			
		void ble(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_false << OP_SH_BO) | (COND_gt << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		// branch if "overflow"
		void bo(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_true << OP_SH_BO) | (COND_so << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}

		// branch if "not overflow"
		void bno(int imm)
			{
			#ifdef _RVL_INVERTED_BRANCH_CONDITION
			ASSERT(imm > 0);
			#endif
			// bcx			
			emitInst(0x40000000 | (BO_false << OP_SH_BO) | (COND_so << OP_SH_BI) | ((imm<<2) & 0xfffc));
			}


		#define XSPR(sprName) ((sprName)>>5|(sprName&31)<<5)
		void mtctrX(RegisterID rs)
			{
			// mtctr rD == mtspr 9,rD
			emitInst(0x7C0003A6 | (rs << OP_SH_RS) | XSPR(PPCRegisters::ctr)<<11);
			}

		void bctrX(void)
			{
			//bcctrx (NO link register update)
			emitInst(0x4C000420 | (BO_always << OP_SH_BO) );
			}
		void bctrlX(void)
			{
			//bcctrx *WITH* link register update
			emitInst(0x4C000420 | (BO_always << OP_SH_BO) | 1);
			}

		void blr(void)
			{
			//Branch Conditional to Link Register (with BO_always)
			//bclr 
			emitInst(0x4C000020 | (BO_always << OP_SH_BO) );
			}

		void bl(void)
			{
			//bl *WITH* link register update
			emitInst(0x48000000 | 1);
			}

		void b(void)
			{
			//b *WITHOUT* link register update
			emitInst(0x48000000);
			}
			

		void mflr(RegisterID rd)
			{
			// mflr rD == mfspr 8,rD
			emitInst(0x7C0002A6 | (rd << OP_SH_RD) | XSPR(PPCRegisters::lr)<<11);
			}

		void mtlr(RegisterID rs)
			{
			// mtlr rD == mtspr 8,rD
			emitInst(0x7C0003A6 | (rs << OP_SH_RS) | XSPR(PPCRegisters::lr)<<11);
			}

		void mfcr(RegisterID rd)
			{
			emitInst(0x7C000026 | (rd << OP_SH_RD));
			}
		
		// --------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------

		void lfd(FPRegisterID rd, RegisterID ra, int offset)
			{
			emitInst(0xc8000000 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		void stfd(FPRegisterID rs, RegisterID ra, int offset)
			{
			emitInst(0xd8000000 | (rs << OP_SH_RS) | (ra << OP_SH_RA) | (offset & 0xffff));
			}

		void fcmpu(FPRegisterID ra, FPRegisterID rb)
			{
			emitInst(0xfc000000 | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void fcmpo(FPRegisterID ra, FPRegisterID rb)
			{
			emitInst(0xfc000040 | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void faddx(FPRegisterID rd, FPRegisterID ra, FPRegisterID rb)
			{
			emitInst(0xfc00002a | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void fsubx(FPRegisterID rd, FPRegisterID ra, FPRegisterID rb)
			{
			emitInst(0xfc000028 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rb << OP_SH_RB));
			}

		void fmulx(FPRegisterID rd, FPRegisterID ra, FPRegisterID rc)
			{
			emitInst(0xfc000032 | (rd << OP_SH_RD) | (ra << OP_SH_RA) | (rc << OP_SH_RC) );
			}

		// --------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------


		// General helpers

		JmpDst label()
			{
			return JmpDst(m_buffer.size());
			}

		JmpDst align(int alignment)
			{
			while(!m_buffer.isAligned(alignment))
				bkpt();

			return label();
			}
		
		static void* getRelocatedAddress(void* code, JmpSrc jump)
			{
			ASSERT(jump.m_offset != -1);
			void* b = reinterpret_cast<void*>((reinterpret_cast<intptr_t>(code)) + jump.m_offset);
			return b;
			}

		static void* getRelocatedAddress(void* code, JmpDst label)
			{
			void* b = reinterpret_cast<void*>((reinterpret_cast<intptr_t>(code)) + label.m_offset);
			return b;
			}

		static int getDifferenceBetweenLabels(JmpDst from, JmpDst to)
			{
			return to.m_offset - from.m_offset;
			}

		static int getDifferenceBetweenLabels(JmpDst from, JmpSrc to)
			{
			return to.m_offset - from.m_offset;
			}

		static int getDifferenceBetweenLabels(JmpSrc from, JmpDst to)
			{
			return to.m_offset - from.m_offset;
			}

		// Assembler admin methods:

		size_t size() const
			{
			return m_buffer.size();
			}

		void* executableCopy(ExecutablePool* allocator)
			{
			void *result = m_buffer.executableCopy(allocator);
			if(!result)
				return 0;

			relocateJumps(m_buffer.data(), result);
			return result;
			}

		static unsigned getCallReturnOffset(JmpSrc call)
			{
			// The return address is after a call and a delay slot instruction
			return call.m_offset;
			}


		// Linking & patching:

		void linkJump(JmpSrc from, JmpDst to)
			{
			ASSERT(to.m_offset != -1);
			ASSERT(from.m_offset != -1);
			PPCWord* insn = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(m_buffer.data()) + from.m_offset);
			PPCWord* toPos = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(m_buffer.data()) + to.m_offset);

			// branch command is one instruction before...
			insn = insn - 1;
			
			linkWithOffset(insn, toPos);
			}

		static void linkJump(void* code, JmpSrc from, void* to)
			{
			ASSERT(from.m_offset != -1);
			PPCWord* insn = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(code) + from.m_offset);

			// branch command is one instruction before...
			insn = insn - 1;

			linkWithOffset(insn, to);
			}
			

		static void linkCall(void* code, JmpSrc from, void* to)
			{
			PPCWord* insn = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(code) + from.m_offset);
			linkCallInternal(insn, to);
			}


		static void linkPointer(void* code, JmpDst from, void* to)
			{
			RVL_JIT_ASSERT(!"TODO");
			/*
			PPCWord* insn = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(code) + from.m_offset);
			ASSERT((*insn & 0xffe00000) == 0x3c000000);	// lui
			*insn = (*insn & 0xffff0000) | ((reinterpret_cast<intptr_t>(to) >> 16) & 0xffff);
			insn++;
			ASSERT((*insn & 0xfc000000) == 0x34000000);	// ori
			*insn = (*insn & 0xffff0000) | (reinterpret_cast<intptr_t>(to) & 0xffff);
			*/
			}

		static void relinkJump(void* from, void* to)
			{
			void* start;
			PPCWord* insn = reinterpret_cast<PPCWord*>(from);

			int flushSize = linkWithOffset(insn-1, to);

			if(flushSize == sizeof(PPCWord))
				start = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(from) - 1 * sizeof(PPCWord));
			else
				{
				RVL_JIT_ASSERT(!"CHECK THIS");
				start = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(from) - 4 * sizeof(PPCWord));
				}

			ExecutableAllocator::cacheFlush(start, flushSize);
			}

		static void relinkCall(void* from, void* to)
			{
			void* start;
			int size = linkCallInternal(from, to);
			if(size == sizeof(PPCWord))
				start = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(from) - 1 * sizeof(PPCWord));
			else
				start = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(from) - 4 * sizeof(PPCWord));

			ExecutableAllocator::cacheFlush(start, size);
			}

		static void repatchInt32(void* from, int32_t to)
			{
			PPCWord* insn = reinterpret_cast<PPCWord*>(from);

			ASSERT((*insn & 0xfc000000) == 0x3C000000);	// lis
			*insn = (*insn & 0xffff0000) | ((to >> 16) & 0xffff);
			insn++;

			ASSERT((*insn & 0xfc000000) == 0x60000000);	// ori
			*insn = (*insn & 0xffff0000) | (to & 0xffff);

			insn--;
			ExecutableAllocator::cacheFlush(insn, 2 * sizeof(PPCWord));
			}

		static void repatchPointer(void* from, void* to)
			{
			repatchInt32(from, reinterpret_cast<int32_t>(to));
			}

		static void repatchLoadPtrToLEA(void* from)
			{
			PPCWord* insn = reinterpret_cast<PPCWord*>(from);
			insn = insn + 3;
			
			// must find a "lwz" there
			ASSERT((*insn & 0xfc000000) == 0x80000000);

			// change from lwz to addi Rx,Rx,y
			*insn = 0x38000000 | (*insn & 0x03ffffff);
			
			ExecutableAllocator::cacheFlush(insn, sizeof(PPCWord));
			}

	private:

		/* Update each jump in the buffer of newBase.  */
		void relocateJumps(void* oldBase, void* newBase)
			{
			for(Jumps::Iterator iter = m_jumps.begin(); iter != m_jumps.end(); ++iter)
				{
				int pos = *iter;
				PPCWord* insn = reinterpret_cast<PPCWord*>(reinterpret_cast<intptr_t>(newBase) + pos);

				RVL_JIT_ASSERT(!"TODO");
				
				#if 0
				insn = insn + 2;
				// Need to make sure we have 5 valid instructions after pos
				if((unsigned int)pos >= m_buffer.size() - 5 * sizeof(PPCWord))
					continue;
				if((*insn & 0xfc000000) == 0x08000000) // j
					{
					int offset = *insn & 0x03ffffff;
					int oldInsnAddress = (int)insn - (int)newBase + (int)oldBase;
					int topFourBits = (oldInsnAddress + 4) >> 28;
					int oldTargetAddress = (topFourBits << 28) | (offset << 2);
					int newTargetAddress = oldTargetAddress - (int)oldBase + (int)newBase;
					int newInsnAddress = (int)insn;
					if(((newInsnAddress + 4) >> 28) == (newTargetAddress >> 28))
						*insn = 0x08000000 | ((newTargetAddress >> 2) & 0x3ffffff);
					else
						{
						/* lui */
						*insn = 0x3c000000 | (PPCRegisters::t9 << OP_SH_RT) | ((newTargetAddress >> 16) & 0xffff);
						/* ori */
						*(insn + 1) = 0x34000000 | (PPCRegisters::t9 << OP_SH_RT) | (PPCRegisters::t9 << OP_SH_RS) | (newTargetAddress & 0xffff);
						/* jr */
						*(insn + 2) = 0x00000008 | (PPCRegisters::t9 << OP_SH_RS);
						}
					}
				else if((*insn & 0xffe00000) == 0x3c000000)	// lui
					{
					int high = (*insn & 0xffff) << 16;
					int low = *(insn + 1) & 0xffff;
					int oldTargetAddress = high | low;
					int newTargetAddress = oldTargetAddress - (int)oldBase + (int)newBase;
					/* lui */
					*insn = 0x3c000000 | (PPCRegisters::t9 << OP_SH_RT) | ((newTargetAddress >> 16) & 0xffff);
					/* ori */
					*(insn + 1) = 0x34000000 | (PPCRegisters::t9 << OP_SH_RT) | (PPCRegisters::t9 << OP_SH_RS) | (newTargetAddress & 0xffff);
					}
				#endif
				}
			}

		static int linkWithOffset(PPCWord* insn, void* to)
			{
			intptr_t diff = (reinterpret_cast<intptr_t>(to)	- reinterpret_cast<intptr_t>(insn));
			RVL_JIT_ASSERT((diff & 0x3) == 0);
			// Check if we have a "Branch Conditional" command here
			if((*insn & 0xfc000000) == 0x40000000)
				{
				//bc?
				//BD field is 14bit
				diff >>= 2;
				
				RVL_JIT_ASSERT(diff >= -8192 && diff <= 8191);
				
				*insn = (*insn & 0xffff0001) | ((diff<<2) & 0xfffc);
				return sizeof(PPCWord);
				}
			//b?
			RVL_JIT_ASSERT((*insn & 0xfc000001) == 0x48000000);
			RVL_JIT_ASSERT(diff >= -(1<<24) && diff <= (1<<24)); // must be 25!!!!!
			*insn = (*insn & 0xfc000001) | (diff & (0x03fffffc));
			return sizeof(PPCWord);
			}

		static int linkCallInternal(void* from, void* to)
			{
			PPCWord* insn = reinterpret_cast<PPCWord*>(from);
			insn -= 1;
			
			// Check bl
			if((*insn & 0xfc000001) == 0x48000001)
				{
				intptr_t diff = (reinterpret_cast<intptr_t>(to)	- reinterpret_cast<intptr_t>(insn));
				RVL_JIT_ASSERT((diff & 0x3) == 0);
				RVL_JIT_ASSERT(diff >= -(1<<24) && diff <= (1<<24)); // must be 25!!!!!

				*insn = (*insn & 0xfc000001) | (diff & (0x03fffffc) );
				return sizeof(PPCWord);
				}
			else
				{
				insn -= 3;
			
				RVL_JIT_ASSERT((*insn & 0xfc000000) == 0x3C000000);			// lis / addis
				RVL_JIT_ASSERT((*(insn + 1) & 0xfc000000) == 0x60000000); 	// ori
	
				*insn = (*insn & 0xffff0000) | ((reinterpret_cast<intptr_t>(to) >> 16) & 0xffff);
				*(insn + 1) = (*(insn + 1) & 0xffff0000) | (reinterpret_cast<intptr_t>(to) & 0xffff);
						
				return 4 * sizeof(PPCWord);

				}
			}

		AssemblerBuffer m_buffer;
		Jumps m_jumps;
		};

	} // namespace JSC

#endif // ENABLE(ASSEMBLER) && CPU(PPC)

#endif // PPCAssembler_h

/* FYWEBKITMOD END */