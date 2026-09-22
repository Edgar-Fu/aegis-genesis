# Aegis Genesis — Radar Collision Avoidance

**Human-Governed Decision Architecture for Safer Autonomous Space Traffic**

Aegis Genesis is a simplified engineering demonstrator that connects relative-motion calculations, an illustrative collision-risk proxy, explicit human-review thresholds, executable C++17, and boundary testing in one traceable workflow.

> **Core principle:** AI can calculate and recommend, but human authority remains responsible for irreversible action.

## Poster

[**View the Robotics & AI Discovery Day 2026 poster (PDF)**](docs/Aegis_Genesis_Robotics_AI_Discovery_Day_2026_Poster.pdf)

The poster was prepared for the **Robotics & AI Discovery Day 2026 Student Research Poster Session**.

## What the code implements

The repository contains the complete `aegis_genesis.cpp` source used by the poster. It implements:

- closest-approach time (`timeToCPA`)
- minimum separation (`distanceAtCPA`)
- an illustrative collision-risk proxy (`collisionProxy`)
- a composite risk score (`compositeRisk`)
- the human-review trigger (`humanReviewRequired`)
- 10 normal, threshold, edge, and invalid-input verification cases
- a deliberate fault-injection path used to show how a sign error changes the result

The source file SHA-256 is:

```text
ee20c87d65b9fd3915ee7ef8997c2d116078e1466746c584cc988df7511d9355
```

This matches the SHA-256 printed on the poster.

## Build and run

### Linux / WSL / macOS with g++

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror src/aegis_genesis.cpp -o aegis_genesis
./aegis_genesis
```

Expected summary:

```text
Tests: 10/10 passed
```

### Fault-injection demonstration

```bash
./aegis_genesis --demonstrate-bug
```

Expected output:

```text
WRONG t_CPA = -100.000000000000 s
WRONG separation = 2.025438224188 NM
```

## Verified nominal result

For the poster's supplied training example:

- `t_CPA = 100.0 s`
- `d_min = 0.320 NM`
- `P_c = 0.903` (dimensionless illustrative proxy, **not** a measured 90.3% collision probability)
- `R = 0.822`
- `H = 1`, meaning human review is required

`H = 1` does **not** authorize an autonomous maneuver. It routes the case to human-governed review.

## Repository structure

```text
aegis-genesis/
├── README.md
├── .gitignore
├── src/
│   └── aegis_genesis.cpp
├── docs/
│   └── Aegis_Genesis_Robotics_AI_Discovery_Day_2026_Poster.pdf
└── results/
    ├── verification_output.txt
    └── fault_injection_output.txt
```

## Scope and limitations

Aegis Genesis is an **academic engineering demonstrator**, not an operational spacecraft collision-avoidance system.

The current implementation:

- uses a simplified 2D constant-relative-velocity model
- uses supplied relative-position and relative-velocity inputs
- uses an illustrative risk proxy rather than an operational collision-probability model
- does not ingest real space-situational-awareness data
- does not implement physical radar hardware
- does not generate or optimize real maneuver plans
- does not implement operational spacecraft control
- validates the numerical calculations and review logic, not operational flight performance

Future work described on the poster includes realistic 3D orbital propagation, covariance-based collision probability, real SSA / multi-object tracking, human-governed maneuver optimization, authorization enforcement, logs, and replay.

## Author

**Edgar Fu**  
Pittsburgh, Pennsylvania  
[LinkedIn](https://www.linkedin.com/in/edgar-fu/)  
[GitHub](https://github.com/Edgar-Fu)
