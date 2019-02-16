//
// Created by Petter on 07/12/2018.
//

typedef struct module_sturct { // This will have the information on a module
    char moduleName[8]; //This is a char array for the name of the module.
    // The module can't have a name longer the 8 characters.
    int semester;
    struct module_sturct *nextMod; // This is a pointer to the next element so i can make an linked list
} module;
typedef struct lectures_struct { // This will have the information on a lecture and practical
    module *modLecture;
    char lectureAWeek[4];
    char practicalsAweek[4];
    struct lectures_struct *nextLecture; // This is a pointer to the next element so i can make an linked list
} lectures;
typedef struct schemes_struct { // This will have the information on a scheme
    char code[5];//This is a char array for the code of the scheme.
    // The scheme can't have a code longer the 5 characters.
    int years;
    int numStudents;
    int coreModules;
    module schemeMod;
    struct schemes_struct *nextScheme; // This is a pointer to the next element so i can make an linked list
} schemes;

typedef struct times_struct { // This will have the information on a time
    char day[10]; // This is a char array for the day. Days can'b be longer then 10 characters.
    int houers;
    int oClock;
    struct times_struct *nextTime; // This is a pointer to the next element so i can make an linked list
} times;

typedef struct head_struct { // This will have the information on a head
    times *headTim;
    module *headMod;
    schemes *headSche;
    lectures *headLec;
}head;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

module *newModule(char name[8], int sem);

void nextModule(module *prevMod, module *newMod);

module *insertModule(module *new, module *headMod);

module *searchMod (module *find, module *headM);

void printModule (module *head);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

lectures *newLectures(module *mod, char lW[4], char pW[4]);

void nextLecture(lectures *prevLecture, lectures *newLecture);

head *readLectures(FILE *fo, head *allHeads);

lectures *insertLecture(lectures *newLecture, lectures *head);

void printLectures(lectures *head);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

head *newHead(lectures *headL, module *headM, schemes *headS, times *headT);

head *setHeadsLM(head *allHeads, lectures *headL, module *headM);

head *setHeadS(head *allHeads, schemes *headS);

head *setHeadT(head *allHeads, times *headT);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

schemes *newScheme(char code[5], int year, int num, int coreModules, module *mod);

void nextScheme(schemes *prevScheme, schemes *newScheme);

schemes *insertSchemes(schemes *newScheme, schemes *head);

head *readSchemes(FILE *fo, head *head);

void *searchScheme(schemes *findScheme, head *allHeads);

void printSchemes(schemes *head);

void printAscheme(schemes *aScheme);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

times *newTime(char day[10], int hours, int oClock);

void nextTime(times *prevTime, times *newTime);

times *insertTime(times *newTime, times *head);

head *readTimes(FILE *fo, head *allHeads);

void printTimes(times *head);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void makeATable(head *allHeads);