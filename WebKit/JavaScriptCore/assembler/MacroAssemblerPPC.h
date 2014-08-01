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

#ifndef MacroAssemblerPPC_h
#define MacroAssemblerPPC_h

#if ENABLE(ASSEMBLER) && CPU(PPC)

	#include "AbstractMacroAssembler.h"
	#include "PPCAssembler.h"

namespace JSC
	{
	const static char fpConst1[] __attribute__ ((aligned (8)))  = { 0x43, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };

	class MacroAssemblerPPC : public AbstractMacroAssembler<PPCAssembler>
		{
	public:
		typedef PPCRegisters::FPRegisterID FPRegisterID;


		MacroAssemblerPPC()
		: m_fixedWidth(false)
			{
			}

		static const Scale ScalePtr = TimesFour;

		// For storing immediate number
		static const RegisterID immTempRegister = PPCRegisters::r9;
		// For storing data loaded from the memory
		static const RegisterID dataTempRegister = PPCRegisters::r10;
		// For storing address base
		static const RegisterID addrTempRegister = PPCRegisters::r11;
		// For storing compare result
		static const RegisterID cmpTempRegister = PPCRegisters::r12;

		// FP temp register
		static const FPRegisterID fpTempRegister = PPCRegisters::f13;

		enum Condition
			{
			Equal,
			NotEqual,
			Above,
			AboveOrEqual,
			Below,
			BelowOrEqual,
			GreaterThan,
			GreaterThanOrEqual,
			LessThan,
			LessThanOrEqual,
			Overflow,
			Signed,
			Zero,
			NonZero
			};

		enum DoubleCondition
			{
			DoubleEqual,
			DoubleNotEqual,
			DoubleGreaterThan,
			DoubleGreaterThanOrEqual,
			DoubleLessThan,
			DoubleLessThanOrEqual,
			DoubleEqualOrUnordered,
			DoubleNotEqualOrUnordered,
			DoubleGreaterThanOrUnordered,
			DoubleGreaterThanOrEqualOrUnordered,
			DoubleLessThanOrUnordered,
			DoubleLessThanOrEqualOrUnordered
			};

		static const RegisterID stackPointerRegister = PPCRegisters::sp;

		// Integer arithmetic operations:
		
		void add32(RegisterID src, RegisterID dest)
			{
			m_assembler.addx(dest, dest, src);
			}

		void add32(Imm32 imm, RegisterID dest)
			{
			add32(imm, dest, dest);
			}

		void add32(Imm32 imm, RegisterID src, RegisterID dest)
			{
			if(!imm.m_isPointer && imm.m_value >= -32768 && imm.m_value <= 32767 && !m_fixedWidth)
				{
				m_assembler.addi(dest, src, imm.m_value);
				}
			else
				{
				move(imm, immTempRegister);
				m_assembler.addx(dest, src, immTempRegister);
				}
			}

		void add32(Imm32 imm, Address address)
			{
			if(address.offset >= -32768 && address.offset <= 32767 && !m_fixedWidth)
				{
				m_assembler.lwz(dataTempRegister, address.base, address.offset);
				if(!imm.m_isPointer
				   && imm.m_value >= -32768 && imm.m_value <= 32767
				   && !m_fixedWidth)
					m_assembler.addi(dataTempRegister, dataTempRegister, imm.m_value);
				else
					{
					move(imm, immTempRegister);
					m_assembler.addx(dataTempRegister, dataTempRegister, immTempRegister);
					}
				m_assembler.stw(dataTempRegister, address.base, address.offset);
				}
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lwz(dataTempRegister, addrTempRegister, address.offset);

				if(imm.m_value >= -32768 && imm.m_value <= 32767 && !m_fixedWidth)
					m_assembler.addi(dataTempRegister, dataTempRegister, imm.m_value);
				else
					{
					move(imm, immTempRegister);
					m_assembler.addx(dataTempRegister, dataTempRegister, immTempRegister);
					}
				m_assembler.stw(dataTempRegister, addrTempRegister, address.offset);
				}
			}

		void add32(Address src, RegisterID dest)
			{
			load32(src, dataTempRegister);
			add32(dataTempRegister, dest);
			}

		void add32(RegisterID src, Address dest)
			{
			if(dest.offset >= -32768 && dest.offset <= 32767 && !m_fixedWidth)
				{
				m_assembler.lwz(dataTempRegister, dest.base, dest.offset);
				m_assembler.addx(dataTempRegister, dataTempRegister, src);
				m_assembler.stw(dataTempRegister, dest.base, dest.offset);
				}
			else
				{
				m_assembler.lis(addrTempRegister, (dest.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, dest.base);
				m_assembler.lwz(dataTempRegister, addrTempRegister, dest.offset);
				m_assembler.addx(dataTempRegister, dataTempRegister, src);
				m_assembler.stw(dataTempRegister, addrTempRegister, dest.offset);
				}
			}

		void add32(Imm32 imm, AbsoluteAddress address)
			{
			move(ImmPtr(address.m_ptr), addrTempRegister);
			m_assembler.lwz(dataTempRegister, addrTempRegister, 0);
			if(!imm.m_isPointer && imm.m_value >= -32768 && imm.m_value <= 32767
			   && !m_fixedWidth)
				m_assembler.addi(dataTempRegister, dataTempRegister, imm.m_value);
			else
				{
				move(imm, immTempRegister);
				m_assembler.addx(dataTempRegister, dataTempRegister, immTempRegister);
				}
			m_assembler.stw(dataTempRegister, addrTempRegister, 0);
			}

		void and32(RegisterID src, RegisterID dest)
			{
			m_assembler.andx(dest, dest, src);
			}

		void and32(Imm32 imm, RegisterID dest)
			{
			if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
				move(PPCRegisters::zero, dest);
			else if(!imm.m_isPointer && imm.m_value > 0 && imm.m_value < 65535
					&& !m_fixedWidth)
				m_assembler.andi(dest, dest, imm.m_value);
			else
				{
				move(imm, immTempRegister);
				m_assembler.andx(dest, dest, immTempRegister);
				}
			}

		void lshift32(Imm32 imm, RegisterID dest)
			{
			m_assembler.slwi(dest, dest, imm.m_value);
			}

		void lshift32(RegisterID shiftAmount, RegisterID dest)
			{
			m_assembler.slwx(dest, dest, shiftAmount);
			}

		void mul32(RegisterID src, RegisterID dest)
			{
			m_assembler.mullw(dest, dest, src);
			}

		void mul32(Imm32 imm, RegisterID src, RegisterID dest)
			{
			if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
				move(PPCRegisters::zero, dest);
			else if(!imm.m_isPointer && imm.m_value == 1 && !m_fixedWidth)
				move(src, dest);
			else
				{
				move(imm, dataTempRegister);
				m_assembler.mullw(dest, src, dataTempRegister);
				}
			}

		void not32(RegisterID srcDest)
			{
			m_assembler.addi(dataTempRegister, PPCRegisters::zero, 0);
			m_assembler.norx(srcDest, srcDest, dataTempRegister);
			}

		void or32(RegisterID src, RegisterID dest)
			{
			m_assembler.orx(dest, dest, src);
			}

		void or32(Imm32 imm, RegisterID dest)
			{
			if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
				return;

			if(!imm.m_isPointer && imm.m_value > 0 && imm.m_value < 65535
			   && !m_fixedWidth)
				{
				m_assembler.ori(dest, dest, imm.m_value);
				return;
				}
			move(imm, dataTempRegister);
			m_assembler.orx(dest, dest, dataTempRegister);
			}



		// must be arthimetic shift!
		// must be arthimetic shift!
		// must be arthimetic shift!
		// must be arthimetic shift!
		void rshift32(RegisterID shiftAmount, RegisterID dest)
			{
			m_assembler.sraw(dest, dest, shiftAmount);
			}

		// must be arthimetic shift!
		// must be arthimetic shift!
		// must be arthimetic shift!
		// must be arthimetic shift!
		void rshift32(Imm32 imm, RegisterID dest)
			{
			m_assembler.srawi(dest, dest, imm.m_value);
			}



		// logical shift
		// logical shift
		void urshift32(RegisterID shiftAmount, RegisterID dest)
			{
			m_assembler.srwx(dest, dest, shiftAmount);
			}

		// logical shift
		// logical shift
		void urshift32(Imm32 imm, RegisterID dest)
			{
			m_assembler.srwi(dest, dest, imm.m_value);
			}





		void sub32(RegisterID src, RegisterID dest)
			{
			m_assembler.subx(dest, dest, src);
			}

		void sub32(Imm32 imm, RegisterID dest)
			{
			if(!imm.m_isPointer && imm.m_value >= -32767 && imm.m_value <= 32768
			   && !m_fixedWidth)
				{
				m_assembler.addi(dest, dest, -imm.m_value);
				}
			else
				{
				move(imm, immTempRegister);
				m_assembler.subx(dest, dest, immTempRegister);
				}
			}

		void sub32(Imm32 imm, Address address)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				{
				m_assembler.lwz(dataTempRegister, address.base, address.offset);
				if(!imm.m_isPointer
				   && imm.m_value >= -32767 && imm.m_value <= 32768
				   && !m_fixedWidth)
					m_assembler.addi(dataTempRegister, dataTempRegister, -imm.m_value);
				else
					{
					move(imm, immTempRegister);
					m_assembler.subx(dataTempRegister, dataTempRegister, immTempRegister);
					}
				m_assembler.stw(dataTempRegister, address.base, address.offset);
				}
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lwz(dataTempRegister, addrTempRegister, address.offset);

				if(!imm.m_isPointer
				   && imm.m_value >= -32767 && imm.m_value <= 32768
				   && !m_fixedWidth)
					m_assembler.addi(dataTempRegister, dataTempRegister, -imm.m_value);
				else
					{
					move(imm, immTempRegister);
					m_assembler.subx(dataTempRegister, dataTempRegister, immTempRegister);
					}
				m_assembler.stw(dataTempRegister, addrTempRegister, address.offset);
				}
			}

		void sub32(Address src, RegisterID dest)
			{
			load32(src, dataTempRegister);
			sub32(dataTempRegister, dest);
			}

		void sub32(Imm32 imm, AbsoluteAddress address)
			{
			move(ImmPtr(address.m_ptr), addrTempRegister);
			m_assembler.lwz(dataTempRegister, addrTempRegister, 0);

			if(!imm.m_isPointer && imm.m_value >= -32767 && imm.m_value <= 32768
			   && !m_fixedWidth)
				{
				m_assembler.addi(dataTempRegister, dataTempRegister, -imm.m_value);
				}
			else
				{
				move(imm, immTempRegister);
				m_assembler.subx(dataTempRegister, dataTempRegister, immTempRegister);
				}
			m_assembler.stw(dataTempRegister, addrTempRegister, 0);
			}

		void xor32(RegisterID src, RegisterID dest)
			{
			m_assembler.xorx(dest, dest, src);
			}

		void xor32(Imm32 imm, RegisterID dest)
			{
			move(imm, immTempRegister);
			m_assembler.xorx(dest, dest, immTempRegister);
			}

		// Memory access operations:

		void load32(ImplicitAddress address, RegisterID dest)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				m_assembler.lwz(dest, address.base, address.offset);
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lwz(dest, addrTempRegister, address.offset);
				}
			}

		void load32(BaseIndex address, RegisterID dest)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lwz(dest, addrTempRegister, address.offset);
				}
			else
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lis(immTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, immTempRegister);
				m_assembler.lwz(dest, addrTempRegister, address.offset);
				}
			}

		void load8(ImplicitAddress address, RegisterID dest)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				m_assembler.lbz(dest, address.base, address.offset);
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lbz(dest, addrTempRegister, address.offset);
				}
			}


		void load32WithUnalignedHalfWords(BaseIndex address, RegisterID dest)
			{
			RVL_JIT_ASSERT(!"TODO");
			/*
			if(address.offset >= -32768 && address.offset <= 32764
			   && !m_fixedWidth)
				{
				m_assembler.sll(addrTempRegister, address.index, address.scale);
				m_assembler.addu(addrTempRegister, addrTempRegister, address.base);

				#if CPU(BIG_ENDIAN)
				m_assembler.lwl(dest, addrTempRegister, address.offset);
				m_assembler.lwr(dest, addrTempRegister, address.offset + 3);
				#else
				m_assembler.lwl(dest, addrTempRegister, address.offset + 3);
				m_assembler.lwr(dest, addrTempRegister, address.offset);
				#endif
				}
			else
				{
				m_assembler.sll(addrTempRegister, address.index, address.scale);
				m_assembler.addu(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lui(immTempRegister, address.offset >> 16);
				m_assembler.ori(immTempRegister, immTempRegister, address.offset);
				m_assembler.addu(addrTempRegister, addrTempRegister,
								 immTempRegister);
				#if CPU(BIG_ENDIAN)
				m_assembler.lwl(dest, addrTempRegister, 0);
				m_assembler.lwr(dest, addrTempRegister, 3);
				#else
				m_assembler.lwl(dest, addrTempRegister, 3);
				m_assembler.lwr(dest, addrTempRegister, 0);
				#endif
				}
			*/
			}

		void load32(void* address, RegisterID dest)
			{
			move(ImmPtr(address), addrTempRegister);
			m_assembler.lwz(dest, addrTempRegister, 0);
			}

		DataLabel32 load32WithAddressOffsetPatch(Address address, RegisterID dest)
			{
			m_fixedWidth = true;
			DataLabel32 dataLabel(this);
			move(Imm32(address.offset), addrTempRegister);
			m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
			m_assembler.lwz(dest, addrTempRegister, 0);
			m_fixedWidth = false;
			return dataLabel;
			}

		Label loadPtrWithPatchToLEA(Address address, RegisterID dest)
			{
			m_fixedWidth = true;
			Label label(this);
			move(Imm32(address.offset), addrTempRegister);
			m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
			m_assembler.lwz(dest, addrTempRegister, 0);
			m_fixedWidth = false;
			return label;
			}

		Label loadPtrWithAddressOffsetPatch(Address address, RegisterID dest)
			{
			return loadPtrWithPatchToLEA(address, dest);
			}


		// Need to use zero-extened load half-word for load16.
		void load16(BaseIndex address, RegisterID dest)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lhz(dest, addrTempRegister, address.offset);
				}
			else
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lis(immTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, immTempRegister);
				m_assembler.lhz(dest, addrTempRegister, address.offset);
				}
			}

		// Need to use zero-extened load half-word for load16.
		void load16(ImplicitAddress address, RegisterID dest)
			{
			if (address.offset >= -32768 && address.offset <= 32767
				&& !m_fixedWidth)
				{
				m_assembler.lhz(dest, address.base, address.offset);
				}
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lhz(dest, addrTempRegister, address.offset);
				}
			}

		DataLabel32 store32WithAddressOffsetPatch(RegisterID src, Address address)
			{
			m_fixedWidth = true;
			DataLabel32 dataLabel(this);
			move(Imm32(address.offset), addrTempRegister);
			m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
			m_assembler.stw(src, addrTempRegister, 0);
			m_fixedWidth = false;
			return dataLabel;
			}

		void store32(RegisterID src, ImplicitAddress address)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				m_assembler.stw(src, address.base, address.offset);
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.stw(src, addrTempRegister, address.offset);
				}
			}

		void store32(RegisterID src, BaseIndex address)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.stw(src, addrTempRegister, address.offset);
				}
			else
				{
				m_assembler.slwi(addrTempRegister, address.index, address.scale);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lis(immTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, immTempRegister);
				m_assembler.stw(src, addrTempRegister, address.offset);
				}
			}

		void store32(Imm32 imm, ImplicitAddress address)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				{
				if(!imm.m_isPointer && !imm.m_value)
					{
					move(PPCRegisters::zero, immTempRegister);
					m_assembler.stw(immTempRegister, address.base, address.offset);
					}
				else
					{
					move(imm, immTempRegister);
					m_assembler.stw(immTempRegister, address.base, address.offset);
					}
				}
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
					{
					move(PPCRegisters::zero, immTempRegister);
					m_assembler.stw(immTempRegister, addrTempRegister, address.offset);
					}
				else
					{
					move(imm, immTempRegister);
					m_assembler.stw(immTempRegister, addrTempRegister, address.offset);
					}
				}
			}

		void store32(RegisterID src, void* address)
			{
			move(ImmPtr(address), addrTempRegister);
			m_assembler.stw(src, addrTempRegister, 0);
			}

		void store32(Imm32 imm, void* address)
			{
			if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
				{
				move(ImmPtr(address), addrTempRegister);
				move(PPCRegisters::zero, immTempRegister);
				m_assembler.stw(immTempRegister, addrTempRegister, 0);
				}
			else
				{
				move(imm, immTempRegister);
				move(ImmPtr(address), addrTempRegister);
				m_assembler.stw(immTempRegister, addrTempRegister, 0);
				}
			}

		// Floating-point operations:

		bool supportsFloatingPoint() const
			{
			return (true);
			}

		bool supportsFloatingPointTruncate() const
			{
			RVL_JIT_ASSERT(!"TODO");
			return false;
			/*
			#if WTF_PPC_DOUBLE_FLOAT && WTF_PPC_ISA_AT_LEAST(2)
					return true;
			#else
					return false;
			#endif
			*/
			}

		// Stack manipulation operations:
		//
		// The ABI is assumed to provide a stack abstraction to memory,
		// containing machine word sized units of data.  Push and pop
		// operations add and remove a single register sized unit of data
		// to or from the stack.  Peek and poke operations read or write
		// values on the stack, without moving the current stack position.

		void pop(RegisterID dest)
			{
			m_assembler.lwz(dest, PPCRegisters::sp, 0);
			m_assembler.addi(PPCRegisters::sp, PPCRegisters::sp, 4);
			}

		void push(RegisterID src)
			{
			m_assembler.addi(PPCRegisters::sp, PPCRegisters::sp, -4);
			m_assembler.stw(src, PPCRegisters::sp, 0);
			}

		void push(Address address)
			{
			load32(address, dataTempRegister);
			push(dataTempRegister);
			}

		void push(Imm32 imm)
			{
			move(imm, immTempRegister);
			push(immTempRegister);
			}

		// Register move operations:
		//
		// Move values in registers.

		void move(Imm32 imm, RegisterID dest)
			{
			if(!imm.m_isPointer && !imm.m_value && !m_fixedWidth)
				move(PPCRegisters::zero, dest);
			else if(imm.m_isPointer || m_fixedWidth)
				{
				m_assembler.lis(dest, imm.m_value>>16);
				m_assembler.ori(dest, dest, imm.m_value);
				}
			else
				m_assembler.li(dest, imm.m_value);
			}

		void move(RegisterID src, RegisterID dest)
			{
			if(src != dest || m_fixedWidth)
				m_assembler.move(dest, src);
			}

		void move(ImmPtr imm, RegisterID dest)
			{
			move(Imm32(imm), dest);
			}

		void swap(RegisterID reg1, RegisterID reg2)
			{
			move(reg1, immTempRegister);
			move(reg2, reg1);
			move(immTempRegister, reg2);
			}

		void signExtend32ToPtr(RegisterID src, RegisterID dest)
			{
			if(src != dest || m_fixedWidth)
				move(src, dest);
			}

		void zeroExtend32ToPtr(RegisterID src, RegisterID dest)
			{
			if(src != dest || m_fixedWidth)
				move(src, dest);
			}


		Jump branch32(Condition cond, RegisterID left, RegisterID right)
			{
			if(cond == Equal || cond == Zero)
				{
				return branchEqual(false, left, right);
				}
			if(cond == NotEqual || cond == NonZero)
				{
				return branchNotEqual(false, left, right);
				}

			// unsigned

			if(cond == Above) 	// BGT
				{
				return branchGreaterThan(false, left, right);
				}
			if(cond == AboveOrEqual) // BGE
				{
				return branchGreaterEqual(false, left, right);
				}
			if(cond == Below) // BLT
				{
				return branchLessThan(false, left, right);
				}
			if(cond == BelowOrEqual) // BLE
				{
				return branchLessEqual(false, left, right);
				}

			// signed

			if(cond == GreaterThan)
				{
				return branchGreaterThan(true, left, right);
				}
			if(cond == GreaterThanOrEqual)
				{
				return branchGreaterEqual(true, left, right);
				}
			if(cond == LessThan)
				{
				return branchLessThan(true, left, right);
				}
			if(cond == LessThanOrEqual)
				{
				return branchLessEqual(true, left, right);
				}

			if(cond == Overflow)
				{
				RVL_JIT_ASSERT(!"TODO");
				/*
				m_assembler.xorInsn(cmpTempRegister, left, right);
				m_assembler.bgez(cmpTempRegister, 11);
				m_assembler.nop();
				m_assembler.subu(cmpTempRegister, left, right);
				m_assembler.xorInsn(cmpTempRegister, cmpTempRegister, left);
				m_assembler.bgez(cmpTempRegister, 7);
				m_assembler.nop();
				*/
				return jump();
				}
			if(cond == Signed)
				{
				RVL_JIT_ASSERT(!"TODO");
				m_assembler.subx(cmpTempRegister, left, right);
				
				//m_assembler.subu(cmpTempRegister, left, right);
				// Check if the result is negative.
				//m_assembler.slt(cmpTempRegister, cmpTempRegister, PPCRegisters::zero);
				
				return branchNotEqual(false, left, right);
				}
			ASSERT(0);
			return Jump();
			}

		Jump branch32(Condition cond, RegisterID left, Imm32 right)
			{
			move(right, immTempRegister);
			return branch32(cond, left, immTempRegister);
			}

		Jump branch32(Condition cond, RegisterID left, Address right)
			{
			load32(right, dataTempRegister);
			return branch32(cond, left, dataTempRegister);
			}

		Jump branch32(Condition cond, Address left, RegisterID right)
			{
			load32(left, dataTempRegister);
			return branch32(cond, dataTempRegister, right);
			}

		Jump branch32(Condition cond, Address left, Imm32 right)
			{
			load32(left, dataTempRegister);
			move(right, immTempRegister);
			return branch32(cond, dataTempRegister, immTempRegister);
			}

		Jump branch32(Condition cond, BaseIndex left, Imm32 right)
			{
			load32(left, dataTempRegister);
			// Be careful that the previous load32() uses immTempRegister.
			// So, we need to put move() after load32().
			move(right, immTempRegister);
			return branch32(cond, dataTempRegister, immTempRegister);
			}

		/*
		Jump branch32WithUnalignedHalfWords(Condition cond, BaseIndex left, Imm32 right)
			{
			load32WithUnalignedHalfWords(left, dataTempRegister);
			// Be careful that the previous load32WithUnalignedHalfWords()
			// uses immTempRegister.
			// So, we need to put move() after load32WithUnalignedHalfWords().
			move(right, immTempRegister);
			return branch32(cond, dataTempRegister, immTempRegister);
			}
		*/

		Jump branch32(Condition cond, AbsoluteAddress left, RegisterID right)
			{
			load32(left.m_ptr, dataTempRegister);
			return branch32(cond, dataTempRegister, right);
			}

		Jump branch32(Condition cond, AbsoluteAddress left, Imm32 right)
			{
			load32(left.m_ptr, dataTempRegister);
			move(right, immTempRegister);
			return branch32(cond, dataTempRegister, immTempRegister);
			}

		Jump branch16(Condition cond, BaseIndex left, RegisterID right)
			{
			load16(left, dataTempRegister);
			return branch32(cond, dataTempRegister, right);
			}

		Jump branch16(Condition cond, BaseIndex left, Imm32 right)
			{
			ASSERT(!(right.m_value & 0xFFFF0000));
			load16(left, dataTempRegister);
			// Be careful that the previous load16() uses immTempRegister.
			// So, we need to put move() after load16().
			move(right, immTempRegister);
			return branch32(cond, dataTempRegister, immTempRegister);
			}

		Jump branch8(Condition cond, Address left, Imm32 right)
			{
			load8(left, dataTempRegister);
			return branch32(cond, dataTempRegister, right);
			}			

		Jump branchTest8(Condition cond, Address address, Imm32 mask = Imm32(-1))
			{
			load8(address, dataTempRegister);
			return branchTest32(cond, dataTempRegister, mask);
			}

		Jump branchTest32(Condition cond, RegisterID reg, RegisterID mask)
			{
			ASSERT((cond == Zero) || (cond == NonZero));
			m_assembler.andC(cmpTempRegister, reg, mask);
			//move(PPCRegisters::zero, PPCRegisters::r9);
			if(cond == Zero)
				{
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.beq(0);
				#else
					m_assembler.bne(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			#ifndef _RVL_INVERTED_BRANCH_CONDITION
				m_assembler.bne(0);
			#else
				m_assembler.beq(2);
				m_assembler.b();
			#endif
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchTest32(Condition cond, RegisterID reg, Imm32 mask = Imm32(-1))
			{
			ASSERT((cond == Zero) || (cond == NonZero));
			
			// Special case:
			// If mask = 0xffffffff this means that the "and" operation is
			// just used for setting the condition register bits.
			if(mask.m_value == -1 && !m_fixedWidth)
				{
				// Just add 0 to set the CR0 flags
				m_assembler.addiC(cmpTempRegister, reg, 0);
				if(cond == Zero)
					{
					#ifndef _RVL_INVERTED_BRANCH_CONDITION
						m_assembler.beq(0);
					#else
						m_assembler.bne(2);
						m_assembler.b();
					#endif
					return Jump(m_assembler.newJmpSrc());
					}
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bne(0);
				#else
					m_assembler.beq(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			// Get mask value into register...
			move(mask, immTempRegister);
			// ..and perform the regular and operation
			return branchTest32(cond, reg, immTempRegister);
			/*
			if(mask.m_value == -1 && !m_fixedWidth)
				{
				move(PPCRegisters::zero, cmpTempRegister);
				if(cond == Zero)
					return branchEqual(false, reg, cmpTempRegister);
				return branchNotEqual(false, reg, cmpTempRegister);
				}
			move(mask, immTempRegister);
			return branchTest32(cond, reg, immTempRegister);
			*/
			
			}

		Jump branchTest32(Condition cond, Address address, Imm32 mask = Imm32(-1))
			{
			load32(address, dataTempRegister);
			return branchTest32(cond, dataTempRegister, mask);
			}

		Jump branchTest32(Condition cond, BaseIndex address, Imm32 mask = Imm32(-1))
			{
			load32(address, dataTempRegister);
			return branchTest32(cond, dataTempRegister, mask);
			}

		Jump jump()
			{
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}


		void jump(RegisterID target)
			{
			m_assembler.mtctrX(target);
			m_assembler.bctrX();
			}

		void jump(Address address)
			{
			m_fixedWidth = true;
			load32(address, PPCRegisters::r9);
			m_assembler.mtctrX(PPCRegisters::r9);
			m_assembler.bctrX();
			m_fixedWidth = false;
			}

		// Arithmetic control flow operations:
		//
		// This set of conditional branch operations branch based
		// on the result of an arithmetic operation.  The operation
		// is performed as normal, storing the result.
		//
		// * jz operations branch if the result is zero.
		// * jo operations branch if the (signed) arithmetic
		//   operation caused an overflow to occur.

		Jump branchAdd32(Condition cond, RegisterID src, RegisterID dest)
			{
			ASSERT((cond == Overflow) || (cond == Signed) || (cond == Zero) || (cond == NonZero));
			if(cond == Overflow)
				{
				
				// Clear XER (and trash CR0)					
				m_assembler.mcrxr();
			
				// Add with XER[OV] update (OE=1)
				// XER[SO] is set in this case
				// XER[SO] copied to CR0 via RC=1
				m_assembler.addOC(dest, dest, src);
				
				// Jump if CR[SO] is finally set
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bo(0);
				#else
					m_assembler.bno(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == Signed)
				{
				add32(src, dest);
				move(PPCRegisters::zero, cmpTempRegister);
				return branchLessThan(true, dest, cmpTempRegister);
				}
			if(cond == Zero)
				{
				//add32(src, dest);
				//move(PPCRegisters::zero, cmpTempRegister);
				//return branchEqual(false, dest, cmpTempRegister);
				m_assembler.addC(dest, dest, src);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.beq(0);
				#else
					m_assembler.bne(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == NonZero)
				{
				//add32(src, dest);
				//move(PPCRegisters::zero, cmpTempRegister);
				//return branchNotEqual(false, dest, cmpTempRegister);
				m_assembler.addC(dest, dest, src);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bne(0);
				#else
					m_assembler.beq(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			ASSERT(0);
			return Jump();
			}

		Jump branchAdd32(Condition cond, Imm32 imm, RegisterID dest)
			{
			move(imm, immTempRegister);
			return branchAdd32(cond, immTempRegister, dest);
			}

		Jump branchMul32(Condition cond, RegisterID src, RegisterID dest)
			{
			ASSERT((cond == Overflow) || (cond == Signed) || (cond == Zero) || (cond == NonZero));
			if(cond == Overflow)
				{
				// Clear XER (and trash CR0)					
				m_assembler.mcrxr();
			
				// Add with XER[OV] update (OE=1)
				// XER[SO] is set in this case
				// XER[SO] copied to CR0 via RC=1
				m_assembler.mullwOC(dest, dest, src);
				
				// Jump if CR[SO] is finally set
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bo(0);
				#else
					m_assembler.bno(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == Signed)
				{
				mul32(src, dest);
				move(PPCRegisters::zero, cmpTempRegister);
				return branchLessThan(true, dest, cmpTempRegister);
				}
			if(cond == Zero)
				{
				//mul32(src, dest);
				//move(PPCRegisters::zero, cmpTempRegister);
				//return branchEqual(false, dest, cmpTempRegister);
				m_assembler.mullwC(dest, dest, src);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.beq(0);
				#else
					m_assembler.bne(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == NonZero)
				{
				//mul32(src, dest);
				//move(PPCRegisters::zero, cmpTempRegister);
				//return branchNotEqual(false, dest, cmpTempRegister);
				m_assembler.mullwC(dest, dest, src);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bne(0);
				#else
					m_assembler.beq(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			ASSERT(0);
			return Jump();
			}

		Jump branchMul32(Condition cond, Imm32 imm, RegisterID src, RegisterID dest)
			{
			move(imm, immTempRegister);
			move(src, dest);
			return branchMul32(cond, immTempRegister, dest);
			}


		// ( jo operations branch if the (signed) arithmetic operation caused an overflow to occur.)

		Jump branchSub32(Condition cond, RegisterID src, RegisterID dest)
			{
			ASSERT((cond == Overflow) || (cond == Signed) || (cond == Zero) || (cond == NonZero));
			if(cond == Overflow)
				{
				
				// Clear XER (and trash CR0)					
				m_assembler.mcrxr();
			
				// Sub with XER[OV] update (OE=1)
				// XER[SO] is set in this case
				// XER[SO] copied to CR0 via RC=1
				m_assembler.subOC(dest, dest, src);
				
				// Jump if CR[SO] is finally set
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bo(0);
				#else
					m_assembler.bno(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == Signed)
				{
				sub32(src, dest);
				move(PPCRegisters::zero, cmpTempRegister);
				return branchLessThan(true, dest, cmpTempRegister);
				}
			if(cond == Zero)
				{
				sub32(src, dest);
				move(PPCRegisters::zero, cmpTempRegister);
				return branchEqual(false, dest, cmpTempRegister);
				}
			if(cond == NonZero)
				{
				sub32(src, dest);
				move(PPCRegisters::zero, cmpTempRegister);
				return branchNotEqual(false, dest, cmpTempRegister);
				}
			ASSERT(0);
			return Jump();
			}

		Jump branchSub32(Condition cond, Imm32 imm, RegisterID dest)
			{
			move(imm, immTempRegister);
			return branchSub32(cond, immTempRegister, dest);
			}

		// Miscellaneous operations:

		void breakpoint()
			{
			m_assembler.bkpt();
			}


		Call nearCall()
			{
			m_assembler.bl();
			return Call(m_assembler.newJmpSrc(), Call::LinkableNear);
			}

		Call call()
			{
			m_fixedWidth = true;
			move(Imm32(0), PPCRegisters::r9);
			m_assembler.mtctrX(PPCRegisters::r9);
			m_assembler.bctrlX();
			m_fixedWidth = false;
			return Call(m_assembler.newJmpSrc(), Call::Linkable);
			}

		Call call(RegisterID target)
			{
			m_assembler.mtctrX(target);
			m_assembler.bctrlX();
			return Call(m_assembler.newJmpSrc(), Call::None);
			}

		Call call(Address address)
			{
			m_fixedWidth = true;
			load32(address, PPCRegisters::r9);
			m_assembler.mtctrX(PPCRegisters::r9);
			m_assembler.bctrlX();
			m_fixedWidth = false;
			return Call(m_assembler.newJmpSrc(), Call::None);
			}

		void ret()
			{
			m_assembler.blr();
			}

		void set32(Condition cond, RegisterID left, RegisterID right, RegisterID dest)
			{
			if(cond == Equal || cond == Zero)
				{
				// substract with CR update				
				m_assembler.subC(dest, left, right);
				m_assembler.mfcr(dest);
				m_assembler.srwi(dest, dest, 29);
				m_assembler.andi(dest, dest, 1);
				return;
				}
			else if(cond == NotEqual || cond == NonZero)
				{
				// substract with CR update				
				m_assembler.subC(dest, left, right);
				m_assembler.mfcr(dest);
				m_assembler.srwi(dest, dest, 29);
				m_assembler.norx(dest, dest, dest);
				m_assembler.andi(dest, dest, 1);
				return;
				}
	
			RVL_JIT_ASSERT(!"TODO");
			
			#if 0
			if(cond == Equal || cond == Zero)
				{
				m_assembler.xorInsn(dest, left, right);
				m_assembler.sltiu(dest, dest, 1);
				}
			else if(cond == NotEqual || cond == NonZero)
				{
				m_assembler.xorInsn(dest, left, right);
				m_assembler.sltu(dest, PPCRegisters::zero, dest);
				}
			else if(cond == Above)
				m_assembler.sltu(dest, right, left);
			else if(cond == AboveOrEqual)
				{
				m_assembler.sltu(dest, left, right);
				m_assembler.xori(dest, dest, 1);
				}
			else if(cond == Below)
				m_assembler.sltu(dest, left, right);
			else if(cond == BelowOrEqual)
				{
				m_assembler.sltu(dest, right, left);
				m_assembler.xori(dest, dest, 1);
				}
			else if(cond == GreaterThan)
				m_assembler.slt(dest, right, left);
			else if(cond == GreaterThanOrEqual)
				{
				m_assembler.slt(dest, left, right);
				m_assembler.xori(dest, dest, 1);
				}
			else if(cond == LessThan)
				m_assembler.slt(dest, left, right);
			else if(cond == LessThanOrEqual)
				{
				m_assembler.slt(dest, right, left);
				m_assembler.xori(dest, dest, 1);
				}
			else if(cond == Overflow)
				{
				m_assembler.xorInsn(cmpTempRegister, left, right);
				m_assembler.bgez(cmpTempRegister, 4);
				m_assembler.move(dest, PPCRegisters::zero);
				m_assembler.subu(cmpTempRegister, left, right);
				m_assembler.xorInsn(cmpTempRegister, cmpTempRegister, left);
				m_assembler.slt(dest, cmpTempRegister, PPCRegisters::zero);
				}
			else if(cond == Signed)
				{
				m_assembler.subu(dest, left, right);
				// Check if the result is negative.
				m_assembler.slt(dest, dest, PPCRegisters::zero);
				}
			#endif
			}

		void set32(Condition cond, RegisterID left, Imm32 right, RegisterID dest)
			{
			move(right, immTempRegister);
			set32(cond, left, immTempRegister, dest);
			}

		void setTest8(Condition cond, Address address, Imm32 mask, RegisterID dest)
			{
			RVL_JIT_ASSERT(!"TODO");
			/*
				if (mask.m_value == -1)
					m_assembler.cmpb_im(0, address.offset, address.base);
				else
					m_assembler.testb_im(mask.m_value, address.offset, address.base);
				m_assembler.setCC_r(x86Condition(cond), dest);
				m_assembler.movzbl_rr(dest, dest);
			*/
			}


		void setTest32(Condition cond, Address address, Imm32 mask, RegisterID dest)
			{
			ASSERT((cond == Zero) || (cond == NonZero));
			load32(address, cmpTempRegister);

			if(mask.m_value == -1 && !m_fixedWidth)
				{
				// This is and and with 0xfffffff which does nothing besides setting CR
				// Just add 0 to set the CR0 flags
				m_assembler.addiC(cmpTempRegister, cmpTempRegister, 0);
				}
			else
				{
				move(mask, immTempRegister);
				m_assembler.andC(cmpTempRegister, cmpTempRegister, immTempRegister);
				}

			// Now CR0 bits are set and we need to extract and extend the result			
			m_assembler.mfcr(dest);
			m_assembler.srwi(dest, dest, 29);
			if(cond == NonZero)
				{
				m_assembler.norx(dest, dest, dest);
				}
			m_assembler.andi(dest, dest, 1);
			}

		DataLabel32 moveWithPatch(Imm32 imm, RegisterID dest)
			{
			m_fixedWidth = true;
			DataLabel32 label(this);
			move(imm, dest);
			m_fixedWidth = false;
			return label;
			}

		DataLabelPtr moveWithPatch(ImmPtr initialValue, RegisterID dest)
			{
			m_fixedWidth = true;
			DataLabelPtr label(this);
			move(initialValue, dest);
			m_fixedWidth = false;
			return label;
			}

		Jump branchPtrWithPatch(Condition cond, RegisterID left, DataLabelPtr& dataLabel, ImmPtr initialRightValue = ImmPtr(0))
			{
			m_fixedWidth = true;
			dataLabel = moveWithPatch(initialRightValue, immTempRegister);
			Jump temp = branch32(cond, left, immTempRegister);
			m_fixedWidth = false;
			return temp;
			}

		Jump branchPtrWithPatch(Condition cond, Address left, DataLabelPtr& dataLabel, ImmPtr initialRightValue = ImmPtr(0))
			{
			m_fixedWidth = true;
			load32(left, dataTempRegister);
			dataLabel = moveWithPatch(initialRightValue, immTempRegister);
			Jump temp = branch32(cond, dataTempRegister, immTempRegister);
			m_fixedWidth = false;
			return temp;
			}

		DataLabelPtr storePtrWithPatch(ImmPtr initialValue, ImplicitAddress address)
			{
			m_fixedWidth = true;
			DataLabelPtr dataLabel = moveWithPatch(initialValue, dataTempRegister);
			store32(dataTempRegister, address);
			m_fixedWidth = false;
			return dataLabel;
			}

		DataLabelPtr storePtrWithPatch(ImplicitAddress address)
			{
			return storePtrWithPatch(ImmPtr(0), address);
			}

		Call tailRecursiveCall()
			{
			// Like a normal call, but don't update the returned address register
			m_fixedWidth = true;
			
			move(Imm32(0), PPCRegisters::r9);
			m_assembler.mtctrX(PPCRegisters::r9);
			m_assembler.bctrX();

			m_fixedWidth = false;
			return Call(m_assembler.newJmpSrc(), Call::Linkable);
			}

		Call makeTailRecursiveCall(Jump oldJump)
			{
			oldJump.link(this);
			return tailRecursiveCall();
			}

		// -----------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------

		void loadDouble(ImplicitAddress address, FPRegisterID dest)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				m_assembler.lfd(dest, address.base, address.offset);
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.lfd(dest, addrTempRegister, address.offset);
				}
			}

		void storeDouble(FPRegisterID dest, ImplicitAddress address)
			{
			if(address.offset >= -32768 && address.offset <= 32767
			   && !m_fixedWidth)
				m_assembler.stfd(dest, address.base, address.offset);
			else
				{
				m_assembler.lis(addrTempRegister, (address.offset + 0x8000) >> 16);
				m_assembler.addx(addrTempRegister, addrTempRegister, address.base);
				m_assembler.stfd(dest, addrTempRegister, address.offset);
				}
			}

		void addDouble(FPRegisterID src, FPRegisterID dest)
			{
			m_assembler.faddx(dest, dest, src);
			}

		void addDouble(Address src, FPRegisterID dest)
			{
			loadDouble(src, fpTempRegister);
			m_assembler.faddx(dest, dest, fpTempRegister);
			}

		void subDouble(FPRegisterID src, FPRegisterID dest)
			{
			m_assembler.fsubx(dest, dest, src);
			}

		void subDouble(Address src, FPRegisterID dest)
			{
			loadDouble(src, fpTempRegister);
			m_assembler.fsubx(dest, dest, fpTempRegister);
			}

		void mulDouble(FPRegisterID src, FPRegisterID dest)
			{
			m_assembler.fmulx(dest, dest, src);
			}

		void mulDouble(Address src, FPRegisterID dest)
			{
			RVL_JIT_ASSERT(!"TODO");
			//loadDouble(src, fpTempRegister);
			//m_assembler.muld(dest, dest, fpTempRegister);
			}

		void convertInt32ToDouble(RegisterID src, FPRegisterID dest)
			{
			/*
			 // By the book, we need todo this:
			 fp1 = 0x43300000 80000000   (constant)
			 r0 = value to convert
			 
			 lis      r3,-32729
			 lfd      fp1,-30816(r3)  	// "somehow" get the constant into fp1
			
			 xoris    r0,r0,0x8000   	// flip sign
			 stw      r0,12(rsp)   	    // store lower half
			
			 lis      r0,17200   		// 0x4330 0000
			 stw      r0,8(rsp)   		// store upper half
			
			 lfd      fp0,8(rsp)     	// load 8 bytes (8-15)
			 fsub     fp31,fp0,fp1
			*/

			// make room on stack for conversion
			m_assembler.addi(PPCRegisters::sp, PPCRegisters::sp, -8);
			
			// Sign flip
			m_assembler.xoris(immTempRegister, src, 0x8000);
			// Store lower half
			m_assembler.stw(immTempRegister, PPCRegisters::sp, 4);

			// Get this stupid constand into some register!
			m_assembler.lis(immTempRegister, ((u32)fpConst1)>>16);
			m_assembler.ori(dataTempRegister, immTempRegister, ((u32)fpConst1)&0xffff);
			m_assembler.lfd(fpTempRegister, dataTempRegister, 0);
			
			m_assembler.lis(immTempRegister, 0x4330);
			m_assembler.stw(immTempRegister, PPCRegisters::sp, 0);

			m_assembler.lfd(dest, PPCRegisters::sp, 0);
			m_assembler.fsubx(dest, dest, fpTempRegister);
			
			// clean stack		
			m_assembler.addi(PPCRegisters::sp, PPCRegisters::sp, 8);
			}

		/*
		Jump branchTrue()
			{
			m_assembler.appendJump();
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchFalse()
			{
			m_assembler.appendJump();
			return Jump(m_assembler.newJmpSrc());
			}
		*/
		
		#ifndef _RVL_INVERTED_BRANCH_CONDITION
		
		Jump branchEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.beq(0);
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchNotEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.bne(0);
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchGreaterThan(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.bgt(0);
			return Jump(m_assembler.newJmpSrc());
					
			}
		Jump branchGreaterEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.bge(0);
			return Jump(m_assembler.newJmpSrc());
			}
			
		Jump branchLessThan(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.blt(0);
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchLessEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			//m_assembler.appendJump();
			m_assembler.ble(0);
			return Jump(m_assembler.newJmpSrc());
			}
			
		#else  // _RVL_INVERTED_BRANCH_CONDITION
			
		// This version allows _jonger_ jumps

		Jump branchEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);

			m_assembler.bne(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchNotEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			m_assembler.beq(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchGreaterThan(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			m_assembler.ble(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
					
			}
		Jump branchGreaterEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			m_assembler.blt(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}
			
		Jump branchLessThan(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			m_assembler.bge(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}

		Jump branchLessEqual(bool isSigned, RegisterID rs, RegisterID rt)
			{
			if(isSigned)
				m_assembler.cmp(rs, rt);
			else
				m_assembler.cmpl(rs, rt);
			m_assembler.bgt(2);
			m_assembler.b();
			return Jump(m_assembler.newJmpSrc());
			}
		
		#endif // _RVL_INVERTED_BRANCH_CONDITION

		Jump branchDouble(DoubleCondition cond, FPRegisterID left, FPRegisterID right)
			{
			if(cond == DoubleEqual)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.beq(0);
				#else
					m_assembler.bne(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleNotEqual)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bne(0);
				#else
					m_assembler.beq(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleGreaterThan)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bgt(0);
				#else
					m_assembler.ble(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleGreaterThanOrEqual)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bge(0);
				#else
					m_assembler.blt(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleLessThan)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.blt(0);
				#else
					m_assembler.bge(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleLessThanOrEqual)
				{
				m_assembler.fcmpo(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.ble(0);
				#else
					m_assembler.bgt(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			// ---------------------------- Unordered ---------------------------
			if(cond == DoubleEqualOrUnordered)
				{
				m_assembler.fcmpu(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.beq(0);
				#else
					m_assembler.bne(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleGreaterThanOrUnordered)
				{
				m_assembler.fcmpu(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bgt(0);
				#else
					m_assembler.ble(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleGreaterThanOrEqualOrUnordered)
				{
				m_assembler.fcmpu(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.bge(0);
				#else
					m_assembler.blt(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleLessThanOrUnordered)
				{
				m_assembler.fcmpu(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.blt(0);
				#else
					m_assembler.bge(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			if(cond == DoubleLessThanOrEqualOrUnordered)
				{
				m_assembler.fcmpu(left, right);
				#ifndef _RVL_INVERTED_BRANCH_CONDITION
					m_assembler.ble(0);
				#else
					m_assembler.bgt(2);
					m_assembler.b();
				#endif
				return Jump(m_assembler.newJmpSrc());
				}
			ASSERT(0);
			return Jump();
			}

		// Truncates 'src' to an integer, and places the resulting 'dest'.
		// If the result is not representable as a 32 bit value, branch.
		// May also branch for some values that are representable in 32 bits
		// (specifically, in this case, INT_MAX 0x7fffffff).
		Jump branchTruncateDoubleToInt32(FPRegisterID src, RegisterID dest)
			{
			RVL_JIT_ASSERT(!"TODO");
			//m_assembler.truncwd(fpTempRegister, src);
			// m_assembler.mfc1(dest, fpTempRegister);
			return branch32(Equal, dest, Imm32(0x7fffffff));
			}

	private:
		// If m_fixedWidth is true, we will generate a fixed number of instructions.
		// Otherwise, we can emit any number of instructions.
		bool m_fixedWidth;

		friend class LinkBuffer;
		friend class RepatchBuffer;

		static void linkCall(void* code, Call call, FunctionPtr function)
			{
			PPCAssembler::linkCall(code, call.m_jmp, function.value());
			}

		static void repatchCall(CodeLocationCall call, CodeLocationLabel destination)
			{
			PPCAssembler::relinkCall(call.dataLocation(), destination.executableAddress());
			}

		static void repatchCall(CodeLocationCall call, FunctionPtr destination)
			{
			PPCAssembler::relinkCall(call.dataLocation(), destination.executableAddress());
			}

		};

	}

	#endif // ENABLE(ASSEMBLER) && PLATFORM(PPC)

#endif // MacroAssemblerPPC_h

/* FYWEBKITMOD END */