# Présentation

Le pôle DATA a la responsabilité de mettre en place le système embarqué de la monoplace, ce qui implique la collecte de toutes les informations externes, telles que les données des capteurs de chaleur des pneumatiques et les commandes d'accélération du moteur, afin de fournir une réponse adaptée à l'environnement de la voiture.

Concrètement, lorsque le pilote demande d'accélérer mais que les roues patinent, le système de contrôle moteur ajuste cette demande pour éviter les pertes de contrôle, comme le tête-à-queue. Cela nécessite une analyse en temps réel des données des capteurs et une réaction rapide pour assurer la sécurité et les performances optimales de la monoplace.



## Choix de la communication : CAN BUS

Pour réaliser une communication entre les différentes unités, nous avons décidé d'utiliser le bus de données CAN (Controller Area Network) donc avec une méthode CSMA/CD.
Pour plus d'information voir le [lien de igm-univ](https://www-igm.univ-mlv.fr/~dr/XPOSE2009/BusCAN/index.html).

Ce choix s'explique par sa simplicité d'utilisation ainsi que son utilisation majeur dans le monde de l'automobile d'aujourd'hui.

#### Se rendre sur le dossier ./CAN_BUS pour voir notre travail et plus d'explications.




# Avancés

# A Faire