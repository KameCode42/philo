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

entree terminal 5 800 200 200 7

Nombre de philosophes : 5
Temps avant de mourir : 800 millisecondes
Temps pour manger : 200 millisecondes
Temps pour dormir : 200 millisecondes
Nombre de repas avant la fin de la simulation : 7

max philo 200

exemple : 
./philo 5 800 200 200
./philo 5 800 200 200 7

nombre de philo ne peut pas etre 0
a part philo le reste peut etre a 0
aucun ne peut etre negatif

-------------------------------------------------------------------------------------------------------------

.h
include <pthread.h>

-------------------------------------------------------------------------------------------------------------

thread : 
permet d avoir plusieurs flux de controle
execute plusieurs taches simultanément
exempe : compter jusqu a 100 et ecrire hello world en meme temps

variable thread :
pthread_t thread

creer un thread :
pthread_create(&thread_1, NULL, ptr vers routine, NULL)

ptr routine = compter jusqu a 100 ou ecrire hello world

variable -> pthread_join(thread, NULL)
pthread_join : permet d attendre la fin du processus appeler
si pthread = thread 1, on attend la fin du processus thread 1

chaque thread est representer par un philo

data_race = exemple si deux philo choppe la meme fourchette c est un data race

mutex lock : permet de resoudre le probleme de data race
On peut penser à un mutex comme au verrou de la porte des toilettes. Un thread vient le verrouiller pour indiquer que les toilettes sont occupées. Les autres threads devront alors attendre patiemment que la porte soit déverrouillée avant de pouvoir accéder aux toilettes à leur tour

variable mutex :
pthread_mutex_t		mutex

Mais avant de pouvoir l’utiliser, on doit d’abord l’initialiser avec la fonction pthread_mutex_init qui a le prototype suivant :

int pthread_mutex_init(pthread_mutex_t *mutex, NULL);

Verrouiller et déverrouiller un mutex

Ensuite, pour verrouiller et déverrouiller notre mutex, il nous faudra deux autres fonctions qui ont les prototypes suivants :

int pthread_mutex_lock(pthread_mutex_t *mutex); // Verrouillage
int pthread_mutex_unlock(pthread_mutex_t *mutex); // Déverrouillage

exemple

pthread_mutex_t  *mutex_lock;

pthread_mutex_init(&mutex_lock, NULL); // IMPORTANT
pthread_mutex_lock(&mutex_lock);
// Your code here
pthread_mutex_unlock(&mutex_lock);

Détruire un mutex

Quand on n’a plus besoin d’un mutex, il nous faut le détruire avec la fonction pthread_mutex_destroy suivante :

int pthread_mutex_destroy(pthread_mutex_t *mutex);

Cette fonction détruit un mutex déverrouillé, libérant les ressources qu’il détient. Dans l’implémentation LinuxThreads des threads POSIX, aucune ressource ne peut être associé à un mutex. Dans ce cas, pthread_mutex_destroy ne fait rien si ce n’est vérifier que le mutex n’est pas verrouillé

-------------------------------------------------------------------------------------------------------------

exemple time :

void    check_philo_death(t_philo *philo)
{
    size_t current_time = get_current_time();
    
    // Vérifie si le philosophe n'a pas mangé depuis trop longtemps
    if (current_time - philo->last_meal_time > philo->time_to_die)
    {
        // Le philosophe est mort
        // ...
    }
}

void    philo_eat(t_philo *philo)
{
    // Le philosophe commence à manger
    philo->last_meal_time = get_current_time();
    
    // Simule le temps du repas
    ft_usleep(philo->time_to_eat);
}

-------------------------------------------------------------------------------------------------------------