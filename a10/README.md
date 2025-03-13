# DIY Cockpit pour A10C et A10C-II

**WIP (Work in Progress)**

Cockpit DIY pour les modules **A-10C** et **A-10C-II** de **DCS World**.

Utilise [DCS-BIOS Fork](https://github.com/DCS-Skunkworks/dcs-bios).

---

## Fonctionnalités :

- **Up Front Controller (UFC)**
- **Landing Gear and Flap Control Panel** (Panneau de contrôle des trains d'atterrissage et des volets)
- **Armament HUD Control Panel (AHCP)** (Panneau de contrôle de l'armement et du HUD)
- **Gun and Nose Wheel Steering (NWS) Lights** (Lumière du canon et du braquage de la roue avant)
- **Horizontal Situation Indicator (HSI)** (Indicateur de situation horizontale)
- **Navigation Mode Select Panel (NMSP)** (Panneau de sélection du mode de navigation)
- **Engine Monitoring Instruments (gauges)** (Instruments de surveillance des moteurs)
- **Fuel System Control Panel** (Panneau de contrôle du système de carburant)
- **Throttles Panel** (Panneau des manettes des gaz)
- **LASTE Control Panel** (Panneau de contrôle LASTE)
- **Radio Control Panel**, incluant :
    - ARC-210
    - AN/ARC-186
    - AN/ARC-164
    - **Intercom Control Panel** (Panneau de contrôle de l'intercom)
    - **TACAN Operation and Control Panel** (Panneau de contrôle et d'opération TACAN)
    - **ILS Control Panel and ILS Operation** (Panneau de contrôle ILS et opérations ILS)
    - **Night Vision Goggles (NVG)** (Lunettes de vision nocturne)
    - **Fuel Quantity** (Quantité de carburant)
- **Emergency Brake System** (Système de freinage d'urgence)
- **Auxiliary Lighting Control Panel** (Panneau de contrôle de l'éclairage auxiliaire)
- **Stability Augmentation System (SAS) Panel** (Panneau du système d'augmentation de la stabilité)
- **Electrical Power Panel** (Panneau d'alimentation électrique)
- **Countermeasures Signal Processor (CMSP) Panel** (Panneau du processeur de signaux de contre-mesures)
- **Light Control Panel** (Panneau de contrôle des lumières)
- **Caution Light Panel** (Panneau des voyants d'avertissement)
- **Auxiliary Avionics Panel (AAP)** (Panneau d'avionique auxiliaire)
- **Control Display Unit (CDU) and Pages** (Unité d'affichage de contrôle et pages)

---

## Master Controller

Fonctionne sous **Pro Micro**. Communique avec le PC comme un contrôleur de jeu avec **128 boutons** et **multi-axes**.

Communique avec chaque module (**Arduino** et **ESP32**) via un bus **I2C**.


## Overview
![plot](./overview.jpg)
