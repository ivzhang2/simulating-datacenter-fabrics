VPATH=src/:include/

CC=gcc
MPICC=mpicc
INCLUDE=include/
CFLAGS=-I $(INCLUDE) -Wall -Werror -pthread
MPICFLAGS=-I $(INCLUDE) -Wall -Werror 
LIB=-lm
CC_CMD=$(CC) $(CFLAGS)
MPI_CC_CMD=$(MPICC) $(MPICFLAGS)

# Note: apparently, linked library files should go *after* source files

OBJ_DIR=obj
BIN_DIR=bin
DEP_DIR=deps
DOC_DIR=docs

SRCS=$(wildcard *.c)
DEPS=$(srcs:.c=.d)

all: dir_tgt simulation traffic_generator simulation_mpi

simulation: flow.o arrival.o network_object.o topology.o switch.o link.o packet.o trace.o simulation_runs.o simulation.o
	$(CC_CMD) $(^:%.o=$(OBJ_DIR)/%.o) -o $(BIN_DIR)/$@ $(LIB)

simulation_mpi: flow.o arrival.o network_object.o topology.o switch.o link.o packet.o trace.o simulation_runs.o simulation_mpi.o
	$(MPI_CC_CMD) $(^:%.o=$(OBJ_DIR)/%.o) -o $(BIN_DIR)/$@ $(LIB)


run: simulation
	$(BIN_DIR)/simulation

traffic_generator: flow.o arrival.o traffic_matrix.o traffic_generator.o
	$(CC_CMD) $(^:%.o=$(OBJ_DIR)/%.o) -o $(BIN_DIR)/$@ $(LIB)

.PHONY: clean obj_dir_tgt bin_dir_tgt dep_dir_tgt doc

doc:
	doxygen doc.config

%.o : %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $(OBJ_DIR)/$@

MKDIR_P=mkdir -p

dir_tgt: obj_dir_tgt bin_dir_tgt dep_dir_tgt

obj_dir_tgt:
	$(MKDIR_P) $(OBJ_DIR)

bin_dir_tgt:
	$(MKDIR_P) $(BIN_DIR)

dep_dir_tgt:
	$(MKDIR_P) $(DEP_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	rm -rf $(DOC_DIR)

-include $(DEPS)
