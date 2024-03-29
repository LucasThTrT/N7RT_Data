# Description

Le système de communication CAN (Controller Area Network) est un protocole robuste utilisé dans les systèmes embarqués pour permettre la transmission fiable de données entre plusieurs nœuds. Il offre une communication bidirectionnelle à haut débit, idéale pour les environnements industriels et automobiles, où la fiabilité et la résistance aux interférences électromagnétiques sont essentielles. Le CAN est largement utilisé dans les applications nécessitant une communication en temps réel entre capteurs, actionneurs et autres composants électroniques.

# Matériel

Pour assurer la communication des CAN bus, nous avons utiliser le  Arduino MCP2515 qui va s'occuper de toute la partie communication CAN.
En effet, cette carte va jouer le rôle de transmetteur/recepteur mais va aussi s'occuper de détecter les collisions des Bus et de pouvoir renvoyer les messages.

On a ainsi : 

- CAN V2.0B : jusqu'à 1Mb/s (donc HS-CAN)
- Interface SPI : jusqu'à 10MHz

# Structure du BUS

can_id : 32 bits (uint32_t) -> Identifiant de la trame
can_dlc : 8 bits (uint8_t)  -> Longueur de la trame 
data[0..7]: 8 bits          -> Informations de la trame

# Ressources

Librairie Arduino du MCP2515
[autowp(Dmitry)](https://github.com/autowp/arduino-mcp2515)