#ifndef LOGICERRORRECOGNIZER_H
#define LOGICERRORRECOGNIZER_H

int userInfoLER();
int initLER();
int addLER(char* argv);
int resetLER(int argc, char* argv[]);
int commitLER();
int commitSetLER(char* shortcutName);
#endif