/***************************************************** 
* maputils.c --- implementation file for ascii maps  * 
*				     		     * 
* Kyle Goodwin, (c) 1998 All Rights Reserved         * 
* vbmasta@earthlink.net - Head Implemenor FirocMUD   * 
*				     		     * 
* Paolo Libardi - pinkpallin@libero.it		     * 
*****************************************************/
#include "maputils.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "db.h"
#include "vehicles.h"


int mapnums[MAP_ROWS + 1][MAP_COLS + 1];

void ping_ship(int vnum, int vnum2) {

    struct char_data *tch, *next_ch;
    struct obj_data *controls = NULL, *obj = NULL;
    int found = false;

    if (vnum2 == -1) {
        return;
    }

    for (tch = character_list; tch; tch = next_ch) {
        next_ch = tch->next;
        if (found == false) {
            if (!(obj = find_control(tch))) {
                continue;
            } else {
                if (GET_OBJ_VAL(obj, 0) == vnum && vnum != vnum2) {
                    controls = obj;
                    found = true;
                }
            }
        }
    }

    if (found == true) {
        send_to_room(IN_ROOM(controls), "@D[@RALERT@D: @YAn unknown radar signal has been detected!@D]@n");
    }
}

int checkship(int rnum, int vnum) {
    struct obj_data *i = NULL;
    int there = false;

    for (i = world[rnum].contents; i; i = i->next_content) {
        if (!ROOM_FLAGGED(rnum, ROOM_NEBULA)) {
            if (GET_OBJ_TYPE(i) == ITEM_VEHICLE && there != true) {
                there = true;
                ping_ship(GET_OBJ_VNUM(i), vnum);
            }
        }
    }

    i = NULL;

    return there;
}

char *getmapchar(int rnum, struct char_data *ch, int start, int vnum) {
    int mapchars = 50;
    static char mapchar[50];
    int there = false, enemy = false;

    if (rnum == start) {
        there = true;
    }
    if (checkship(rnum, vnum)) {
        enemy = true;
    }

    if (rnum == real_room(GET_RADAR1(ch)) || rnum == real_room(GET_RADAR2(ch)) || rnum == real_room(GET_RADAR3(ch))) {
        if (there) {
            snprintf(mapchar, mapchars, "@WB@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@WB@r#");
        } else {
            snprintf(mapchar, mapchars, "@WBB");
        }
    } /* End Buoy */
    else if (ROOM_FLAGGED(rnum, ROOM_EORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@GE@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@GE@r#");
        } else {
            snprintf(mapchar, mapchars, "@GEE");
        }
    } /* End Earth Character */
    else if (ROOM_FLAGGED(rnum, ROOM_CORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@MC@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@MC@r#");
        } else {
            snprintf(mapchar, mapchars, "@MCC");
        }
    } /* End Cerria Character */
    else if (ROOM_FLAGGED(rnum, ROOM_FORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@CF@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@CF@r#");
        } else {
            snprintf(mapchar, mapchars, "@CFF");
        }
    } /* End Frigid Character */
    else if (ROOM_FLAGGED(rnum, ROOM_KORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@mK@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@mK@r#");
        } else {
            snprintf(mapchar, mapchars, "@mKK");
        }
    } /* End Konack Character */
    else if (ROOM_FLAGGED(rnum, ROOM_NORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@gN@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@gN@r#");
        } else {
            snprintf(mapchar, mapchars, "@gNN");
        }
    } /* End Namek Character */
    else if (GET_ROOM_VNUM(rnum) == 50772) {
        if (there) {
            snprintf(mapchar, mapchars, "@cZ@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@cZ@r#");
        } else {
            snprintf(mapchar, mapchars, "@cZZ");
        }
    } /* End Zenith Character */
    else if (ROOM_FLAGGED(rnum, ROOM_VORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@YV@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@YV@r#");
        } else {
            snprintf(mapchar, mapchars, "@YVV");
        }
    } /* End Vegeta Character */
    else if (ROOM_FLAGGED(rnum, ROOM_AORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@BA@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@BA@r#");
        } else {
            snprintf(mapchar, mapchars, "@BAA");
        }
    } /* End Aether Character */
    else if (ROOM_FLAGGED(rnum, ROOM_YORBIT)) {
        if (there) {
            snprintf(mapchar, mapchars, "@MY@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@MY@r#");
        } else {
            snprintf(mapchar, mapchars, "@MYY");
        }
    } /* End Yardrat Character */
    else if (ROOM_FLAGGED(rnum, ROOM_KANORB)) {
        if (there) {
            snprintf(mapchar, mapchars, "@CK@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@CK@r#");
        } else {
            snprintf(mapchar, mapchars, "@CKK");
        }
    } /* End Kanassa Character */
    else if (ROOM_FLAGGED(rnum, ROOM_ARLORB)) {
        if (there) {
            snprintf(mapchar, mapchars, "@mA@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@mA@r#");
        } else {
            snprintf(mapchar, mapchars, "@mAA");
        }
    } /* End Arlia Character */
    else if (ROOM_FLAGGED(rnum, ROOM_NEBULA)) {
        if (there) {
            snprintf(mapchar, mapchars, "@m&@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@m&@r#");
        } else {
            snprintf(mapchar, mapchars, "@m&&");
        }
    } /* End Nebula Character */
    else if (GET_ROOM_VNUM(rnum) == 38028) {
        if (there) {
            snprintf(mapchar, mapchars, "@yQ@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@yQ@r#");
        } else {
            snprintf(mapchar, mapchars, "@yQQ");
        }
    } /* End Namek Character */
    else if (ROOM_FLAGGED(rnum, ROOM_ASTERO)) {
        if (there) {
            snprintf(mapchar, mapchars, "@y:@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@y:@r#");
        } else {
            snprintf(mapchar, mapchars, "@y::");
        }
    } /* End Asteroid Character */
    else if (ROOM_FLAGGED(rnum, ROOM_WORMHO)) {
        if (there) {
            snprintf(mapchar, mapchars, "@b@1*@RX@n");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@b@1*@r#@n");
        } else {
            snprintf(mapchar, mapchars, "@b@1**@n");
        }
    } /* End Wormhole Character */
    else if (ROOM_FLAGGED(rnum, ROOM_STATION)) {
        if (there) {
            snprintf(mapchar, mapchars, "@DS@RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@DS@r#");
        } else {
            snprintf(mapchar, mapchars, "@DSS");
        }
    } /* End Station Character */
    else if (ROOM_FLAGGED(rnum, ROOM_STAR)) {
        if (there) {
            snprintf(mapchar, mapchars, "@6 @RX@n");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@6 @r#@n");
        } else {
            snprintf(mapchar, mapchars, "@6  @n");
        }
    } /* End Star Character */
    else {
        if (there) {
            snprintf(mapchar, mapchars, "@w @RX");
        } else if (enemy == true) {
            snprintf(mapchar, mapchars, "@w @r#");
        } else {
            int color = rand_number(1, 30);
            if (rand_number(1, 40) == 2) {
                snprintf(mapchar, mapchars, "%s. ", color > 15 ? "@w" : (color >= 7 ? "@Y" : (color > 3 ? "@R" : "@B")));
            } else if (rand_number(1, 40) == 2) {
                snprintf(mapchar, mapchars, "%s .", color > 15 ? "@w" : (color >= 7 ? "@Y" : (color > 3 ? "@R" : "@B")));
            } else {
                snprintf(mapchar, mapchars, "@w  ");
            }
        }
    } /* End default Character */
    return mapchar;
}

MapStruct findcoord(int rnum) {
    int x, y;
    MapStruct coords;

    coords.x = 0;
    coords.y = 0;

    for (y = 0; y <= MAP_ROWS; y++) {
        for (x = 0; x <= MAP_COLS; x++) {
            if (mapnums[y][x] == rnum) {
                coords.y = y;
                coords.x = x;
                return coords;
            }
        }
    }

    log("SYSERR: findcoord for non-map rnum");
    return coords;
}

void printmap(int rnum, struct char_data *ch, int type, int vnum) {
    int x = 0, lasty = -1;
    int y = 0;
    int sightradius;
    int count = 0, initline = 0;
    char buf[MAX_STRING_LENGTH * 2];
    char buf2[512];
    MapStruct coord;

    int start = rnum;

    coord = findcoord(rnum);
    strcpy(buf, "\n");
    if (type == 0) {
        sightradius = 12;
    } else {
        sightradius = 4;
    }

    if (type == 0) {
        send_to_char(ch, "@b______________________________________________________________________@n\n");
    }

    for (y = coord.y - sightradius; y <= coord.y + sightradius; y++) {
        if (type == 0) {
            if (count == initline) {
                strcat(buf, "@b     [@CR. Key@b]     | ");
            } else if (count == initline + 1) {
                strcat(buf, "@GEE@D:@w Earth@b         | ");
            } else if (count == initline + 2) {
                strcat(buf, "@gNN@D:@w Namek@b         | ");
            } else if (count == initline + 3) {
                strcat(buf, "@YVV@D:@w Vegeta@b        | ");
            } else if (count == initline + 4) {
                strcat(buf, "@CFF@D:@w Frigid@b        | ");
            } else if (count == initline + 5) {
                strcat(buf, "@mKK@D:@w Konack@b        | ");
            } else if (count == initline + 6) {
                strcat(buf, "@BAA@D:@w Aether@b        | ");
            } else if (count == initline + 7) {
                strcat(buf, "@MYY@D:@w Yardrat@b       | ");
            } else if (count == initline + 8) {
                strcat(buf, "@CKK@D:@w Kanassa@b       | ");
            } else if (count == initline + 9) {
                strcat(buf, "@mAA@D:@w Arlia@b         | ");
            } else if (count == initline + 10) {
                strcat(buf, "@cZZ@D:@w Zenith@b        | ");
            } else if (count == initline + 11) {
                strcat(buf, "@MCC@D:@w Cerria@b        | ");
            } else if (count == initline + 12) {
                strcat(buf, "@WBB@D:@w Buoy@b          | ");
            } else if (count == initline + 13) {
                strcat(buf, "@m&&@D:@w Nebula@b        | ");
            } else if (count == initline + 14) {
                strcat(buf, "@yQQ@D:@w Asteroid@b      | ");
            } else if (count == initline + 15) {
                strcat(buf, "@y::@D:@w Asteroid Field@b| ");
            } else if (count == initline + 16) {
                strcat(buf, "@b@1**@n@D:@w Wormhole@b      | ");
            } else if (count == initline + 17) {
                strcat(buf, "@DSS@D:@w S. Station@b    | ");
            } else if (count == initline + 18) {
                strcat(buf, " @r#@D:@w Unknown Ship@b  | ");
            } else if (count == initline + 19) {
                strcat(buf, "@6  @n@D:@w Star@b          | ");
            } else {
                strcat(buf, "                  @b| ");
            }
            count++;
        } else {
            if (count == 0) {
                strcat(buf, "      @RCompass@n           ");
            } else if (count == 2) {
                sprintf(buf2, "@w       @w|%s@w|            ", (W_EXIT(rnum, 0) ? " @CN " : "   "));
                strcat(buf, buf2);
            } else if (count == 3) {
                sprintf(buf2, "@w @w|%s@w| |%s@w| |%s@w|      ", (W_EXIT(rnum, 6) ? " @CNW" : "   "),
                        (W_EXIT(rnum, 4) ? " @YU " : "   "), (W_EXIT(rnum, 7) ? "@CNE " : "   "));
                strcat(buf, buf2);
            } else if (count == 4) {
                sprintf(buf2, "@w @w|%s@w| |%s@w| |%s@w|      ", (W_EXIT(rnum, 3) ? "  @CW" : "   "),
                        (W_EXIT(rnum, 10) ? "@m I " : (W_EXIT(rnum, 11) ? "@mOUT" : "   ")),
                        (W_EXIT(rnum, 1) ? "@CE  " : "   "));
                strcat(buf, buf2);
            } else if (count == 5) {
                sprintf(buf2, "@w @w|%s@w| |%s@w| |%s@w|      ", (W_EXIT(rnum, 9) ? " @CSW" : "   "),
                        (W_EXIT(rnum, 5) ? " @YD " : "   "), (W_EXIT(rnum, 8) ? "@CSE " : "   "));
                strcat(buf, buf2);
            } else if (count == 6) {
                sprintf(buf2, "@w       @w|%s@w|            ", (W_EXIT(rnum, 2) ? " @CS " : "   "));
                strcat(buf, buf2);
            } else {
                strcat(buf, "                        ");
            }
            count++;
        }
        for (x = coord.x - sightradius; x <= coord.x + sightradius; x++) {
            if (x == coord.x && y == coord.y) {
                strcat(buf, getmapchar(mapnums[y][x], ch, start, vnum));
            } else if (x > MAP_COLS || x < 0) {
                if (lasty != true && y > -1 && y < 200) {
                    strcat(buf, "@D?");
                    lasty = true;
                }
            } else if (y > MAP_ROWS || y < 0) {
                if (y == -1 || y == 200) {
                    strcat(buf, "@D??");
                }
            } else
                strcat(buf, getmapchar(mapnums[y][x], ch, start, vnum));
        }
        strcat(buf, "\n");
        lasty = false;
    }

    send_to_char(ch, buf);
    *buf2 = '\0';
    *buf = '\0';
    if (type == 0) {
        send_to_char(ch, "\n@b______________________________________________________________________@n");
    }
}
