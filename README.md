# ASExtHook [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) <img align="right" src="./img/logo.png" alt="ASExtHook" />


# A metamod Plugin to extend the Sven Co-op Hook

## Current Expansion Hook

---

### MonsterTakeDamage

```
Hooks::Entity const uint32 MonsterTakedamage (CBaseMonster@ pMonster, entvars_t@ pevAttacker, entvars_t@ pevInflictor, float flDamage, int bitDamageType)
```

Call after origin CBaseMonster::TakeDamage called.

StopMode: CALL_ALL

MapScript | Plugin

---