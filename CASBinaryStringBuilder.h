#pragma once
#include <string>

struct CBinaryStringBuilder {
public:
	std::string szBuffer;

	void WriteInt(int value);
	void WriteLong(long value);
	void WriteFloat(float value);
	void WriteDouble(double value);
	void WriteVector(vec3_t value);
	void WriteString(CString* value);
};

void ConstructBinaryString(void* pObject);
void DestructBinaryString(CBinaryStringBuilder* pBuilder);