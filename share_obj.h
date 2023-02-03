#pragma once
typedef struct entitylaginfo_s {
	Vector Origin;
	Vector Angles;
	int GaitSequence;
	int Sequence;
	float Frame;
	float FrameRate;
	float AnimTime;
}entitylaginfo_t;
class CEntityObject {
public:
	entitylaginfo_t pLastInfo;
	std::vector <entitylaginfo_t*> aryLagInfo;
	std::vector <float> aryLagInfoRecordTime;
	inline void Clean() {
		aryLagInfoRecordTime.clear();
		for (size_t i = 0; i < aryLagInfo.size(); i++) {
			delete aryLagInfo[i];
		}
		aryLagInfo.clear();
	}
};
CEntityObject* GetGameObject(int index);
void ClearGameObject();
void RemoveGameObject(int index);
CEntityObject* CreateGameObject(int index);