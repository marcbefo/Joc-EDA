#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK0


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  typedef vector<int> VI;

  //map<int, int> kind; // For pioneers: 0 -> random, 1 -> cyclic.

  void move_pioneers() {
    vector<int> P = pioneers(me());
    for (int id : P) {
      command(id, Dir(Bottom));
    }
  }
  /**
   * Types and attributes for your player can be defined here.
   */

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_pioneers();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
