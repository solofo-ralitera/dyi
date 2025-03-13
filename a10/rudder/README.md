# Module pour transformer un pédalier Logitech G27 en palonier pour DCS World A-10C

## Description
Ce module consiste à transformer un pédalier de volant Logitech G27 en un rudder (palonnier) fonctionnel pour le simulateur de vol **DCS World**, spécifiquement pour le module **A-10C Warthog**. L'objectif est de réutiliser le pédalier du G27, initialement conçu pour les jeux de course, afin de contrôler les axes de direction (rudder) et de frein dans un simulateur de vol.


## Fonctionnalités
- **Transformation du pédalier G27** : Utilisation des pédales d'accélérateur, d'embrayage et de frein pour contrôler les axes de direction et de freinage.
- **Compatibilité** : Intégration parfaite avec **DCS World** et le module **A-10C Warthog**.
- **Plug-and-play** : Le module se connecte directement à votre PC via USB et est reconnu comme un joystick multi-axes.
- Le module peut être adapté pour d'autres simulateurs de vol ou jeux compatibles avec les périphériques joystick.


## Composition du module
Le module est composé des éléments suivants :
- **Arduino Pro Micro** : Pour gérer la conversion des signaux du pédalier en entrées USB.
- **Connecteur DB9** : Permet de connecter le pédalier G27 à l'Arduino.
- **Firmware personnalisé** : Transforme l'Arduino en un périphérique de type joystick multi-axes.


## Fonctionnement
- **Accélérateur et embrayage** : Ces pédales sont utilisées pour contrôler le **palonnier gauche et droit** (axe de direction).
- **Frein** : La pédale de frein agit comme un **frein de roue** lorsque l'avion est au sol.


