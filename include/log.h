#ifndef LOG_H
#define LOG_H
#include "game.h"
void playerLog(FILE *logfp, GAME *game);
void handLog(FILE *logfp, GAME *game);
void boardHLog(FILE *logfp, GAME *game); 
#endif