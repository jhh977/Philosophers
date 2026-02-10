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


## Resources

Codevault videos for a great introduction to what is mutex, what is a race condition, and how to avoid it:
What are Race conditions? https://www.youtube.com/watch?v=FY9livorrJI&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=3&pp=iAQB
What is a mutex in C? https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4&pp=iAQB

Dean Ruina's blog on Medium for a great explanation of the project:
https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

Additionally I relied on the AI to better explain specific details regarding threads and multithreading, get a better general idea of the project, and understand the external functions for this project as well as where can I use them to get the best result.