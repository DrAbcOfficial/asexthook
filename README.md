# `ASExtHook`: Plugin to extend Sven Co-op script <img align="right" src="./img/logo.png" width="140" height="140" alt="ASExtHook" />

[![License: GPL v3](https://img.shields.io/github/license/DrAbcOfficial/asexthook)](https://www.gnu.org/licenses/gpl-3.0)
[![Build](https://img.shields.io/github/actions/workflow/status/DrAbcOfficial/asexthook/build.yml?branch=main)](https://github.com/DrAbcOfficial/asexthook/actions)
[![Release](https://img.shields.io/github/v/release/DrAbcOfficial/asexthook)](https://github.com/DrAbcOfficial/asexthook/releases)
[![Download](https://img.shields.io/github/downloads/DrAbcOfficial/asexthook/total)](https://github.com/DrAbcOfficial/asexthook/releases)
[![Commit](https://img.shields.io/github/last-commit/DrAbcOfficial/asexthook)](https://github.com/DrAbcOfficial/asexthook)

`ASExtHook` is a Metamod plugin used to extend the Sven Co-op AngelScripts scripting system.

Using this plugin makes it easy to perform operations that were previously exceptionally difficult, such as hooking whether a monster is dead or not.

---

<!-- vscode-markdown-toc -->
* 1. [Install](#Install)
* 2. [Build](#Build)
* 3. [Document](#Document)
	* 3.1. [Current Expansion Feature](#CurrentExpansionFeature)
	* 3.2. [Current Expansion Objects](#CurrentExpansionObjects)
	* 3.3. [Current Expansion Methods](#CurrentExpansionMethods)
	* 3.4. [Current Expansion Hooks](#CurrentExpansionHooks)
		* 3.4.1. [EntitySpawn](#EntitySpawn)
		* 3.4.2. [IRelationship](#IRelationship)
		* 3.4.3. [MonsterSpawn](#MonsterSpawn)
		* 3.4.4. [MonsterTakeDamage](#MonsterTakeDamage)
		* 3.4.5. [MonsterKilled](#MonsterKilled)
		* 3.4.6. [MonsterTraceAttack](#MonsterTraceAttack)
		* 3.4.7. [BreakableKilled](#BreakableKilled)
		* 3.4.8. [BreakableTakeDamage](#BreakableTakeDamage)
		* 3.4.9. [BreakableTraceAttack](#BreakableTraceAttack)
		* 3.4.10. [PlayerPostTakeDamage](#PlayerPostTakeDamage)
		* 3.4.11. [PlayerTakeHealth](#PlayerTakeHealth)
		* 3.4.12. [PlayerCallMedic](#PlayerCallMedic)
		* 3.4.13. [PlayerCallGrenade](#PlayerCallGrenade)
		* 3.4.14. [PlayerUserInfoChanged](#PlayerUserInfoChanged)
		* 3.4.15. [GrappleGetMonsterType](#GrappleGetMonsterType)
		* 3.4.16. [SendScoreInfo](#SendScoreInfo)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

---

##  1. <a name='Install'></a>Install

1. Grab metamod-p and asext.dll/asext.so [Here](https://github.com/hzqst/metamod-fallguys/releases/tag/s2v1)

2. Install them.
3. Grab asexthook.dll/asexthook.so, put them into `svencoop/addons/metamod/dlls`
   1.  Grab latest version in [Action](https://github.com/DrAbcOfficial/asexthook/actions/workflows/build.yml) (Unstable, crash risk)
		
		or

   2.  Grab release version in [Release](https://github.com/DrAbcOfficial/asexthook/releases) (Stable)
4. edit `svencoop/addons/metamod/plugins.ini`
5. add 

``` ini

win32 addons/metamod/dlls/asexthook.dll
linux addons/metamod/dlls/asexthook.so

```

6. enjoy your new hook :3

---

##  2. <a name='Build'></a>Build

If you are using systems that are not covered by automatic builds (yum's and aur's) 

or want to add new hooks yourself, you can follow these steps to configure your build environment.

1. Install everything you need
   
	<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>

	1. [Git](https://git-scm.com/download/win) or `winget install --id Git.Git -e --source winget`
	2. [Visual Studio with vc143 toolset](https://visualstudio.microsoft.com/) And [C++ desktop development](https://learn.microsoft.com/en-us/cpp/ide/using-the-visual-studio-ide-for-cpp-desktop-development?view=msvc-170)

	<img src="https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white"/>

	1. `sudo apt install git make build-essential gcc gcc-multilib g++-multilib -y`

	<img src="https://img.shields.io/badge/Fedora-294172?style=for-the-badge&logo=fedora&logoColor=white"/>

	1. `sudo yum install git make gcc gcc-c++ glibc-devel.i686 libstdc++-devel.i686 -y`

	<img src="https://img.shields.io/badge/Arch_Linux-1793D1?style=for-the-badge&logo=arch-linux&logoColor=white"/>

	Sorry guys who using Arch, I've never used an Arch based distribution, you'll have to find out how to configure the dependencies yourselves!🙂

2. Clone metamod modified by hzqst
   
   `git clone https://github.com/hzqst/metamod-fallguys.git metamod`

   `cd metamod`

3. Clone this

	`git clone https://github.com/DrAbcOfficial/asexthook.git`

	`cd asexthook`

4. Build!

	<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>

	1. Open `asexthook.sln` with visual studio
	2. Press `F7`
	3. Wait and done.

	<img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black"/>

	1. `make OPT=opt install`
   
6. Grab
	
	Now you can grab your new library (asexthook.dll/asexthook.so) in 
	
	`metamod/build/addons/metamod/dlls/`

##  3. <a name='Document'></a>Document

###  3.1. <a name='CurrentExpansionProperty'></a>Current Expansion Property
 
|Class|Namespace|Object|
|---|---|---|
|CBinaryStringBuilder|\<Global\>|g_BinaryStringBuilder|

###  3.2. <a name='CurrentExpansionObjects'></a>Current Expansion Objects

```
class HealthInfo{
	CBaseEntity@ pEntity;
	float flHealth;
	int bitsDamageType;
	int health_cap;
}
```

---

###  3.3. <a name='CurrentExpansionMethods'></a>Current Expansion Methods

|Class|Method|Explian|
|---|---|---|
|CEngineFuncs|uint32 CRC32(const string& in szBuffer)|Caculate CRC32 for a string|
|---|---|---|
|CBinaryStringBuilder|void Copy(string&out buffer)|Copy output to a string|
|CBinaryStringBuilder|void SetReadBuffer(string&in buffer)|Bind a read bufferg|
|CBinaryStringBuilder|uint GetReadPointer()|Get the read pointer|
|CBinaryStringBuilder|void SetReadPointer(uint iPointer)|Set the read pointer|
|CBinaryStringBuilder|void WriteInt(int value)|Write a Value|
|CBinaryStringBuilder|void WriteLong(int64 value)|Write a Value|
|CBinaryStringBuilder|void WriteFloat(float value)|Write a Value|
|CBinaryStringBuilder|void WriteDouble(double value)|Write a Value|
|CBinaryStringBuilder|void WriteVector(Vector value)|Write a Value|
|CBinaryStringBuilder|void WriteString(string&in value)|Write a Value|
|CBinaryStringBuilder|int ReadInt()|Read a Value|
|CBinaryStringBuilder|int64 ReadLong()|Read a Value|
|CBinaryStringBuilder|float ReadFloat()|Read a Value|
|CBinaryStringBuilder|double ReadDouble()|Read a Value|
|CBinaryStringBuilder|void ReadVector(Vector&out value)|Read a Value|
|CBinaryStringBuilder|void ReadString(string&out value)|Read a Value|
|CBinaryStringBuilder|void Reset()|Reset buffer|

###  3.4. <a name='CurrentExpansionHooks'></a>Current Expansion Hooks

---

####  3.4.1. <a name='EntitySpawn'></a>EntitySpawn

```
Hooks::Entity const uint32 EntitySpawn (CBaseEntity@ pEntity)
```

Call after original CBaseEntity::Spawn called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.2. <a name='IRelationship'></a>IRelationship

```
Hooks::Entity const uint32 IRelationship (CBaseEntity@ pEntity, CBaseEntity@ pOther, bool param, int& out newValue)
```

Pre call before checking relation.

if newValue changed, will use new relationship.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.3. <a name='MonsterSpawn'></a>MonsterSpawn

```
Hooks::Monster const uint32 MonsterSpawn (CBaseMonster@ pMonster)
```

Call after who having FL_MONSTER entity CBaseEntity::Spawn called.

StopMode: CALL_ALL

MapScript | Plugin

---


####  3.4.4. <a name='MonsterTakeDamage'></a>MonsterTakeDamage

```
Hooks::Monster const uint32 MonsterTakeDamage (DamageInfo@ info)
```

Call before origin CBaseMonster::TakeDamage called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.5. <a name='MonsterKilled'></a>MonsterKilled

```
Hooks::Monster const uint32 MonsterKilled (CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib)
```

Call before origin CBaseMonster::Killed called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.6. <a name='MonsterTraceAttack'></a>MonsterTraceAttack

```
Hooks::Monster const uint32 MonsterTraceAttack (CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType)
```

Call before origin CBaseMonster::TraceAttack called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---


####  3.4.7. <a name='BreakableKilled'></a>BreakableKilled

```
Hooks::Entity const uint32 BreakableKilled (CBaseEntity@ pBreakable, entvars_t@ pevAttacker, int iGib)
```

Call before origin CBreakable::Die called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.8. <a name='BreakableTakeDamage'></a>BreakableTakeDamage

```
Hooks::Entity const uint32 BreakableTakeDamage (DamageInfo@ info)
```

Call before origin CBreakable::TakeDamage called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.9. <a name='BreakableTraceAttack'></a>BreakableTraceAttack

```
Hooks::Monster const uint32 MonsterTraceAttack (CBaseEntity@ pBreakable, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType)
```

Call before origin CBreakable::TraceAttack called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.10. <a name='PlayerPostTakeDamage'></a>PlayerPostTakeDamage

```
Hooks::Player const uint32 PlayerPostTakeDamage (DamageInfo@ info)
```

Call after origin CBasePlayer::TakeDamage called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.11. <a name='PlayerTakeHealth'></a>PlayerTakeHealth

```
Hooks::Player const uint32 PlayerTakeHealth (HealthInfo@ info)
```

Call after origin CBasePlayer::TakeHealth called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.12. <a name='PlayerCallMedic'></a>PlayerCallMedic

```
Hooks::Player const uint32 PlayerCallMedic (CBasePlayer@ pPlayer)
```

Call before "Medic!!!!"

StopMode: CALL_ALL

MapScript | Plugin


---

####  3.4.13. <a name='PlayerCallGrenade'></a>PlayerCallGrenade

```
Hooks::Player const uint32 PlayerCallGrenade (CBasePlayer@ pPlayer)
```

Call before "Take Cover!!!!"

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.14. <a name='PlayerUserInfoChanged'></a>PlayerUserInfoChanged

```
Hooks::Player const uint32 PlayerUserInfoChanged (CBasePlayer@ pClient, string szInfoBuffer, uint&out uiFlag)
```

Call before player userinfo changed (e.g: name change)

will block original call if uiFlag not 0

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.15. <a name='GrappleGetMonsterType'></a>GrappleGetMonsterType

```
Hooks::Weapon const uint32 GrappleGetMonsterType (CBaseEntity@ pThis, CBaseEntity@ pEntity, uint& out flag)
```

Pre call before Weapon Grapple checking monster type

No more hardcoded grapple, yay!

out return value:
|value|result|
|---|---|
|1|pull monster to player|
|2|pull player to monster|
|other|use default|

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.4.16. <a name='SendScoreInfo'></a>SendScoreInfo

```
Hooks::Player const uint32 SendScoreInfo (CBasePlayer@ pPlayer, edict_t@ pTarget, int iTeamID, string szTeamName, uint& out flag)
```

Pre call before sending hud info to edict

will block original call if out value not 0.

StopMode: CALL_ALL

MapScript | Plugin

---
