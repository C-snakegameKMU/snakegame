#include "game.h"
void growing() {
    int r = 0;
    int food_crush_on = 0;
    while (1) {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r);
        g_itemx = (rand() % 18) + 1;
        g_itemy = (rand() % 18) + 1;

        if (map[stage][g_itemy][g_itemx] != 0) {
            food_crush_on = 1;
            r++;
        }
        if (food_crush_on == 1) continue;

        map[stage][g_itemy][g_itemx] = 5;
        break;
    }

}

void posion() {
    int r = 3;
    int food_crush_on = 0;
    while (1) {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r);
        p_itemx = (rand() % 18) + 1;
        p_itemy = (rand() % 18) + 1;

        if (map[stage][p_itemy][p_itemx] != 0) {
            food_crush_on = 1;
            r++;
        }
        if (food_crush_on == 1) continue;

        map[stage][p_itemy][p_itemx] = 6;
        break;

    }
}
void gate() {
    srand((unsigned)time(NULL));
    while (1) {
        gate1_x = (rand() % 21);
        gate1_y = (rand() % 21);
        if (map[stage][gate1_y][gate1_x] == 1) {
            map[stage][gate1_y][gate1_x] = 7;
            break;
        }
    }
    srand((unsigned)time(NULL));
    while (1) {
        gate2_x = (rand() % 21);
        gate2_y = (rand() % 21);
        if (map[stage][gate2_y][gate2_x] == 1) {
            map[stage][gate2_y][gate2_x] = 7;
            break;
        }
    }
}
