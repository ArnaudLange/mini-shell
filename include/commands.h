#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define NAME_SIZE 100
#define MAX_COMMANDS 200

/**
 * @brief      Structure for a shell command
 */
struct command{
        /**
         * Name of the command
         */
	char name[NAME_SIZE];

        /**
         * Parameters of the commands. 
         * Max size if 100 caracters.
         * Can hold up to 100 parameters
         */
        char parameters[MAX_COMMANDS][NAME_SIZE];
        /**
         * Options of the commands. 
         * Max size if 100 caracters.
         * Can hold up to 100 options
         */
        char options[MAX_COMMANDS][NAME_SIZE];
        /**
         * Size of the name
         */
        int nameLength;
        /**
         * Size of the parameters
         * 100 sizes for 100 parameters available
         */
        int parameterLength[NAME_SIZE];
        /**
         * Size of the options
         * 100 sizes for 100 options available
         */
        int optionLength[NAME_SIZE];

        /**
         * Pointer to the function
         * NULL if the command is not an internal
         * Otherwise it means the command is internal and can be called
         */
	int (*cmd_ptr)(int, int);
};

/**
 * Enumeration of all the automate states
 */
typedef enum {
        S0, // starting state is S0
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        S10,
        S11,
        S12,
        S13
} State;


typedef struct command Command;

/**
 * @brief      Initialize an array of commands.
 *
 * @return     1 if everything went correctly. 0 otherwise
 */
int initCommands(Command** array);

int freeCommands(int nbCmd, Command** commands);

Command* allocateCommand(char* name, char** parameters, char** options, int nameLength, int* parameterLength, int* optionLength, int (*cmd_ptr)(int, int));

Command** allocateCommands(int amount);

/**
 * @brief      Parse a String command
 *
 * @param      input  the input string to parse
 * @see        command
 * @return     a Command struct which holds the different parsed informations
 */
Command* parseCommand(char* input);

/**
 * @brief      Print the name of the command
 *
 * @param      cmd   The command structure
 */
void printName(Command* cmd);

/**
 * @brief      Print the parameters of the command
 *
 * @param      cmd   The command structure
 */
void printParameters(Command* cmd);

/**
 * @brief      Print the options of the command
 *
 * @param      cmd   The command structure
 */
void printOptions(Command* cmd);

#endif