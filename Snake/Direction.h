#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction{
  UP,
  DOWN,
  RESERVED, // This is used to make computations easier/faster. Because the difference between UP and DOWN, as well as LEFT and RIGHT is now 1.
  LEFT,
  RIGHT  
};

#endif // DIRECTION_H
