# `ASExtHook`: Plugin to extend Sven Co-op script <img align="right" src="./img/logo.png" width="140" height="140" alt="ASExtHook" />

[![License: GPL v3](https://img.shields.io/github/license/DrAbcOfficial/asexthook)](https://www.gnu.org/licenses/gpl-3.0)
[![Build](https://img.shields.io/github/workflow/status/DrAbcOfficial/asexthook/Build)](https://github.com/DrAbcOfficial/asexthook/actions)
[![Release](https://img.shields.io/github/v/release/DrAbcOfficial/asexthook)](https://github.com/DrAbcOfficial/asexthook/releases)
[![Download](https://img.shields.io/github/downloads/DrAbcOfficial/asexthook/total)](https://github.com/DrAbcOfficial/asexthook/releases)
[![Commit](https://img.shields.io/github/last-commit/DrAbcOfficial/asexthook)](https://github.com/DrAbcOfficial/asexthook)

`ASExtHook` is a Metamod plugin used to extend the Sven Co-op AngelScripts scripting system.

Using this plugin makes it easy to perform operations that were previously exceptionally difficult, such as hooking whether a monster is dead or not.
<!-- vscode-markdown-toc -->
* 1. [Install](#Install)
* 2. [Build](#Build)
* 3. [Document](#Document)
	* 3.1. [Current Expansion Objects](#CurrentExpansionObjects)
	* 3.2. [Current Expansion Methods](#CurrentExpansionMethods)
	* 3.3. [Current Expansion Hooks](#CurrentExpansionHooks)
		* 3.3.1. [MonsterTakeDamage](#MonsterTakeDamage)
		* 3.3.2. [MonsterKilled](#MonsterKilled)
		* 3.3.3. [MonsterTraceAttack](#MonsterTraceAttack)
		* 3.3.4. [BreakableKilled](#BreakableKilled)
		* 3.3.5. [BreakableTakeDamage](#BreakableTakeDamage)
		* 3.3.6. [BreakableTraceAttack](#BreakableTraceAttack)
		* 3.3.7. [PlayerPostTakeDamage](#PlayerPostTakeDamage)
		* 3.3.8. [PlayerTakeHealth](#PlayerTakeHealth)
		* 3.3.9. [PlayerCallMedic](#PlayerCallMedic)
		* 3.3.10. [PlayerCallGrenade](#PlayerCallGrenade)
		* 3.3.11. [GrappleGetMonsterType](#GrappleGetMonsterType)
		* 3.3.12. [SendScoreInfo](#SendScoreInfo)
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

	Sorry guys who using Arch, I've never used an Arch based distribution, you'll have to find out how to configure the dependencies yourselves!????

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

###  3.1. <a name='CurrentExpansionObjects'></a>Current Expansion Objects

```
class HealthInfo{
	CBaseEntity@ pEntity;
	float flHealth;
	int bitsDamageType;
	int health_cap;
}
```

---

###  3.2. <a name='CurrentExpansionMethods'></a>Current Expansion Methods

|Class|Method|Explian|
|---|---|---|
|CEngineFuncs|uint32 CRC32(const string& in szBuffer)|Caculate CRC32 for a string|

###  3.3. <a name='CurrentExpansionHooks'></a>Current Expansion Hooks

---

####  3.3.1. <a name='MonsterTakeDamage'></a>MonsterTakeDamage

```
Hooks::Monster const uint32 MonsterTakeDamage (DamageInfo@ info)
```

Call before origin CBaseMonster::TakeDamage called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.2. <a name='MonsterKilled'></a>MonsterKilled

```
Hooks::Monster const uint32 MonsterKilled (CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib)
```

Call before origin CBaseMonster::Killed called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.3. <a name='MonsterTraceAttack'></a>MonsterTraceAttack

```
Hooks::Monster const uint32 MonsterTraceAttack (CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType)
```

Call before origin CBaseMonster::TraceAttack called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---


####  3.3.4. <a name='BreakableKilled'></a>BreakableKilled

```
Hooks::Entity const uint32 BreakableKilled (CBaseEntity@ pBreakable, entvars_t@ pevAttacker, int iGib)
```

Call before origin CBreakable::Die called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.5. <a name='BreakableTakeDamage'></a>BreakableTakeDamage

```
Hooks::Entity const uint32 BreakableTakeDamage (DamageInfo@ info)
```

Call before origin CBreakable::TakeDamage called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.6. <a name='BreakableTraceAttack'></a>BreakableTraceAttack

```
Hooks::Monster const uint32 MonsterTraceAttack (CBaseEntity@ pBreakable, entvars_t@ pevAttacker, float flDamage, Vector vecDir, const TraceResult& in ptr, int bitDamageType)
```

Call before origin CBreakable::TraceAttack called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.7. <a name='PlayerPostTakeDamage'></a>PlayerPostTakeDamage

```
Hooks::Player const uint32 PlayerPostTakeDamage (DamageInfo@ info)
```

Call after origin CBasePlayer::TakeDamage called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.8. <a name='PlayerTakeHealth'></a>PlayerTakeHealth

```
Hooks::Player const uint32 PlayerTakeHealth (HealthInfo@ info)
```

Call after origin CBasePlayer::TakeHealth called.

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.9. <a name='PlayerCallMedic'></a>PlayerCallMedic

```
Hooks::Player const uint32 PlayerCallMedic (CBasePlayer@ pPlayer)
```

Call before "Medic!!!!"

StopMode: CALL_ALL

MapScript | Plugin


---

####  3.3.10. <a name='PlayerCallGrenade'></a>PlayerCallGrenade

```
Hooks::Player const uint32 PlayerCallGrenade (CBasePlayer@ pPlayer)
```

Call before "Take Cover!!!!"

StopMode: CALL_ALL

MapScript | Plugin

---

####  3.3.11. <a name='GrappleGetMonsterType'></a>GrappleGetMonsterType

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

####  3.3.12. <a name='SendScoreInfo'></a>SendScoreInfo

```
Hooks::Player const uint32 SendScoreInfo (CBasePlayer@ pPlayer, edict_t@ pTarget, int iTeamID, string szTeamName, uint& out flag)
```

Pre call before sending hud info to edict

will block original call if out value not 0.

StopMode: CALL_ALL

MapScript | Plugin

---
