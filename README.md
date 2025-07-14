 
<div align="center">
<h1>Dinning Philosophers</h1>
	
<a href="https://github.com/bental77a/philosophers">![42 Badge](https://github.com/mcombeau/mcombeau/blob/main/42_badges/philosophersm.png)</a>

</div>
<label>
	<h2> Score </h2>	
	<img alt="100" style="width: 100px;height: 70px" src="https://github.com/simon-zerisenay/simon-zerisenay/blob/main/100.png"/>
</label> 
<h2>Introduction</h2>
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/simon-zerisenay/42_Philosophers?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/simon-zerisenay/42_Philosophers?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/simon-zerisenay/42_Philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/simon-zerisenay/42_Philosophers?color=blue" /> 
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/simon-zerisenay/42_Philosophers?color=green" />
</p>  
Welcome to the Dining Problem project! This project is part of the curriculum at 42 and focuses on solving the classic dining problem using threads and synchronization techniques. The dining problem is a fundamental synchronization challenge in computer science that illustrates resource sharing and deadlock avoidance.

## Objective
The main objective of this project is to design a program that simulates the dining problem, where a certain number of entities sit around a table with a shared set of resources. The entities alternate between thinking and consuming, but to consume, they must acquire two adjacent resources. The challenge is to ensure that each entity can successfully consume without causing a deadlock or starvation.

## Features

### Program Design
The project involves designing a program that simulates the dining problem. The key features include:

### Entities
The program represents entities as individual threads, each responsible for alternating between thinking and consuming states.

### Resources
The resources are shared objects used by the entities to consume. Each entity needs two adjacent resources to enter the consuming state.

### Synchronization
The program must implement synchronization mechanisms to ensure that entities can access resources without causing conflicts or deadlocks. Techniques such as mutexes, semaphores, or other synchronization primitives can be used.

## The Dining Problem

The dining problem is a classic synchronization challenge in computer science that highlights difficulties related to resource sharing and deadlock avoidance. It describes a scenario where a group of entities is seated around a table and alternates between thinking and consuming. The entities share a set of resources placed between them on the table.

The problem arises when each entity requires two adjacent resources to consume. If an entity picks up one resource and waits for the adjacent resource to become available, it can lead to a deadlock situation. Deadlock occurs when each entity is holding one resource and waiting indefinitely for the adjacent resource, resulting in a state where no entity can proceed.

The dining problem aims to find a solution that allows all entities to consume without deadlocks or starvation. Several strategies can be employed to address this problem:

### Resource Sharing
Each resource can be considered a shared object, and entities must properly allocate and release resources to avoid conflicts. For example, entities can be assigned a unique identifier and required to pick up the lower-indexed resource first, minimizing the possibility of circular dependencies.

### Deadlock Avoidance
Implementing a protocol to prevent deadlock is essential. One common approach is to use a limit on the number of entities allowed to pick up resources simultaneously. By limiting the number of entities, it ensures that at least one entity can consume without waiting indefinitely.

### Synchronization Mechanisms
Various synchronization techniques can be used to ensure proper resource sharing. Mutexes or semaphores can be employed to protect critical sections where entities access resources. These mechanisms help enforce mutual exclusion, allowing only one entity to hold a resource at a time.

### Fairness
Ensuring fairness is crucial to prevent starvation, where an entity is unable to consume due to other entities continuously acquiring the required resources. Techniques like a coordinator or arbiter can be introduced to control access to the resources, ensuring that each entity gets a fair chance to consume.

Solving the dining problem requires finding a balance between resource sharing, synchronization, and avoiding deadlocks or starvation. It is a fundamental problem in concurrent programming, highlighting the complexities of coordinating shared resources among multiple processes or threads.

By studying and implementing solutions to the dining problem, programmers gain insights into critical synchronization concepts and techniques that are essential in developing robust and efficient concurrent systems.

## Installation and Usage

To install and run the Dining Problem project, follow these steps:

1. Clone the project repository:
   ```bash
   git clone https://github.com/your_username/42-dining-problem.git
   ```

2. Navigate to the project directory:
   ```bash
   cd 42-dining-problem
   ```

3. Compile the project using the provided Makefile:
   ```bash
   make
   ```

4. Run the program with the desired parameters:
   ```bash
   ./program <number_of_entities> <time_to_die> <time_to_consume> <time_to_think> [number_of_times_each_entity_must_consume]
   ```

Ensure that you have the necessary libraries and dependencies installed on your system. The project's repository may provide further instructions on any additional requirements.

## Testing

To test the Dining Problem project and evaluate its functionality, follow these steps:

1. Run the program with different configurations, including various numbers of entities and different time constraints.
2. Observe the behavior of the entities and verify that they alternate between thinking and consuming.
3. Monitor the synchronization mechanisms to ensure that entities share the resources properly and avoid deadlock.
4. Test the program with edge cases, such as a single entity or a large number of entities, to validate its robustness and performance.
5. Measure the program's resource utilization and efficiency to ensure optimal performance.

By conducting thorough testing, you can ensure the correctness and effectiveness of your implementation of the dining problem.

## Parameters

- `number_of_entities`: The number of entities participating in the simulation
- `time_to_die`: Maximum time an entity can go without consuming before terminating
- `time_to_consume`: Time required for an entity to complete the consuming process
- `time_to_think`: Time spent by an entity in the thinking state
- `number_of_times_each_entity_must_consume` (optional): Condition where each entity must consume a certain number of times before the program terminates
