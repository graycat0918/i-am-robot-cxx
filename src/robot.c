/**
 * @file robot.c
 * defination of 'robot'.
 *
 * @author  duruyao
 * @version 1.0  20-03-21
 * @update  [id] [yy-mm-dd] [author] [description] 
 */

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "robot.h"

#define HEIGHT  16
#define WIDTH   26

/******************************************************************************/
/*                                                                            */
/* struct defination                                                          */
/*                                                                            */
/******************************************************************************/


struct STEP {
    uint8_t s_nb;
    char  **str;
};

struct ACTION {
    char   *folder;
    char    cmd;
    uint8_t st_nb;
    Step   *step;
};

struct POSITION {
    int x;
    int y;
};

struct ROBOT {
    uint8_t id;
    uint8_t width;
    uint8_t height;
    uint8_t act_nb;
    Act *action;
    Pos  pos;

    int (*init)(Bot *, uint8_t, uint8_t, uint8_t, uint8_t, Act *, Pos);
    int (*ctrl)(Bot *, char *, char *, char *, char *, char *, char *);
};


/******************************************************************************/
/*                                                                            */
/* func defination                                                            */
/*                                                                            */
/******************************************************************************/


int create_bot(Bot **bot_p) {
    if ((*bot_p = ALLOC(1, Bot)) == NULL) {
        fprintf(stderr, "Allocate memory error\n");
        return -1;
    }
    (*bot_p)->init = &bot_init;
    (*bot_p)->ctrl = &bot_ctrl;

    return 0;
}

int delete_bot(Bot **bot_p) {
    if (bot_p == NULL || *bot_p == NULL)
        return -1;

    Bot *bot = *bot_p;
    if (bot->action == NULL)
        return 0;

 // while ((bot->act_nb)--) {
 //     Act a = bot->action[bot->act_nb];
 //     while ((a.st_nb)--) {
 //         Step s = a.step[a.st_nb];
 //         FREE((s.s_nb), (s.str));
 //     }
 // }
    free(bot);
    *bot_p = NULL;

    return 0;
}

int bot_init(Bot *bot, uint8_t id, uint8_t wdt,
             uint8_t hgt, uint8_t act_nb, Act *act, Pos pos) {
    if (bot == NULL)
        return -1;
    bot->id     = id;
    bot->width  = wdt;
    bot->height = hgt;
    bot->act_nb = act_nb;
    bot->action = act;
    bot->pos    = pos;

    return 0;
}

int bot_ctrl(Bot *bot, char *left, char *right,
             char *up, char *down, char *dance, char *kick) {

    return 0;
}

int act_load(Act *act, uint8_t act_nb,
             char *cmd, uint8_t *step_nb, char **folder) {
    if (act == NULL)
        return -1;
    for (uint8_t i = 0; i < act_nb; i++) {
        act[i].cmd    = cmd[i];
        act[i].st_nb  = step_nb[i];
        act[i].folder = folder[i];
        for (int j = 0; j < step_nb[i]; j++) {
            char filename[255];//////
            FILE *fd = NULL;
            if ((fd = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "Cannot open %s\n", filename);
                return -1;
            }
            if ((act[i].step[j].str == ALLOC(HEIGHT, char*)) == NULL) {
                fprintf(stderr, "Allocate memory error\n");
                return -1;
            }
            for (int k = 0; k < HEIGHT; k++) {
                if ((act[i].step[j].str[k] = ALLOC(WIDTH + 1, char)) == NULL) {
                    fprintf(stderr, "Cannot open %s\n", filename);
                    return -1;
                }
                fgets(act[i].step[j].str[k], WIDTH + 1, fd);
            }
            if (fd)
                fclose(fd);
        }
    }

    return 0;
}

int act_unload(Act *act, uint8_t act_nb) {
    if (act == NULL)
        return 0;
    while (act_nb--) {
        Act a = act[act_nb];
        while ((a.st_nb)--) {
            Step s = a.step[a.st_nb];
            FREE((s.s_nb), (s.str));
        }
    }
    
    return 0;
}

