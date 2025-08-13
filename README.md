

# Sujet :
Ce projet implémente le problème des philosophes (Dining Philosophers Problem) en C, en utilisant pthread pour gérer le multithreading et mutex pour éviter les accès concurrents aux ressources partagées (les fourchettes).

L’objectif est de simuler un groupe de philosophes assis autour d’une table.

Chaque philosophe :
- Pense
- Prend deux fourchettes
- Mange
- Dort
- Recommence

- Si un philosophe reste trop longtemps sans manger, il meurt et la simulation s’arrête.
- Si un nombre de repas précis est atteint pour tous les philosophes, la simulation se termine également.

# Règles :
- Nombre de philosophes (> 1 ou <= 200)
- Temps à mourir (ms ≥ 0) :  Temps maximal qu’un philosophe peut passer sans manger avant de mourir.
- Temps à manger (ms ≥ 0) :  Temps nécessaire pour manger.
- Temps à dormir (ms ≥ 0) : Temps passé à dormir.
- Nombre de repas (optionel): Nombre de repas que chaque philosophe doit manger pour que la simulation s’arrête.
- Le philosophe 1 est assis entre le dernier et le deuxième philosophe.
- Chaque philosophe a une fourchette à sa gauche et à sa droite.
- Les ressources (fourchettes) sont protégées par des mutex pour éviter les data races.
<br>
# Fonctionnement :
Threads :
- Chaque philosophe est représenté par un thread (pthread_create).
- Le thread gère les cycles penser → prendre fourchettes → manger → dormir.

Mutex :
- Chaque fourchette est représentée par un mutex (pthread_mutex_t).
- Avant de manger, un philosophe verrouille (pthread_mutex_lock) ses deux fourchettes.
- Après avoir mangé, il déverrouille (pthread_mutex_unlock) ses fourchettes.

Gestion du temps et de la mort :
- Chaque philosophe enregistre le moment de son dernier repas (last_meal_time).
- Un thread de surveillance vérifie régulièrement si un philosophe dépasse temps-à-mourir.
- Si c’est le cas → message "X meurt" et fin de la simulation.

Fonctions clés :
- pthread_create : créer un thread
- pthread_join : attendre la fin d’un thread
- pthread_mutex_init / lock / unlock / destroy : gestion des verrous
- gettimeofday ou équivalent : mesurer le temps en millisecondes
- usleep : pause en microsecondes (converti depuis ms)
<br>
# Exemple d’exécution :
./philo 5 800 200 200 7

Interprétation :
- 5 philosophes
- Ils meurent s’ils restent 800 ms sans manger
- Ils mettent 200 ms pour manger
- Ils dorment 200 ms après chaque repas
- La simulation s’arrête quand chacun a mangé 7 fois
