#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "functions.h"

int main() {

    lectures *headLectures = NULL;
    schemes *headScheme = NULL;
    module *headModule = NULL;
    times *headTimes = NULL;

    /*------------------------------------Finding a directory----------------------------------------*/
    printf("what is the name of the folder?\n");
    char dirName[30] = "../";
    char feedback[20];
    scanf("%s", feedback); //This is taking the string the user typed in.
    strcat(dirName, feedback);  //This is adding the name of the folder the user typed in to dirName.
    //initialing the different files
    char moduleFile[30] = "";
    char schemeFile[30] = "";
    char timesFile[30] = "";
    char roomFile[30] = "";
    //setting the folder where the files are and adding the name of the file to the path of the folder
    strcpy(moduleFile, dirName);
    strcat(moduleFile, "/modules.txt");
    strcpy(schemeFile, dirName);
    strcat(schemeFile, "/schemes.txt");
    strcpy(timesFile, dirName);
    strcat(timesFile, "/times.txt");
    strcpy(roomFile, dirName);
    strcat(roomFile, "/rooms.txt");
    /*-----------------------------------------------------------------------------------------------*/
    /*-------------------------------------Opening the directory-------------------------------------*/
    //Opening all of the files
    FILE *fileM = fopen(moduleFile, "r");
    FILE *fileS = fopen(schemeFile, "r");
    FILE *fileT = fopen(timesFile, "r");
    FILE *fileR = fopen(roomFile, "r");
    //Checking if it could open the folders
    if (fileM == NULL && fileS == NULL && fileT == NULL && fileR == NULL) {
        printf("404 file not find\n");

    } else {
        printf("found files: %s", "modules.txt, schemes.txt, times.txt, rooms.txt\n");
    /*-----------------------------------------------------------------------------------------------*/
    /*---------------------------------------Loading all files---------------------------------------*/
        printf("loading files...\n");
        head *allHeads = newHead(headLectures, headModule, headScheme, headTimes);// making an head to keep all heads
        allHeads = readLectures(fileM, allHeads); //reading in the modules file with the modules, lectures and practicals
        allHeads = readSchemes(fileS, allHeads); //reading in the schemes file with all the schemes in
        allHeads = readTimes(fileT, allHeads); //reading in the times file with all the times in
        printf("Files loaded\n");
    /*-----------------------------------------------------------------------------------------------*/
    /*--------------------------------------------Main menu------------------------------------------*/
        int choice = 9;
        while (choice != 0) {
            printf("\n");
            printf("1 - Printing all modules\n");
            printf("2 - Printing all lectures and practicals\n");
            printf("3 - Printing all schemes\n");
            printf("4 - Printing all times\n");
            printf("5 - Find a module\n");
            printf("6 - attempt to built a timetable\n");
            printf("0 - to Exit\n");
            scanf("%d", &choice); //taking one a number to choice one option from the mine menu
            switch (choice) {
                case 0: { // Exiting the program
                    printf("Exiting program");
                    return 0;
                }
                case 1: { //printing out all the modules
                    printModule(allHeads->headMod);
                    break;
                }
                case 2: { // printing out all the lectures and practicals
                    printLectures(allHeads->headLec);
                    break;
                }
                case 3: { // printing out all the schemes
                    printSchemes(allHeads->headSche);
                    break;
                }
                case 4: { // printing out all the times
                    printTimes(allHeads->headTim);
                    break;
                }
                case 5: { // printing out info about a module of your choice
                    printf("type in the module you want to find?\n");
                    char mod[8] = "";
                    scanf("%s", mod);
                    schemes *find = newScheme("", 0, 0, 0, newModule(strupr(mod), 0)); // making an module to search for
                    searchScheme(find, allHeads);
                    break;
                }
                case 6:{
                    makeATable(allHeads);
                    break;
                }
                default: { // If the user gives an invalid input
                    printf("invalid answer");
                    break;
                }
            }
        }
        return 0;
    }
    /*-----------------------------------------------------------------------------------------------*/
}