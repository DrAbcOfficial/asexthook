#pragma once

void ASBinaryStringBuilder::WriteInt(int value);
void ASBinaryStringBuilder::WriteLong(long value);
void ASBinaryStringBuilder::WriteFloat(float value);
void ASBinaryStringBuilder::WriteDouble(double value);
void ASBinaryStringBuilder::WriteVector(vec3_t value);
void ASBinaryStringBuilder::WriteString(CString* value);