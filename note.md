Philosophers :

Regles globales :
- les variables globales sont interdites.
- vos programmes doivent prendre les arguments suivants :

	- nombre-de-philosophes : Le nombre de philosophes et, par conséquent, le nombre de fourchettes.
	- temps-à-mourir (en millisecondes) : Si un philosophe n'a pas commencé à manger dans les temps-à-mourir millisecondes écoulées depuis le début de son dernier repas ou depuis le début de la simulation, il meurt.
	- temps-à-manger (en millisecondes) : Le temps qu'il faut à un philosophe pour manger.
	Pendant ce temps, il devra tenir deux fourchettes.
	- temps-à-dormir (en millisecondes) : Le temps qu'un philosophe passe à dormir.
	- nombre-de-repas (argument optionnel) : Si tous les philosophes ont mangé au moins nombre-de-repas fois, la simulation s'arrête.
	Sinon, la simulation s'arrête lorsqu'un philosophe meurt.

- chaque philosophe se voit attribuer un numéro allant de 1 à nombre-de-philosophes.
- le philosophe numéro 1 est assis à côté du philosophe numéro nombre-de-philosophes.
- tout autre philosophe, numéro N, est assis entre le philosophe numéro N - 1 et le philosophe numéro N + 1.

Tout changement d'état d'un philosophe doit être formaté comme suit :

	[timestamp en ms] X a pris une fourchette
	[timestamp en ms] X mange
	[timestamp en ms] X dort
	[timestamp en ms] X pense
	[timestamp en ms] X meurt

Remplacez timestamp en ms par l'horodatage actuel en millisecondes et X par le numéro du philosophe.

-------------------------------------------------------------------------------------------------------------

.h
include <pthread.h>

-------------------------------------------------------------------------------------------------------------

thread : 
permet d avoir plusieurs flux de controle
execute plusieurs taches simultanément
exempe : compter jusqu a 100 et ecrire hello world en meme temps

variable thread :
pthread_t thread_1

creer un thread :
pthread_create(&thread_1, NULL, ptr vers routine, NULL)

ptr routine = compter jusqu a 100 ou ecrire hello world

pthread_join : permet d attendre la fin du processus appeler
si pthread = thread 1, on attend la fin du processus thread 1

chaque thread est representer par un philo

data_race = exemple si deux philo choppe la meme fourchette c est un data race


mutex lock : permet de resoudre le probleme de data race
variable mutex :
pthread_mutex_t *a