# BE de POO : projet Protech(t)

Protech(t) est une application de Health Monitoring qui permet de surveiller la température et la chute du patient et d'envoyer un message aux urgences si besoin. 

## Matériel nécessaire

Pour utiliser cette application, il vous suffit de posséder le matériel suivant :
- un Wemos D1 R1,
- un écran OLED 128x128 Grove Seeed,
- un accéléromètre (SEN0224 DFRobot),
- un capteur de température (101020015 Seeed Studio)
- quatre boutons,
- cinq résistance de 10k Ohms,
- une LED,
- un buzzer,
- une breadboard,
- des fils.

Le schéma de câblage se trouve dans le dossier ***Fritzing_schema***.

## Installation

Pour installer cette application, il suffit :
1. de télécharger le dossier ***Projet_health_monitoring***,
2. d'ouvrir le projet dans l'IDE Arduino,
3. d'entrer le nom de votre modem WiFi et le mot de passe dans la classe **Sms.h**,
4. de compiler,
5. de téléverser.

Il est possible que l'application ne se lance pas tout de suite après l'avoir téléversée. Il suffit juste de débrancher et rebrancher la carte Arduino de sa source de courant.

## Utilisation

Il y a quatre boutons pour contrôler l'application :
- un bouton jaune pour monter,
- un bouton vert pour sélectionner,
- un bouton bleu pour descendre,
- un bouton rouge pour allumer ou éteindre l'application.

Il faut, en tout premier, configurer l'âge du patient. 
Ensuite, l'écran de *Monitoring* apparaîtra. A partir de cet écran, plusieurs actions sont possibles :
1. appeler directement les urgences, / envoyer un SMS à un numéro configuré sur l'applet IFTTT -> génération d'un lien à mettre dans sms.h
2. aller dans les réglages (pour changer l'âge du patient),
3. en appuyant sur le bouton on/off, il est possible d'éteindre l'application (et de la rallumer en appuyant sur le même bouton).

Si plusieurs boutons sont appuyés en même temps, la priorité des actions se fait dans cet ordre: 
1. ON/OFF 
2. Sélectionner 
3. Descendre 
4. Monter 

Pendant le *Monitoring*, l'application récupère la température et l'accélération du patient. Plusieurs cas sont possibles :
1. La température monte entre 38° et 40°, une alarme sonne sans appeler les urgences (cette alarme ne peut se réactiver que 10 min après avoir été désactivée),
2. la température monte au-dessus de 40° ou descend en-dessous de 36°, une alarme sonne et appelle les urgences (cette alarme ne peut se réactiver que 10 min après avoir été désactivée),
3. le patient tombe, une alarme sonne et appelle les urgences si elle n'a pas été désactivée au bout de 15 secondes.

## Autre

### Notes

A de rares occasion, la connexion entre la carte Arduino et l'accéléromètre se perd. Si la valeur lue après "Motion sensor" est systématiquement 0 rebrancher l'accéléromètre et si besoin, téléverser à nouveau.

### Remerciements

Nous voulons remercier M. Monteil et M. Deau pour leurs encouragements et leur aide dans ce projet. 

### Autrices

Assia Nguyen et Agathe Lièvre
