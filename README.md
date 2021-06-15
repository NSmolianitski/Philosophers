# Philosophers 🤔
Philosophers is a project about multithreading that suggests to solve a task about [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Main principle
Philosophers sit around the table. Every philosopher has a bowl of spaghetti. Their life cycle is: eating => sleeping => thinking.

There are as many forks as philosophers. A philosopher needs two forks to eat. If he doesn't eat for specified time, he will die and simulation will stop.

Philosophers don't talk to each other.

Program receives 4 or 5 arguments:
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat (optional)

## Content description
The project consists of three similar programs. But every program has it's own features:

Philo_one:
- each philosopher is a thread
- each fork is a mutex
- one fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher

Philo_two:
- each philosopher is a thread
- forks represented as a semaphore
- all the forks are in the middle of the table

Philo_three:
- each philosopher is a process (main process is not a philosopher)
- forks represented as a semaphore
- all the forks are in the middle of the table

## My solution
I decided to implement a waiter that checks every philosopher for starving, 
grants permission to take forks and checks deaths to stop the simulation.

## What I learned
- threads and processes interaction
- starvation, deadlock, data racing, race condition principles
- mutex and semaphore principles
