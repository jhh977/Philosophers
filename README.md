# Philosophers

*This project has been created as part of the 42 curriculum by jhijazi*

## Description:

This project is an introduction to multithreading and process synchronization in C. It implements the classic Dining Philosophers problem, where multiple philosophers sit at a round table, alternating between thinking, eating, and sleeping. The challenge is to prevent philosophers from starving while avoiding deadlocks and data races.

Each philosopher is represented by a thread, and forks (resources) are represented by mutexes. The program demonstrates concurrency control using mutexes and careful timing to ensure that no philosopher dies from starvation.

## Instructions

### Clone the repository

### Compile the program

make        # Creates executable named "philo"
make clean  # Removes object files
make fclean # Removes object files AND executable
make re     # Recompiles everything

### Run the executable

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_times_each_philosopher_must_eat]
