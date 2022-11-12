#pragma once

typedef struct vtable_base_s {
	void (SC_SERVER_DECL* PreSpawn)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Spawn)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* PostSpawn)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Precache)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* KeyValue)(void* pThis, SC_SERVER_DUMMYARG KeyValueData* pkvd) = nullptr;
	double(SC_SERVER_DECL* GetKeyValue)(void* pThis, SC_SERVER_DUMMYARG char* szKey, void* entvartype) = nullptr;
	void (SC_SERVER_DECL* OnKeyValueUpdate)(void* pThis, SC_SERVER_DUMMYARG char* szKey) = nullptr;
	void (SC_SERVER_DECL* Save)(void* pThis, SC_SERVER_DUMMYARG void* pSave) = nullptr;
	void (SC_SERVER_DECL* Restore)(void* pThis, SC_SERVER_DUMMYARG void* pRestore) = nullptr;
	int (SC_SERVER_DECL* ObjectCaps)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Activate)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* SetObjectCollisionBox)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* GetClassification)(void* pThis, SC_SERVER_DUMMYARG int donno) = nullptr;
	void (SC_SERVER_DECL* GetClassificationTag)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* GetClassificationName)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* SetClassification)(void* pThis, SC_SERVER_DUMMYARG int classify) = nullptr;
	void* (SC_SERVER_DECL* SetClassificationSpecial)(void* pThis, SC_SERVER_DUMMYARG int classify, bool over) = nullptr;
	int (SC_SERVER_DECL* IRelationship)(void* pThis, SC_SERVER_DUMMYARG void* pOther, bool friendly) = nullptr;
	int (SC_SERVER_DECL* Classify)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* DeathNotice)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevChild) = nullptr;
	void (SC_SERVER_DECL* TraceAttack)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) = nullptr;
	int (SC_SERVER_DECL* TakeDamage)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) = nullptr;
	int (SC_SERVER_DECL* TakeHealth)(void* pThis, SC_SERVER_DUMMYARG float flHealth, int bitsDamageType, int cap) = nullptr;
	int (SC_SERVER_DECL* TakArmor)(void* pThis, SC_SERVER_DUMMYARG float flHealth, int bitsDamageType, int cap) = nullptr;
	void (SC_SERVER_DECL* Killed)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, int iGib) = nullptr;
	int (SC_SERVER_DECL* BloodColor)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* TraceBleed)(void* pThis, SC_SERVER_DUMMYARG float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) = nullptr;
	bool (SC_SERVER_DECL* IsTriggered)(void* pThis, SC_SERVER_DUMMYARG void* pActivator) = nullptr;
	void* (SC_SERVER_DECL* MyMonsterPointer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* MySquadMonsterPointer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* MyCustomPointer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* MyItemPointer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* GetToggleState)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* AddPoints)(void* pThis, SC_SERVER_DUMMYARG int score, bool bAllowNegativeScore) = nullptr;
	void (SC_SERVER_DECL* AddPointsToTeam)(void* pThis, SC_SERVER_DUMMYARG int score, bool bAllowNegativeScore) = nullptr;
	bool (SC_SERVER_DECL* AddPlayerItem)(void* pThis, SC_SERVER_DUMMYARG void* pItem) = nullptr;
	bool (SC_SERVER_DECL* RemovePlayerItem)(void* pThis, SC_SERVER_DUMMYARG void* pItem) = nullptr;
	int (SC_SERVER_DECL* GiveAmmo)(void* pThis, SC_SERVER_DUMMYARG int iAmount, const char* szName, int iMax) = nullptr;
	float (SC_SERVER_DECL* GetDelay)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* IsMoving)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* OverrideReset)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* DamageDecal)(void* pThis, SC_SERVER_DUMMYARG int bitsDamageType) = nullptr;
	void (SC_SERVER_DECL* SetToggleState)(void* pThis, SC_SERVER_DUMMYARG int state) = nullptr;
	void (SC_SERVER_DECL* StartSneaking)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* StopSneaking)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* OnControls)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pev) = nullptr;
	bool (SC_SERVER_DECL* IsSneaking)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsAlive)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsBSPModel)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* ReflectGauss)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* HasTarget)(void* pThis, SC_SERVER_DUMMYARG string_t targetname) = nullptr;
	bool (SC_SERVER_DECL* IsInWorld)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsMonster)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsPlayer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsNetClient)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsPointEnt)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsBreakable)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* IsMachine)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	const char* (SC_SERVER_DECL* TeamID)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* CriticalRemove)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* GetNextTarget)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Think)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Touch)(void* pThis, SC_SERVER_DUMMYARG void* pOther) = nullptr;
	void (SC_SERVER_DECL* Use)(void* pThis, SC_SERVER_DUMMYARG void* pActivator, void* pCaller, int useType, float value) = nullptr;
	void (SC_SERVER_DECL* Blocked)(void* pThis, SC_SERVER_DUMMYARG void* pOther) = nullptr;
	void (SC_SERVER_DECL* UpdateOnRemove)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void* (SC_SERVER_DECL* Respawn)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* SUB_UseTargets)(void* pThis, SC_SERVER_DUMMYARG void* pActivator, void* pCaller, int useType, float value) = nullptr;
	void (SC_SERVER_DECL* IsLockedByMaster)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* UpdateOwner)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* FBecomeProne)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	Vector* (SC_SERVER_DECL* Center)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	Vector* (SC_SERVER_DECL* EyePosition)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	Vector* (SC_SERVER_DECL* EarPosition)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	Vector* (SC_SERVER_DECL* BodyTarget)(void* pThis, SC_SERVER_DUMMYARG const Vector& posSrc) = nullptr;
	int (SC_SERVER_DECL* Illumination)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	bool (SC_SERVER_DECL* FVisible)(void* pThis, SC_SERVER_DUMMYARG void* pEntity) = nullptr;
	bool (SC_SERVER_DECL* FVisibleVector)(void* pThis, SC_SERVER_DUMMYARG const Vector& vecOrigin) = nullptr;
	bool (SC_SERVER_DECL* FVisibleFromPos)(void* pThis, SC_SERVER_DUMMYARG Vector* pos, Vector* angle) = nullptr;
	bool (SC_SERVER_DECL* IsFacing)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevOther, float dis) = nullptr;
	float (SC_SERVER_DECL* GetPointsForDamage)(void* pThis, SC_SERVER_DUMMYARG float damage) = nullptr;
	void (SC_SERVER_DECL* GetDamagePoints)(void* pThis, SC_SERVER_DUMMYARG entvars_t* pevAttacker, entvars_t* pevInfictor, float damage) = nullptr;
	void (SC_SERVER_DECL* SetPlayerAlly)(void* pThis, SC_SERVER_DUMMYARG bool dunno) = nullptr;
	void (SC_SERVER_DECL* Deconstructor1)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Deconstructor2)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* OnCreate)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* OnDestroy)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* OnSetOriginByMap)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* IsRevivable)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* BeginRevive)(void* pThis, SC_SERVER_DUMMYARG float flRespawn) = nullptr;
	void (SC_SERVER_DECL* EndRevive)(void* pThis, SC_SERVER_DUMMYARG float flRespawn) = nullptr;
	int (SC_SERVER_DECL* ShowHUDInfo)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* ShouldDisablePlayerCollisions)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	Vector* (SC_SERVER_DECL* GetAttackVectors)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* Teleport)(void* pThis, SC_SERVER_DUMMYARG Vector vecPos, Vector vecAng) = nullptr;
	void (SC_SERVER_DECL* SetTopColor)(void* pThis, SC_SERVER_DUMMYARG int color) = nullptr;
	void (SC_SERVER_DECL* SetBottomColor)(void* pThis, SC_SERVER_DUMMYARG int color) = nullptr;
	void (SC_SERVER_DECL* SetColors)(void* pThis, SC_SERVER_DUMMYARG int topcolor, int bottomcolor) = nullptr;
	int (SC_SERVER_DECL* GetTopColor)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	int (SC_SERVER_DECL* GetBottomColor)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
	void (SC_SERVER_DECL* UpdateColorMap)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA ) = nullptr;
} vtable_base_t;
typedef struct vtable_delay_s : vtable_base_s {
	void (SC_SERVER_DECL* DelayThink)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
}vtable_delay_t;
typedef struct vtable_animating_s : vtable_delay_s {
	void (SC_SERVER_DECL* HandleAnimEvent)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA, void* pEvent) = nullptr;
}vtable_animating_t;
typedef struct vtable_physicsobject_s : vtable_animating_s {
	void (SC_SERVER_DECL* WorldInit)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* Materialize)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* TouchedWorld)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA, bool touch) = nullptr;
	void (SC_SERVER_DECL* Kill)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* GetBounceSound)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* FallInit)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
}vtable_physicsobject_t;
typedef struct vtable_pickupobject_s : vtable_physicsobject_s {
	void (SC_SERVER_DECL* CanCollect)(void* pThis, SC_SERVER_DUMMYARG void* pOther, int iCollectType) = nullptr;
	void (*__purecall)() = nullptr;
	void (SC_SERVER_DECL* Collected)(void* pThis, SC_SERVER_DUMMYARG void* pOther, int iCollectTyp) = nullptr;
	void (SC_SERVER_DECL* DefaultUse)(void* pThis, SC_SERVER_DUMMYARG void* pActivator, void* pCaller, int useType, float value) = nullptr;
	void (SC_SERVER_DECL* Dropped)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA, void* pNewEntity) = nullptr;
	float (SC_SERVER_DECL* GetFadeDelay)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
}vtable_pickupobject_t;
typedef struct vtable_playeritem_s : vtable_pickupobject_s {
	int (SC_SERVER_DECL* AddToPlayer)(void* pThis, SC_SERVER_DUMMYARG void* pPlayer) = nullptr;
	int (SC_SERVER_DECL* AddDuplicate)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* AddAmmoFromItem)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	char* (SC_SERVER_DECL* GetPickupSound)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* GetItemInfo)(void* pThis, SC_SERVER_DUMMYARG  void* pItemInfo) = nullptr;
	int (SC_SERVER_DECL* CanDeploy)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* Deploy)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* CanHolster)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* Holster)(void* pThis, SC_SERVER_DUMMYARG int skiplocal) = nullptr;
	void (SC_SERVER_DECL* UpdateItemInfo)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* ItemPreFrame)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* ItemPostFrame)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* InactiveItemPreFrame)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* InactiveItemPostFrame)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* AttachToPlayer)(void* pThis, SC_SERVER_DUMMYARG void* pPlayer) = nullptr;
	void (SC_SERVER_DECL* DetachFromPlayer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* PrimaryAmmoIndex)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* SecondaryAmmoIndex)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* UpdateClientData)(void* pThis, SC_SERVER_DUMMYARG void* pPlayer) = nullptr;
	void* (SC_SERVER_DECL* GetWeaponPtr)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* iItemSlot)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	float (SC_SERVER_DECL* GetRespawnTime)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void* (SC_SERVER_DECL* DropItem)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* CanHaveDuplicates)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
}vtable_playeritem_t;
typedef struct vtable_playerweapon_s : vtable_playeritem_s {
	void (SC_SERVER_DECL* ExtractAmmoFromItem)(void* pThis, SC_SERVER_DUMMYARG void* pItem) = nullptr;
	void (SC_SERVER_DECL* ExtractAmmo)(void* pThis, SC_SERVER_DUMMYARG void* pOtherWeapon) = nullptr;
	int (SC_SERVER_DECL* ExtractClipAmmo)(void* pThis, SC_SERVER_DUMMYARG void* pOtherWeapon) = nullptr;
	int (SC_SERVER_DECL* AddWeapon)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* GetAmmo1Drop)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* GetAmmo2Drop)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* PlayEmptySound)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* ResetEmptySound)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* SendWeaponAnim)(void* pThis, SC_SERVER_DUMMYARG int index, int skiplocal, int body) = nullptr;
	void (SC_SERVER_DECL* BulletAccuracy)(void* pThis, SC_SERVER_DUMMYARG Vector vecMoving, Vector vecStanding, Vector vecCrouched) = nullptr;
	int (SC_SERVER_DECL* IsUseable)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* PrimaryAttack)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* SecondaryAttack)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* TertiaryAttack)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* Reload)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* FinishReload)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* ShouldReload)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* WeaponIdle)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* RetireWeapon)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* ShouldWeaponIdle)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* UseDecrement)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* BurstSupplement)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* GetP_Model)(void* pThis, SC_SERVER_DUMMYARG char* szOut) = nullptr;
	void (SC_SERVER_DECL* GetW_Model)(void* pThis, SC_SERVER_DUMMYARG char* szOut) = nullptr;
	void (SC_SERVER_DECL* GetV_Model)(void* pThis, SC_SERVER_DUMMYARG char* szOut) = nullptr;
	void (SC_SERVER_DECL* PrecacheCustomModels)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* GetWeaponData)(void* pThis, SC_SERVER_DUMMYARG weapon_data_s* pData) = nullptr;
	void (SC_SERVER_DECL* SetWeaponData)(void* pThis, SC_SERVER_DUMMYARG weapon_data_s* pData) = nullptr;
	void (SC_SERVER_DECL* IsMultiplayer)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	int (SC_SERVER_DECL* FRunfuncs)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* SetFOV)(void* pThis, SC_SERVER_DUMMYARG int iFOV) = nullptr;
	int (SC_SERVER_DECL* FRunfuncs2)(void* pThis SC_SERVER_DUMMYARG_NOCOMMA) = nullptr;
	void (SC_SERVER_DECL* CustomDecrement)(void* pThis, SC_SERVER_DUMMYARG float flDecrement) = nullptr;
	void (SC_SERVER_DECL* SetV_Model)(void* pThis, SC_SERVER_DUMMYARG char* szModel) = nullptr;
	void (SC_SERVER_DECL* SetP_Model)(void* pThis, SC_SERVER_DUMMYARG char* szModel) = nullptr;
	void (SC_SERVER_DECL* ChangeWeaponSkin)(void* pThis, SC_SERVER_DUMMYARG short iskin) = nullptr;
}vtable_playerweapon_t;

vtable_base_t* GetEntityVTable(const char* szClassName);
vtable_base_s* AddEntityVTable(const char* szClassName);