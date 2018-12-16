#include "../../Headers/DataStructures/Bitset.h"
#include <fstream>
using namespace lun;

Bitset::Bitset(u32 bits) {
	length = (u32)Math<f32>::ceil(bits / 32.f);
	if (length == 0)
		length = 1;
	groteBeetjesVlag = new u32[length];
	memset(groteBeetjesVlag, 0, sizeof(u32) * length);
	this->bits = bits;
}

//Delete the bitset
Bitset::~Bitset() { delete[] groteBeetjesVlag; }

//Copy constructor
Bitset::Bitset(const Bitset &b) {
	groteBeetjesVlag = new u32[length = b.length];
	bits = b.bits;
	for (u32 i = 0; i < length; ++i)
		groteBeetjesVlag[i] = b.groteBeetjesVlag[i];
}

//Assign
Bitset &Bitset::operator=(const Bitset &b) {
	groteBeetjesVlag = new u32[length = b.length];
	bits = b.bits;
	for (u32 i = 0; i < length; ++i)
		groteBeetjesVlag[i] = b.groteBeetjesVlag[i];
	return *this;
}

//Grab a bit at offset
bool Bitset::operator[](u32 offset) const {
	if (offset >= bits)
		return false;
	u32 val = *(groteBeetjesVlag + offset / 32);
	return (val >> (31 - offset % 32)) & 0x1;
}

//Set the bit at offset to flag
void Bitset::set(u32 offset, bool flag) {
	if (offset >= bits)
		return;

	u32 &val = *(groteBeetjesVlag + offset / 32);

	if (flag)
		val |= (u32)1 << (31 - offset % 32);
	else
		val &= ~((u32)1 << (31 - offset % 32));
}

//Performs and gate at offset
void Bitset::AND(u32 offset, bool flag) {
	set(offset, (*this)[offset] && flag);
}

//Performs or gate at offset
void Bitset::OR(u32 offset, bool flag) {
	set(offset, (*this)[offset] || flag);
}

//Performs xor gate at offset
void Bitset::XOR(u32 offset, bool flag) {
	set(offset, (*this)[offset] != flag);
}

//Performs nand gate at offset
void Bitset::NAND(u32 offset, bool flag) {
	set(offset, !((*this)[offset] && flag));
}

//Performs nor gate at offset
void Bitset::NOR(u32 offset, bool flag) {
	set(offset, !((*this)[offset] || flag));
}

//Performs nxor gate at offset
void Bitset::NXOR(u32 offset, bool flag) {
	set(offset, (*this)[offset] == flag);
}

//Performs not gate at offset
void Bitset::NOT(u32 offset) {
	set(offset, !(*this)[offset]);
}

//Performs not gate
void Bitset::NOT() {
	for (u32 i = 0; i < length; ++i)
		groteBeetjesVlag[i] = ~groteBeetjesVlag[i];
}

//Performs or gate
void Bitset::OR(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) break;
		groteBeetjesVlag[i] |= b.groteBeetjesVlag[i];
	}
}

//Performs nor gate
void Bitset::NOR(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) break;
		groteBeetjesVlag[i] = ~(groteBeetjesVlag[i] | b.groteBeetjesVlag[i]);
	}
}

//Performs and gate
void Bitset::AND(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) {
			groteBeetjesVlag[i] = 0;
			continue;
		}
		groteBeetjesVlag[i] &= b.groteBeetjesVlag[i];
	}
}

//Performs nor gate
void Bitset::NAND(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) {
			groteBeetjesVlag[i] = 0;
			continue;
		}
		groteBeetjesVlag[i] = ~(groteBeetjesVlag[i] & b.groteBeetjesVlag[i]);
	}
}

//Performs xor gate
void Bitset::XOR(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) {
			groteBeetjesVlag[i] = 0;
			continue;
		}
		groteBeetjesVlag[i] ^= b.groteBeetjesVlag[i];
	}
}

//Performs nxor gate
void Bitset::NXOR(const Bitset &b) {
	for (u32 i = 0; i < length; ++i) {
		if (i >= b.length) {
			groteBeetjesVlag[i] = 0;
			continue;
		}
		groteBeetjesVlag[i] = ~(groteBeetjesVlag[i] ^ b.groteBeetjesVlag[i]);
	}
}

//Copy data from one bitset to another
void Bitset::copy(u32 oldStart, u32 oldEnd, const Bitset &b, u32 newStart, u32 newEnd) {
	for (u32 i = 0; i < newEnd - newStart; ++i) {
		if (i >= oldEnd - oldStart)
			set(newStart + i, false);
		else
			set(newStart + i, b[i + oldStart]);
	}
}

//u8
Bitset Bitset::getBits(u8 i) {
	u32 len = 8;
	Bitset b(len);
	for (u32 j = 0; j < len; ++j) 
		b.set(j, (i & ((u8)0b1 << (len - 1 - j))) != 0);
	return b;
}
Bitset Bitset::getBits(i8 i) { return getBits(*(u8*)&i); }

//u16
Bitset Bitset::getBits(u16 i) {
	u32 len = 16;
	Bitset b(len);
	for (u32 j = 0; j < len; ++j)
		b.set(j, (i & ((u16)0b1 << (len - 1 - j))) != 0);
	return b;
}
Bitset Bitset::getBits(i16 i) { return getBits(*(u16*)&i); }

//u32
Bitset Bitset::getBits(u32 i) {
	u32 len = 32;
	Bitset b(len);
	for (u32 j = 0; j < len; ++j) 
		b.set(j, (i & ((u32)0b1 << (len - 1 - j))) != 0);
	return b;
}
Bitset Bitset::getBits(i32 i) { return getBits(*(u32*)&i); }

//u64
Bitset Bitset::getBits(u64 i) {
	u32 len = 8;
	Bitset b(len);
	for (u32 j = 0; j < len; ++j)
		b.set(j, (i & ((u64)0b1 << (len - 1 - j))) != 0);
	return b;
}
Bitset Bitset::getBits(i64 i) { return getBits(*(u64*)&i); }

//f<x>
Bitset Bitset::getBits(f32 f) { return getBits(*(u32*)&f); }
Bitset Bitset::getBits(f64 f) { return getBits(*(u64*)&f); }

//std::string
Bitset Bitset::getBits(std::string s) {
	Bitset b((u32)s.size() * 8);
	for (u32 i = 0; i < b.getBytes(); ++i) {
		char &c = s[i];
		u8 &u = *(u8*)&c;
		b.writeUByte(u, i * 8);
	}
	return b;
}

//Operators
Bitset &Bitset::operator^=(const Bitset &b) { XOR(b); return *this; }
Bitset &Bitset::operator&=(const Bitset &b) { AND(b); return *this; }
Bitset &Bitset::operator|=(const Bitset &b) { OR(b); return *this; }
Bitset Bitset::operator^(const Bitset &b) { Bitset copy = *this; copy.XOR(b); return copy; }
Bitset Bitset::operator&(const Bitset &b) { Bitset copy = *this; copy.AND(b); return copy; }
Bitset Bitset::operator|(const Bitset &b) { Bitset copy = *this; copy.OR(b); return copy; }
Bitset Bitset::operator+(const Bitset &b) {
	Bitset b2 = Bitset(bits + b.bits);
	for (u32 i = 0; i < bits; ++i)
		b2.set(i, (*this)[i]);
	for (u32 i = 0; i < b.bits; ++i)
		b2.set(i + bits, b[i]);
	return b2;
}

//Printing data
void Bitset::print(u32 printType) {
	if (printType == 1) {
		for (u32 i = 0; i < bits / 4; i++) {
			bool a = (*this)[i * 4];
			bool b = (*this)[i * 4 + 1];
			bool c = (*this)[i * 4 + 2];
			bool d = (*this)[i * 4 + 3];
			u8 val = ((u8)a << 3) | ((u8)b << 2) | ((u8)c << 1) | (u8)d;

			printf("%c", val < 10 ? '0' + val : 'A' + val - 10);
			if ((i + 1) % 16 == 0)
				printf("\n");
			else if ((i + 1) % 2 == 0)
				printf("\t\t");
		}
		printf("\n");
	}
	else if (printType == 2) {
		print(0);
		print(1);
	}
	else {
		for (u32 i = 0; i < bits; i++) {
			printf("%c", (*this)[i] ? '1' : '0');
			if ((i + 1) % 8 == 0)
				printf("\t");
		}
		printf("\n");
	}
}

//Getters

u32 Bitset::getLength() { return length; }
u32 Bitset::getBits() { return bits; }

//From and to char*

char *Bitset::copyData() {
	char *data = new char[length*4];
	for (u32 i = 0; i < length*4; ++i) {
		u32 j = groteBeetjesVlag[i / 4];
		u8 dat = (j >> ((3 - i % 4) * 8)) & 0xFF;
		data[i] = *(char*)&dat;
	}
	return data;
}

Bitset Bitset::readData(char *c, u32 length) {
	Bitset b(length * 8);
	for (u32 i = 0; i < length; ++i) {
		u32 val = (u32)*(u8*)&c[i];
		u32 dat = val << ((3 - i % 4) * 8);
		b.groteBeetjesVlag[i / 4] |= dat;
	}
	return b;
}

Bitset Bitset::readData(std::string path) {
	std::ifstream i(path, std::ios::in | std::ios::binary);
	if (!i.good()) {
		printf("Couldn't open file at \"%s\". File can't be opened!\n", path.c_str());
		return Bitset(1);
	}
	i.seekg(0, std::ios::end);
	u32 len = (u32)i.tellg();
	i.seekg(0, std::ios::beg);
	char *buf = new char[len];
	i.read(buf, len);
	i.close();
	Bitset b = Bitset::readData(buf, len);
	delete[] buf;
	return b;
}

//Reading integers & floats

u64 Bitset::readInteger(u32 start, u32 length) {
	u64 result = 0;
	for (u32 i = 0; i < length; ++i) 
		result |= (u64)((*this)[start + i]) << (length - 1 - i);
	return result;
}

u64 Bitset::readULong(u32 index) { return readInteger(index, 64); }
u32 Bitset::readUInt(u32 index) { return (u32)readInteger(index, 32); }
u16 Bitset::readUShort(u32 index) { return (u16)readInteger(index, 16); }
u8 Bitset::readUByte(u32 index) { return (u8)readInteger(index, 8); }

i64 Bitset::readLong(u32 index) { u64 val = readULong(index);  return *(i64*)&val; }
i32 Bitset::readInt(u32 index) { u32 val = readUInt(index);  return *(i32*)&val; }
i16 Bitset::readShort(u32 index) { u16 val = readUShort(index);  return *(i16*)&val; }
i8 Bitset::readByte(u32 index) { u8 val = readUByte(index);  return *(i8*)&val; }

f64 Bitset::readDouble(u32 index) { u64 val = readULong(index);  return *(f64*)&val; }
f32 Bitset::readFloat(u32 index) { u32 val = readUInt(index);  return *(f32*)&val; }

std::string Bitset::readString(u32 index, u32 length) {
	std::string str(length, ' ');
	for (u32 i = 0; i < length; ++i) {
		u8 u = readUByte(index + i * 8);
		char c = *(char*)&u;
		str[i] = c;
	}
	return str;
}

u64 *Bitset::readULongArray(u32 index, u32 length) {
	u64 *arr = new u64[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readULong(index + i * 64);
	return arr;
}

u32 *Bitset::readUIntArray(u32 index, u32 length) {
	u32 *arr = new u32[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readUInt(index + i * 32);
	return arr;
}

u16 *Bitset::readUShortArray(u32 index, u32 length) {
	u16 *arr = new u16[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readUShort(index + i * 16);
	return arr;
}

u8 *Bitset::readUByteArray(u32 index, u32 length) {
	u8 *arr = new u8[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readUByte(index + i * 8);
	return arr;
}

i64 *Bitset::readLongArray(u32 index, u32 length) {
	i64 *arr = new i64[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readLong(index + i * 64);
	return arr;
}

i32 *Bitset::readIntArray(u32 index, u32 length) {
	i32 *arr = new i32[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readInt(index + i * 32);
	return arr;
}

i16 *Bitset::readShortArray(u32 index, u32 length) {
	i16 *arr = new i16[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readShort(index + i * 16);
	return arr;
}

i8 *Bitset::readByteArray(u32 index, u32 length) {
	i8 *arr = new i8[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readByte(index + i * 8);
	return arr;
}

f32 *Bitset::readFloatArray(u32 index, u32 length) {
	f32 *arr = new f32[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readFloat(index + i * 32);
	return arr;
}

f64 *Bitset::readDoubleArray(u32 index, u32 length) {
	f64 *arr = new f64[length];
	for (u32 i = 0; i < length; ++i)
		arr[i] = readDouble(index + i * 64);
	return arr;
}

//Writing integers & floats

void Bitset::writeULong(u64 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 64, b, index, index + 64);
}

void Bitset::writeUInt(u32 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 32, b, index, index + 32);
}

void Bitset::writeUShort(u16 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 16, b, index, index + 16);
}

void Bitset::writeUByte(u8 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 8, b, index, index + 8);
}

void Bitset::writeLong(i64 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 64, b, index, index + 64);
}

void Bitset::writeInt(i32 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 32, b, index, index + 32);
}

void Bitset::writeShort(i16 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 16, b, index, index + 16);
}

void Bitset::writeByte(i8 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 8, b, index, index + 8);
}

void Bitset::writeDouble(f64 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 64, b, index, index + 64);
}

void Bitset::writeFloat(f32 value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, 32, b, index, index + 32);
}

void Bitset::writeString(std::string value, u32 index) {
	Bitset b = Bitset::getBits(value);
	copy(0, (u32)value.size() * 8, b, index, index + (u32)value.size() * 8);
}

void Bitset::writeUByteArray(u8 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeUByte(value[i], index + 8 * i);
}

void Bitset::writeByteArray(i8 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeByte(value[i], index + 8 * i);
}

void Bitset::writeUShortArray(u16 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeUShort(value[i], index + 16 * i);
}

void Bitset::writeShortArray(i16 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeShort(value[i], index + 16 * i);
}

void Bitset::writeUIntArray(u32 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeUInt(value[i], index + 32 * i);
}

void Bitset::writeIntArray(i32 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeInt(value[i], index + 32 * i);
}

void Bitset::writeULongArray(u64 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeULong(value[i], index + 64 * i);
}

void Bitset::writeLongArray(i64 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeLong(value[i], index + 64 * i);
}

void Bitset::writeFloatArray(f32 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeFloat(value[i], index + 32 * i);
}

void Bitset::writeDoubleArray(f64 *value, u32 index, u32 length) {
	for (u32 i = 0; i < length; ++i)
		writeDouble(value[i], index + 64 * i);
}

u32 Bitset::getBytes() {
	return bits / 8;
}