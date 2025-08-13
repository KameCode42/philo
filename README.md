

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

