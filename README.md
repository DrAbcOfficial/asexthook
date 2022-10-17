# ASExtHook [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) <img align="right" src="./img/logo.png" alt="ASExtHook" />


# A metamod Plugin to extend the Sven Co-op Hook

## Current Expansion Hook

---

### MonsterTakeDamage

```
Hooks::Monster const uint32 MonsterTakedamage (CBaseMonster@ pMonster, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType)
```

Call after origin CBaseMonster::TakeDamage called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

### MonsterKilled

```
Hooks::Monster const uint32 MonsterKilled (CBaseMonster@ pMonster, entvars_t@ pevAttacker, int iGib)
```

Call after origin CBaseMonster::Killed called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---

### MonsterTraceAttack

```
Hooks::Monster const uint32 MonsterTraceAttack (CBaseMonster@ pMonster, entvars_t@ pevAttacker, float flDamage, const TraceResult& in ptr, int bitDamageType)
```

Call after origin CBaseMonster::TraceAttack called.

Notice that player died will call this hook, because player is monster too.

StopMode: CALL_ALL

MapScript | Plugin

---


### BreakableDie

```
Hooks::Entity const uint32 BreakableDie (CBaseEntity@ pBreakable)
```

Call after origin CBreakable::Die called.

NOT IMPLEMENT YET

StopMode: CALL_ALL

MapScript | Plugin

---

### BreakableTakeDamage

```
Hooks::Entity const uint32 BreakableTakeDamage (CBaseEntity@ pBreakable, entvars_t@ pevInflictor, float flDamage, int bitDamageType)
```

Call after origin CBreakable::TakeDamage called.

NOT IMPLEMENT YET

StopMode: CALL_ALL

MapScript | Plugin

---