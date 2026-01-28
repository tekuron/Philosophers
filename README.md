# Philosophers
![Language](https://img.shields.io/badge/Language-C-blue)
![Score](https://img.shields.io/badge/Score-125%2F100-brightgreen)

<p>Simulation of the classic Dining Philosophers problem. The project focuses on the basics of threading, process forking, and using mutexes and semaphores to prevent data races and deadlocks.</p>

---

## Table of Contents
- [Overview](#overview)
- [Arguments](#arguments)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)
- [Author](#author)

---

## Overview
n philosophers sit at a round table with a bowl of spaghetti. There are as many forks as there are philosophers. They alternate between eating, sleeping, and thinking. For a philosopher to eat, they must hold two forks simultaneously.



## Arguments
The program is executed with the following arguments:

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers and also the number of forks. |
| `time_to_die` | (in ms) If a philosopher doesn't start eating 'time_to_die' milliseconds after the start of their last meal or the start of the simulation, they die. |
| `time_to_eat` | (in ms) The time it takes for a philosopher to eat. During this time, they will hold two forks. |
| `time_to_sleep` | (in ms) The time a philosopher will spend sleeping. |
| `[number_of_times_each_philosopher_must_eat]` | (Optional) If all philosophers have eaten at least 'number_of_times_each_philosopher_must_eat' times, the simulation stops. If not specified, the simulation stops when a philosopher dies. |

## Mandatory Part
In this part, each philosopher has a fork to their left and a fork to their right. The philosophers are represented by **threads**, and the forks are represented by **mutex locks**.

Mutexes are also used to protect print actions and to check the last meal timestamp, preventing data races between threads. The main process monitors the philosophers to detect if anyone has died or if the simulation should end.

## Bonus Part
In the bonus part, each philosopher is their own **process**, and the forks are placed in the middle of the table.

Since the number of forks is a shared resource across processes, it is represented by a **semaphore**. The semaphore is initialized with the value *n*. Philosophers `wait` to take forks and `post` to return them. A separate thread is used within each philosopher process to monitor for death. A semaphore is also used here to prevent data races between the philosopher process and its monitoring thread.

## Author
- **Name:** Daniel Zamora
- **GitHub:** [tekuron](https://github.com/tekuron)
- **42 Intra:** [danzamor](https://profile-v3.intra.42.fr/users/danzamor)
- **School:** 42
