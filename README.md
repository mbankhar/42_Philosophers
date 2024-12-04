# Dining Philosophers Simulation

This project implements a simulation of the classic **Dining Philosophers Problem** using multithreading in C. The philosophers follow a cycle of thinking, eating, and sleeping, using mutexes to manage access to shared resources (forks).

## Features

- Handles synchronization using **pthread mutexes**.
- Simulates philosophers' behaviors: **thinking**, **eating**, and **sleeping**.
- Supports user-defined parameters for:
  - Number of philosophers.
  - Time to die.
  - Time to eat.
  - Time to sleep.
  - Number of cycles for each philosopher.

## Files

### Core Source Files

- **`philo.c`**: Contains the main function and handles the overall flow of the simulation.
- **`init.c`**: Initializes philosophers and threads.
- **`pars_and_error.c`**: Parses arguments and validates input.
- **`philo_utils.c`**: Utility functions for time handling and error management.
- **`routines.c`**: Defines the behaviors (thinking, eating, and sleeping) of the philosophers.

### Header File

- **`philo.h`**: Contains global includes, type definitions, and function prototypes.

### Makefile

- Compile the project with a simple `make` command.

## Usage

### Compilation

To compile the project, run:

```bash
make
```

This will generate an executable named `philo`.

### Running the Program

Execute the program with the following arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_cycles]
```

- `<number_of_philosophers>`: Total number of philosophers.
- `<time_to_die>`: Time (in milliseconds) a philosopher can live without eating.
- `<time_to_eat>`: Time (in milliseconds) a philosopher spends eating.
- `<time_to_sleep>`: Time (in milliseconds) a philosopher spends sleeping.
- `[number_of_cycles]` (optional): Number of times each philosopher must eat. If not provided, the simulation runs indefinitely.

### Example

```bash
./philo 5 800 200 200 3
```

Simulates 5 philosophers, each needing to eat within 800ms, taking 200ms to eat and 200ms to sleep, with a total of 3 cycles.

## Notes

- Handles cases where:
  - Only one philosopher is present.
  - Invalid or missing arguments.
  - Philosophers die due to starvation.
- Ensures all philosophers' actions are synchronized without deadlocks.

## Limitations

- Maximum number of philosophers is defined by `PHILO_MAX` in `philo.h`.
- Requires `pthread` library support.

## License

This project is open-source and can be modified or redistributed under the terms of the MIT License.
