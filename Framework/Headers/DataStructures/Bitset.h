#pragma once
#include "../Type/OTypes.h"
#include "../Math/Math.h"
namespace lun {
	class Bitset {
	public:
		//Allocate a bitset with length u32 bits
		Bitset(u32 bits);

		//Delete the bitset
		~Bitset();

		//Copy constructor
		Bitset(const Bitset &b);

		//Assign
		Bitset &operator=(const Bitset &b);

		//Grab a bit at offset
		bool operator[](u32 offset) const;

		//Set the bit at offset to flag
		void set(u32 offset, bool flag);

		//Performs and gate at offset
		void AND(u32 offset, bool flag);

		//Performs or gate at offset
		void OR(u32 offset, bool flag);

		//Performs xor gate at offset
		void XOR(u32 offset, bool flag);

		//Performs nand gate at offset
		void NAND(u32 offset, bool flag);

		//Performs nor gate at offset
		void NOR(u32 offset, bool flag);

		//Performs nxor gate at offset
		void NXOR(u32 offset, bool flag);

		//Performs not gate at offset
		void NOT(u32 offset);

		//Performs not gate
		void NOT();

		//Performs or gate
		void OR(const Bitset &b);

		//Performs nor gate
		void NOR(const Bitset &b);

		//Performs and gate
		void AND(const Bitset &b);

		//Performs nand gate
		void NAND(const Bitset &b);

		//Performs xor gate
		void XOR(const Bitset &b);

		//Performs nxor gate
		void NXOR(const Bitset &b);

		//Copy a bitset
		void copy(u32 oldStart, u32 oldEnd, const Bitset &b, u32 newStart, u32 newEnd);

		//Prints data
		//@optional u32 printType; default = 0
		//			printType = 0; binary
		//			printType = 1; hex
		//			printType = 2; both
		//			default;	   binary
		void print(u32 printType=0);

		Bitset &operator^=(const Bitset &b);
		Bitset &operator&=(const Bitset &b);
		Bitset &operator|=(const Bitset &b);
		Bitset operator^(const Bitset &b);
		Bitset operator&(const Bitset &b);
		Bitset operator|(const Bitset &b);
		Bitset operator+(const Bitset &b);

		//Get bits of u8 (big endian)
		static Bitset getBits(u8 i);

		//Get bits of i8 (big endian)
		static Bitset getBits(i8 i);

		//Get bits of u16 (big endian)
		static Bitset getBits(u16 i);

		//Get bits of i16 (big endian)
		static Bitset getBits(i16 i);

		//Get bits of u32 (big endian)
		static Bitset getBits(u32 i);

		//Get bits of i32 (big endian)
		static Bitset getBits(i32 i);

		//Get bits of u64 (big endian)
		static Bitset getBits(u64 i);

		//Get bits of i64 (big endian)
		static Bitset getBits(i64 i);

		//Get bits of f32 (big endian)
		static Bitset getBits(f32 f);

		//Get bits of f64 (big endian)
		static Bitset getBits(f64 f);

		//Get bits of std::string (big endian)
		static Bitset getBits(std::string s);

		
		//Read ulong from bitset
		u64 readULong(u32 index);

		//Read uint from bitset
		u32 readUInt(u32 index);

		//Read ushort from bitset
		u16 readUShort(u32 index);

		//Read ubyte from bitset
		u8 readUByte(u32 index);

		//Read long from bitset
		i64 readLong(u32 index);

		//Read int from bitset
		i32 readInt(u32 index);

		//Read short from bitset
		i16 readShort(u32 index);

		//Read byte from bitset
		i8 readByte(u32 index);

		//Read float from bitset
		f32 readFloat(u32 index);

		//Read double from bitset
		f64 readDouble(u32 index);

		//Read string from bitset
		//@param u32 length; in bytes
		std::string readString(u32 index, u32 length);

		//Read ulongs from bitset
		u64 *readULongArray(u32 index, u32 length);

		//Read uints from bitset
		u32 *readUIntArray(u32 index, u32 length);

		//Read ushorts from bitset
		u16 *readUShortArray(u32 index, u32 length);

		//Read ubytes from bitset
		u8 *readUByteArray(u32 index, u32 length);

		//Read longs from bitset
		i64 *readLongArray(u32 index, u32 length);

		//Read ints from bitset
		i32 *readIntArray(u32 index, u32 length);

		//Read shorts from bitset
		i16 *readShortArray(u32 index, u32 length);

		//Read bytes from bitset
		i8 *readByteArray(u32 index, u32 length);

		//Read floats from bitset
		f32 *readFloatArray(u32 index, u32 length);

		//Read doubles from bitset
		f64 *readDoubleArray(u32 index, u32 length);


		//Write ulong to bitset
		void writeULong(u64 value, u32 index);

		//Write uint to bitset
		void writeUInt(u32 value, u32 index);

		//Write ushort to bitset
		void writeUShort(u16 value, u32 index);

		//Write ubyte to bitset
		void writeUByte(u8 value, u32 index);

		//Write long to bitset
		void writeLong(i64 value, u32 index);

		//Write int to bitset
		void writeInt(i32 value, u32 index);

		//Write short to bitset
		void writeShort(i16 value, u32 index);

		//Write byte to bitset
		void writeByte(i8 value, u32 index);

		//Write float to bitset
		void writeFloat(f32 value, u32 index);

		//Write double to bitset
		void writeDouble(f64 value, u32 index);

		//Write std::string to bitset
		void writeString(std::string value, u32 index);

		//Write ubytes to bitset
		void writeUByteArray(u8 *value, u32 index, u32 length);

		//Write ushorts to bitset
		void writeUShortArray(u16 *value, u32 index, u32 length);

		//Write uints to bitset
		void writeUIntArray(u32 *value, u32 index, u32 length);

		//Write ulongs to bitset
		void writeULongArray(u64 *value, u32 index, u32 length);

		//Write bytes to bitset
		void writeByteArray(i8 *value, u32 index, u32 length);

		//Write shorts to bitset
		void writeShortArray(i16 *value, u32 index, u32 length);

		//Write ints to bitset
		void writeIntArray(i32 *value, u32 index, u32 length);

		//Write longs to bitset
		void writeLongArray(i64 *value, u32 index, u32 length);

		//Write floats to bitset
		void writeFloatArray(f32 *value, u32 index, u32 length);

		//Write doubles to bitset
		void writeDoubleArray(f64 *value, u32 index, u32 length);


		//Get length in uints
		u32 getLength();

		//Get length in bytes
		u32 getBytes();
		
		//Get length in bits
		u32 getBits();

		//Copy data from ??? endian integer array to big endian byte array
		char *copyData();

		//Copy data from file to big endian byte array
		static Bitset readData(std::string path);

		//Copy data from big endian byte array to ??? endian integer array
		static Bitset readData(char *c, u32 length);

	protected:
		u64 readInteger(u32 start, u32 length);

	private:
		u32 *groteBeetjesVlag;
		u32 length, bits;
	};
}