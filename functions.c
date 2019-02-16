//
// Created by Petter on 07/12/2018.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This is the constructor for a new module. This constructor will return a module pointer.
 * @param name is the name of the module.
 * @param sem is witch semester the module is run in.
 * @return a pointer to the new module created.
 */
module *newModule(char name[8], int sem) {
    module *temp = malloc(sizeof(module)); // This will make a module with the size of module to give it space in memory.
    strcpy(temp->moduleName, name); //This will delete whats in the variable moduleName and replace it with name passed in.
    temp->semester = sem;
    temp->nextMod = NULL;
    return temp;
}

/**
 * This will make a link to the next module and make a linked list in the end.
 * @param prevMod is a pointer to the module at the end of the linked list.
 * @param newMod is a pointer to the new module added to the list.
 */
void nextModule(module *prevMod, module *newMod) {
    prevMod->nextMod = newMod;
}

/**
 * This will put the new module into the linked list at the end.
 * If the new module is the first on ti will sett it ass the head of the list.
 * @param new is a pointer to the new module added to the linked list.
 * @param headMod is a pointer to the head of the linked list.
 * @return a pointer of the new head of the linked list.
 */
module *insertModule(module *new, module *headMod) {
    module *tempModule = headMod;
    if (headMod == NULL) {
        headMod = new;
        return headMod;
    } else {
        while (tempModule->nextMod != NULL) {
            tempModule = tempModule->nextMod;
        }
        if (headMod != new) {
            nextModule(tempModule, new);
            return headMod;
        }
    }
}

/**
 * This is to search for an module in the linked list.
 * @param find the module the user want to find.
 * @param headM a pointer to the head to head of the linked list of modules.
 * @return the module it found or NULL.
 */
module *searchMod(module *find, module *headM) {
    module *temp = headM;
    while (1) {
        int ans = strcmp(temp->moduleName, find->moduleName);
        if (ans == 0) {
            return temp;
        } else {
            if (temp->nextMod == NULL) {
                printf("could not find the module you search for.");
                return NULL;
            }
            temp = temp->nextMod;
        }
    }
}

/**
 * This will print all of the modules in the linked list.
 * @param head is a pointer to the head of the linked list.
 */
void printModule(module *head) {
    module *tempmod = head;
    while (tempmod->nextMod != NULL) {
        printf("%s %d\n", tempmod->moduleName,
               tempmod->semester);
        tempmod = tempmod->nextMod;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This is a counstructor for a new lceture. this returns a pointer to the new lecture
 * @param mod is a pointer to the module this lecture has.
 * @param lW is how many lecture it is a week.
 * @param pW is how many practicals there is a week.
 * @return a pointer to the new lecture.
 */
lectures *newLectures(module *mod, char lW[4], char pW[4]) {
    lectures *temp = malloc(sizeof(lectures));
    temp->modLecture = mod;
    strcpy(temp->lectureAWeek, lW);
    strcpy(temp->practicalsAweek, pW);
    temp->nextLecture = NULL;
    return temp;
}

/**
 * This will make a link to the next lecture and make a linked list in the end.
 * @param prevLecture is a pointer to the lecture at the end of the linked list.
 * @param newLecture is a pointer to the new lecture added to the list.
 */
void nextLecture(lectures *prevLecture, lectures *newLecture) {
    prevLecture->nextLecture = newLecture;
}

/**
 * This will put the new lecture into the linked list at the end.
 * If the new lecture is the first on ti will sett it ass the head of the list.
 * @param newLecture is a pointer to the new lecture added to the linked list.
 * @param head is a pointer to the head of the linked list.
 * @return a pointer of the new head of the linked list.
 */
lectures *insertLecture(lectures *newLecture, lectures *head) {
    lectures *tempLecture = head;
    if (head == NULL) {
        head = newLecture;
        return head;
    } else {
        while (tempLecture->nextLecture != NULL) {
            tempLecture = tempLecture->nextLecture;
        }
        if (head != newLecture) {
            nextLecture(tempLecture, newLecture);
            return head;
        }
    }
}

/**
 * This will read inn all the modules and lectures in a given file.
 * @param fo is a pointer to the file the user is reading.
 * @param allHeads is a pointer to all heads.
 * @return all heds updated.
 */
head *readLectures(FILE *fo, head *allHeads) {
    lectures *headLec = allHeads->headLec;
    module *headMod = allHeads->headMod;

    char temp[8];
    while (EOF != fscanf(fo, "%s", temp)) { // this will go trough the file while it has not go to the end of the file
        char name[8];
        int sem = 0;
        char lW[4];
        char pW[4];
        strcpy(name, temp);
        fscanf(fo, "%d %s %s", &sem, lW, pW);
        module *mod = newModule(name, sem);
        headMod = insertModule(mod, headMod);
        lectures *new = newLectures(mod, lW, pW);
        headLec = insertLecture(new, headLec);
    }
    allHeads = setHeadsLM(allHeads, headLec, headMod);
    return allHeads;
}

/**
 * This wil print out all the lectures in the linked list.
 * @param head is a pointer to the first element in the linked list.
 */
void printLectures(lectures *head) {
    lectures *tempLecture = head;
    while (tempLecture->nextLecture != NULL) {
        printf("%s %d %s %s\n", tempLecture->modLecture->moduleName,
               tempLecture->modLecture->semester, tempLecture->lectureAWeek,
               tempLecture->practicalsAweek);
        tempLecture = tempLecture->nextLecture;
    }
    printf("%s %d %s %s\n", tempLecture->modLecture->moduleName,
           tempLecture->modLecture->semester, tempLecture->lectureAWeek,
           tempLecture->practicalsAweek);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * This is a construction for a common head.
 * @param headL this is a pointer for the start of the linked list for lectures.
 * @param headM this is a pointer for the start of the linked list for modules.
 * @param headS this is a pointer for the start of the linked list for schemes.
 * @param headT this is a pointer for the start of the linked list for times.
 * @return returns a pointer to the heads.
 */
head *newHead(lectures *headL, module *headM, schemes *headS, times *headT) {
    head *temp = malloc(sizeof(temp));
    temp->headLec = headL;
    temp->headMod = headM;
    temp->headSche = headS;
    temp->headTim = headT;
    return temp;
}

/**
 * This is to update the heads created.
 * @param allHeads this is a pointer to the head created and will be updated.
 * @param headL this is a pointer to the head of lectures.
 * @param headM this is a pointer to the head of modules.
 * @return a pointer to the updated head.
 */
head *setHeadsLM(head *allHeads, lectures *headL, module *headM) {
    allHeads->headLec = headL;
    allHeads->headMod = headM;
    return allHeads;
}

/**
 * This is to update the heads created.
 * @param allHeads this is a pointer to the head created and will be updated.
 * @param headS this is a pointer to the head of schemes.
 * @return a pointer to the updated head.
 */
head *setHeadS(head *allHeads, schemes *headS) {
    allHeads->headSche = headS;
    return allHeads;
}

/**
 * This is to update the head created.
 * @param allHeads this is a pointer to the head created and will be updated.
 * @param headT this is a pointer to the head of times.
 * @return a pointer to the updated head.
 */
head *setHeadT(head *allHeads, times *headT) {
    allHeads->headTim = headT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * This is a counstructor for a new scheme. this returns a pointer to the new scheme.
 * @param code is the scheme code.
 * @param year is the semestere the scheme is for.
 * @param num is the number of students.
 * @param coreModules this will say how many modules is in the scheme.
 * @param mod is the first module the scheme has.
 * @return is returning a pointer of the new scheme.
 */
schemes *newScheme(char code[5], int year, int num, int coreModules, module *mod) {
    schemes *temp = malloc(sizeof(schemes));
    strcpy(temp->code, code);
    temp->years = year;
    temp->numStudents = num;
    temp->coreModules = coreModules;
    temp->schemeMod = *mod;
    temp->nextScheme = NULL;
    return temp;
}

/**
 * This will make a link to the next scheme and make a linked list in the end.
 * @param prevScheme is a pointer to the scheme at the end of the linked list.
 * @param newScheme is a pointer to the new scheme added to the list.
 */
void nextScheme(schemes *prevScheme, schemes *newScheme) {
    prevScheme->nextScheme = newScheme;
}

/**
 * This will put the new scheme into the linked list at the end.
 * If the new scheme is the first on ti will sett it ass the head of the list.
 * @param newScheme is a pointer to the new scheme added to the linked list.
 * @param head is a pointer to the head of the linked list.
 * @return a pointer of the new head of the linked list.
 */
schemes *insertSchemes(schemes *newScheme, schemes *head) {
    schemes *tempScheme = head;
    if (head == NULL) {
        head = newScheme;
        return head;
    } else {
        while (tempScheme->nextScheme != NULL) {
            tempScheme = tempScheme->nextScheme;
        }
        if (head != newScheme) {
            nextScheme(tempScheme, newScheme);
            return head;
        }
    }
}

/**
 * This will read inn all the schemes in a given file.
 * @param fo is a pointer to the file the user is reading.
 * @param head is a pointer to all heads.
 * @return all heads updated.
 */
head *readSchemes(FILE *fo, head *head) {
    schemes *headScheme = head->headSche;
    int year = 0;
    int num = 0;
    int coreModules = 0;
    char code[5];
    while (EOF != fscanf(fo, "%s", code)) {
        fscanf(fo, "%d %d %d", &year, &num, &coreModules);
        module *startMod = NULL;
        for (int i = 0; i < coreModules; ++i) {
            if (i == 0) {
                char modName[8];
                fscanf(fo, "%s", modName);
                startMod = searchMod(newModule(modName, 0), head->headMod);
            } else {
                char modName[8];
                fscanf(fo, "%s", modName);
            }
        }
        schemes *new = newScheme(code, year, num, coreModules, startMod);
        headScheme = insertSchemes(new, headScheme);
    }
    head = setHeadS(head, headScheme);
    return head;
}

/**
 * This will search for the module in a scheme and give the information from the scheme
 * and give the clashing modules.
 * @param findScheme is a pointer the scheme the user want to find.
 * @param allHeads is a pointer to all the heads.
 */
void *searchScheme(schemes *findScheme, head *allHeads) {
    schemes *temp = allHeads->headSche;
    module *mods = malloc(sizeof(module) * 1);
    int timesRun = 0;
    int modsLengt = 1;
    while (1) {
        module *tempMod = &temp->schemeMod;
        int ans = strcmp(tempMod->moduleName, findScheme->schemeMod.moduleName);
        if (ans == 0) {
            tempMod = &temp->schemeMod;
            for (int j = 0; j < temp->coreModules; ++j) {
                int equal = 0;
                for (int i = 0; i < modsLengt; ++i) {
                    equal = 0;
                    if ((strcmp(mods[i].moduleName, tempMod->moduleName) == 0 |
                         strcmp(tempMod->moduleName, findScheme->schemeMod.moduleName) == 0)) {
                        equal++;
                        tempMod = tempMod->nextMod;
                        ++j;
                    }
                }
                if (equal == 0) {
                    mods[modsLengt - 1] = *tempMod;
                    printf("%s\n", tempMod->moduleName);
                    mods = realloc(mods, sizeof(mods) * 1);
                    modsLengt++;
                    tempMod = tempMod->nextMod;
                    ++j;
                }
                timesRun++;
            }
            ///////////////////////////////////////////////
            //printAscheme(temp);
            temp = temp->nextScheme;
        } else {
            for (int a = 0; a < temp->coreModules; ++a) {
                if (timesRun == 0){
                    printf("This module is run in semester %d\n",temp->years);
                    printf("The number of registered students is %d\n", temp->numStudents*temp->coreModules);
                    printf("This module is clashing with this modules: \n");
                }
                ans = 0;
                ans = strcmp(tempMod->moduleName, findScheme->schemeMod.moduleName);
                if (ans == 0) {
                    tempMod = &temp->schemeMod;
                    for (int j = 0; j <= temp->coreModules; ++j) {
                        int equal = 0;
                        for (int i = 0; i < modsLengt; ++i) {
                            equal = 0;
                            if ((strcmp(mods[i].moduleName, tempMod->moduleName) == 0 |
                            strcmp(tempMod->moduleName, findScheme->schemeMod.moduleName) == 0)) {
                                equal++;
                                tempMod = tempMod->nextMod;
                                ++j;
                            }
                        }
                        if (equal == 0) {
                            mods[modsLengt - 1] = *tempMod;
                            printf("%s\n", tempMod->moduleName);
                            mods = realloc(mods, sizeof(mods) * 1);
                            modsLengt++;
                            tempMod = tempMod->nextMod;
                            ++j;
                        }
                    }
                    /////////////////////////////////////
                    //printAscheme(temp);
                    //take the scheme
                }
                tempMod = tempMod->nextMod;
                timesRun++;
            }
            if (temp->nextScheme == NULL) {
                return NULL;
            } else
            temp = temp->nextScheme;
        }
    }
};

/**
 * This will print out all the schemes.
 * @param head is the start of the linked list.
 */
void printSchemes(schemes *head) {
    schemes *tempScheme = head;
    while (tempScheme->nextScheme != NULL) {
        printAscheme(tempScheme);
        tempScheme = tempScheme->nextScheme;
    }
    printAscheme(tempScheme);
}

/**
 * This will print a single scheme.
 * @param aScheme this is a pointer to the scheme.
 */
void printAscheme(schemes *aScheme) {
    module *temp = &aScheme->schemeMod;
    printf("%s %d %d %d", aScheme->code, aScheme->years, aScheme->numStudents,
           aScheme->coreModules);
    for (int i = 0; i < aScheme->coreModules; ++i) {
        printf(" %s ", temp->moduleName);
        temp = temp->nextMod;
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * This is a counstructor for a new time. this returns a pointer to the new time.
 * @param day it is the day.
 * @param hours is the amount of hours in a day.
 * @param oClock is the time the lecture or practical starts.
 * @return a pointer to the new time.
 */
times *newTime(char day[10], int hours, int oClock) {
    times *temp = malloc(sizeof(times));
    strcpy(temp->day, day);
    temp->houers = hours;
    temp->oClock = oClock;
    temp->nextTime = NULL;

}

/**
 * This will make a link to the next time and make a linked list in the end.
 * @param prevTime is a pointer to the time at the end of the linked list.
 * @param newTime is a pointer to the new time added to the list.
 */
void nextTime(times *prevTime, times *newTime) {
    prevTime->nextTime = newTime;
}

/**
 * This will put the new time into the linked list at the end.
 * If the new time is the first on ti will sett it ass the head of the list.
 * @param newTime is a pointer to the new time added to the linked list.
 * @param head is a pointer to the head of the linked list.
 * @return a pointer of the new head of the linked list.
 */
times *insertTime(times *newTime, times *head) {
    times *tempTime = head;
    if (head == NULL) {
        head = newTime;
        return head;
    } else {
        while (tempTime->nextTime != NULL) {
            tempTime = tempTime->nextTime;
        }
        if (head != newTime) {
            nextTime(tempTime, newTime);
            return head;
        }
    }
}

/**
 * This will read inn all the times in a given file.
 * @param fo is a pointer to the file the user is reading.
 * @param allHeads is a pointer to all heads.
 * @return all heads updated.
 */
head *readTimes(FILE *fo, head *allHeads) {
    times *headTimes = allHeads->headTim;
    char day[10] = "";
    int hoursADay = 0;
    while (EOF != fscanf(fo, "%s %d", day, &hoursADay)) {
        int hour = 0;
        if (hoursADay == 0) {
            times *new = newTime(day, hoursADay, hour);
        } else {
            for (int i = 0; i < hoursADay; ++i) {
                if (i == 0) {
                    fscanf(fo, "%d", &hour);
                } else {
                    int waste = 0;
                    fscanf(fo, "%d", &waste);
                }
            }
        }
        times *new = newTime(day, hoursADay, hour);
        headTimes = insertTime(new, headTimes);
    }
    allHeads = setHeadT(allHeads, headTimes);
}

/**
 * This will print out all the schemes.
 * @param head is the start of the linked list.
 */
void printTimes(times *head) {
    times *tempTime = head;
    while (tempTime->nextTime != NULL) {
        printf("%s %d", tempTime->day, tempTime->houers);
        for (int i = 0; i < tempTime->houers; ++i) {
            printf(" %d ", tempTime->oClock + i);
        }
        printf("\n");
        tempTime = tempTime->nextTime;
    }
    printf("%s %d", tempTime->day, tempTime->houers);
    for (int i = 0; i < tempTime->houers; ++i) {
        printf(" %d ", tempTime->oClock + i);
    }
    printf("\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This will attempt to build a timetable.
 * @param allHeads it is a pointer to all the heads.
 */
void makeATable(head *allHeads){
    head *tempHead = allHeads;
    module *tempMod = tempHead->headMod;
    times *tempTime = tempHead->headTim;
    printf("Do you want to build a table for\n"
           "Semester 1 or semester 2\n");
    int ans = 0;
    module *table[7][9];
    int row = 0;

    scanf("%d", &ans);
    if (ans == 1){
        times *header = tempTime;
        for (int i = 0; i < header->houers; ++i) {
            if (i == 0){
                printf("|    %d    ", (header->oClock + i));
            }else
            printf("|    %d   ", (header->oClock + i));
        }
        printf("|\n");
        while(row < 7) {
            int amountModules = 0;
            int column = 0;

            while (tempTime->houers > amountModules) {
                if (tempMod->semester == 1) {
                    int pastNine = tempTime->oClock - 9;
                    table[row][column + pastNine] = tempMod;
                    tempMod = tempMod->nextMod;
                    amountModules++;
                    column++;
                    printf("| %s ", tempMod->moduleName);
                }
                if (tempMod->semester == 2) {
                    tempMod = tempMod->nextMod;
                }
            }
            printf("|\n");
            tempTime = tempTime->nextTime;
            row++;
        }
    } else if (ans == 2){

    }else{
        printf("invalid input");
    }

}