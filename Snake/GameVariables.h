#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

struct Coordinate {
    int x;
    int y;
};

struct GameVariables{
    Coordinate pos;
    QueueList<Coordinate> tail;
    int score;
    Coordinate apple_position;
    int high_score;
    int death_count;
    bool paused;
};

#endif // GAMEVARIABLES_H
