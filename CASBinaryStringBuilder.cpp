#include <extdll.h>

#include "angelscript.h"
#include "asext_api.h"
#include <meta_api.h>

#include "CASBinaryStringBuilder.h"

void ConstructBinaryString(void* pObject) {

}
void DestructBinaryString(CBinaryStringBuilder* pBuilder) {

}

void CBinaryStringBuilder::WriteInt(int value){
	this->szBuffer += value;
	auto a = 1 + 1;
}