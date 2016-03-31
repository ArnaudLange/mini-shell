#ifndef COMMANDParsedCommand_H
#define COMMAND_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define NAME_SIZE 100
#define MAX_COMMANDS 200

struct command{
        char name[NAME_SIZE];

        /**
         * Pointer to the function
         * NULL if the ParseCommand is not an internal
         * Otherwise it means the ParseCommand is internal and can be called
         */
        int (*cmd_ptr)(int, int);
};

/**
 * @brief      Structure for a shell ParseCommand
 */
struct parsedCommand{
        /**
         * Name of the ParseCommand
         */
	char name[NAME_SIZE];

        /**
         * Parameters of the ParsedCommand. 
         * Max size if 100 caracters.
         * Can hold up to 100 parameters
         */
        char parameters[MAX_COMMANDS][NAME_SIZE];
        /**
         * Options of the ParsedCommand. 
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


typedef struct parsedCommand ParsedCommand;
typedef struct command Command;

/**
 * @brief      Initialize an array of ParsedCommands.
 *
 * @return     1 if everything went correctly. 0 otherwise
 */
int initCommands(Command** array);

/**
 * @brief      Free all the dynamically allocated commands
 *
 * @param[in]  nbCmd     How many commands have been allocated in the array
 * @param      commands  The array of allocated commands
 *
 * @return     1 if the number of commands is ok, -1 otherwise
 */
int freeCommands(int nbCmd, Command** commands);

/**
 * @brief      Parse a String ParsedCommand
 *
 * @param      input  the input string to parse
 * @see        ParsedCommand
 * @return     a ParsedCommand struct which holds the different parsed informations
 */
ParsedCommand* parseCommand(char* input);

/**
 * @brief      Adds a Command struct to the array
 *
 * @param      array  The array in which to add the Command
 * @param[in]  index  The index to add the Command
 * @param      name   The name of the Command
 * @param      name   The function pointer to call the function
 *
 * @return     { description_of_the_return_value }
 */
int addCmdToArray(Command** array, int index, char* name, int (*cmd_ptr)(int, int));

/**
 * @brief      Print the name of the ParsedCommand
 *
 * @param      cmd   The ParsedCommand structure
 */
void printName(ParsedCommand* cmd);

/**
 * @brief      Print the parameters of the ParsedCommand
 *
 * @param      cmd   The ParsedCommand structure
 */
void printParameters(ParsedCommand* cmd);

/**
 * @brief      Print the options of the ParsedCommand
 *
 * @param      cmd   The ParsedCommand structure
 */
void printOptions(ParsedCommand* cmd);

#endif