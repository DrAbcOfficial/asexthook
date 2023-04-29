#include <extdll.h>

#include "angelscript.h"

#include <meta_api.h>

#include "CASBinaryStringBuilder.h"

CBinaryStringBuilder::CBinaryStringBuilder(){
	refCount = 1;
}
CBinaryStringBuilder* CBinaryStringBuilder::Factory() {
	return new CBinaryStringBuilder();
}

void CBinaryStringBuilder::Get(CString* buffer){
	buffer->assign(this->szBuffer.c_str(), this->szBuffer.length());
}
void CBinaryStringBuilder::Set(CString* buffer){
	this->szBuffer = buffer->c_str();
	this->iReadPointer = 0;
}
size_t CBinaryStringBuilder::GetReadPointer(){
	return this->iReadPointer;
}
void CBinaryStringBuilder::SetReadPointer(size_t pointer){
	this->iReadPointer = min(this->szBuffer.length(), pointer);
}
template <typename T>
void WriteBuffer(CBinaryStringBuilder* pThis, T value) {
	size_t length = sizeof(value);
	for (size_t i = 0; i < length; i++) {
		pThis->szBuffer += static_cast<char>(value << (i * 8) >> ((length - 1) * 8));
	}
}
void CBinaryStringBuilder::WriteInt(int value){
	WriteBuffer(this, value);
}
void CBinaryStringBuilder::WriteLong(int64 value){
	WriteBuffer(this, value);
}
void CBinaryStringBuilder::WriteFloat(float value){
	WriteBuffer(this, std::bit_cast<int>(value));
}
void CBinaryStringBuilder::WriteDouble(double value){
	WriteBuffer(this, std::bit_cast<int64>(value));
}
void CBinaryStringBuilder::WriteVector(vec3_t value){
	WriteBuffer(this, std::bit_cast<int>(value.x));
	WriteBuffer(this, std::bit_cast<int>(value.y));
	WriteBuffer(this, std::bit_cast<int>(value.z));
}
void CBinaryStringBuilder::WriteString(CString* value){
	this->szBuffer += value->c_str();
}
template <typename T1, typename T2>
T1 ReadBuffer(CBinaryStringBuilder* pThis) {
	T2 temp = 0;
	size_t length = sizeof(T2);
	for (size_t i = 0; i < length; i++) {
		temp += static_cast<T2>(pThis->szBuffer[pThis->iReadPointer]) << ((length - 1 - i) * 8);
		pThis->iReadPointer++;
	}
	return std::bit_cast<T1>(temp);
}
int CBinaryStringBuilder::ReadInt(){
	return iReadPointer < szBuffer.length() ? ReadBuffer<int, int>(this) : 0;
}
int64 CBinaryStringBuilder::ReadLong(){
	return iReadPointer < szBuffer.length() ? ReadBuffer<int64, int64>(this) : 0;
}
float CBinaryStringBuilder::ReadFloat(){
	return iReadPointer < szBuffer.length() ? ReadBuffer<float, int>(this) : 0.0f;
}
double CBinaryStringBuilder::ReadDouble(){
	return iReadPointer < szBuffer.length() ? ReadBuffer<double, int64>(this) : 0.0;
}
void CBinaryStringBuilder::ReadVector(vec3_t vecBuffer){
	vecBuffer.x = ReadBuffer<float, int>(this);
	vecBuffer.y = ReadBuffer<float, int>(this);
	vecBuffer.z = ReadBuffer<float, int>(this);
}
void CBinaryStringBuilder::ReadString(CString* szOutBuffer){
	std::string temp;
	for (size_t i = iReadPointer; i < szBuffer.length(); i++) {
		char c = szBuffer[iReadPointer];
		temp += c;
		iReadPointer++;
		if (c == '\0')
			break;
	}
	szOutBuffer->assign(temp.c_str(), temp.length());
}
bool CBinaryStringBuilder::IsReadToEnd(){
	return iReadPointer >= szBuffer.length();
}