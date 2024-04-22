#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_I


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
      vector<bool> m (8, false);
      Pos p = unit(id).pos;
      bool moved = false;
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(0)); moved = true;}
      p.j = p.j + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(1)); moved = true;}
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(2)); moved = true;}
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(3)); moved = true;}
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(4)); moved = true;}
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(5)); moved = true;}
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(6)); moved = true;}
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1) {command(id, Dir(7)); moved = true;}
      if (not moved) command(id, Dir(random(0, 7)));
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
