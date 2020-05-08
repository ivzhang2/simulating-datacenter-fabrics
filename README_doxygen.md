# Simulation of datacenter fabrics {#mainpage}

Collaborators: Muhammad Tirmazi, Ivan Zhang, Erik Johnson, Jessica Wijaya

============

## 1. Overview

### 1.1. Background 

Cloud vendors, including Amazon AWS, Microsoft Azure and Google Cloud, make their datacenter network accessible for clients by abstract out the complexities of the underlying interconnect. For the client, the datacenter network is one large fabric that (somewhat magically) connects all of their rented instances. To the client, the data center fabric is a black box providing the illusion of a large uniform interconnect where each instance is connected directly to every
other instance in a mesh or “fabric”. In reality, things are not as simple.

An actual datacenter fabric, however, looks much more like the figure below. The process
of designing and deploying a datacenter fabric, and its accompanying network
stack, costs upwards of a billion dollars. Hence, computer scientists evaluate a
potential design’s performance using a network simulator prior to deploying it
in an actual datacenter.

<img src="fattree.png" alt="Figure 1" width="500"/>

### 1.2. Problem Statement

Network simulators are traditionally serial. To get an intuition for why parallelizing a network is non-trivial, consider the following naive way of dividing the problem. We can simulate network devices in parallel, which involves developing a simulator for a network switch and running parallel simulations for all the switches in the above figure on separate threads. The problem with this approach is that there is a dependence between a switch and every other switch in the
network, e.g. you cannot simulate the load on any of the switches at the top of figure 2 (core) without knowing how much data they are being sent by the switches underneath them (aggregation). The same goes for any other set of switches one can think of.


## 2. Usage

### 2.1 Code Dependencies

The code to run the simulation was developed in C, for both the serial and parallel version. Therefore, to execute the simulation, you need to have `gcc` installed in your machine. Siince the parallel simulation was developed with the help of OpenMP and MPI, you will also need to have `openmpi` and `openmp` installed in your machine to run the parallel simulation.

### 2.2. Simulation Execution

To download our code, you can clone the repository from our github page:

	`git clone https://github.com/ivzhang2/simulating-datacenter-fabrics`


Once the download is complete, the code can be compiled using the command:

	`make`

### 2.3. Code Documentation

We use [Doxygen](http://www.doxygen.nl/index.html) to generate the documentation of our code and visualize the relations between the elements within our modules. 
You can easily view the documentation using the following commands:

- For Mac OS X:

	`open docs/html/index.html`
		

- For Windows:

	`start docs/html/index.html`

- For Linux/Unix:

	`xdg-open docs/html/index.html`




