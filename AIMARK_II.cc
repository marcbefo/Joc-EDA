#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_II


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  void search_nearest_pioneer();
  bool is_near_any_damage(Pos p){
    p.i = p.i + 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.j = p.j + 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.i = p.i - 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.i = p.i - 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.j = p.j - 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.j = p.j - 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.i = p.i + 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    p.i = p.i + 1;
    if(unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound) return true;
    return false;
  }

  void move_furyans() {
    vector <int> F = furyans(me());
    for (int id : F) {
      // search nearest pioneer()
      Pos p = unit(id).pos;
      bool moved = false;
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(0)); moved = true;}
      p.j = p.j + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(1)); moved = true;}
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(2)); moved = true;}
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(3)); moved = true;}
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(4)); moved = true;}
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(5)); moved = true;}
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(6)); moved = true;}
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()) {command(id, Dir(7)); moved = true;}
      if (not moved){
        p = unit(id).pos;
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(0)); moved = true;}
        p.j = p.j + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(1)); moved = true;}
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(2)); moved = true;}
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(3)); moved = true;}
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(4)); moved = true;}
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(5)); moved = true;}
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(6)); moved = true;}
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {command(id, Dir(7)); moved = true;}
        if (not moved) command(id, Dir(random(0, 7)));
      }
    }
  }

  void move_pioneers() {
    vector<int> P = pioneers(me());
    for (int id : P) {
      Pos p = unit(id).pos;
      bool moved = false;
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(0));
          moved = true;
          }
        }
      p.j = p.j + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(1));
          moved = true;
          }
        }
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(2));
          moved = true;
          }
        }
      p.i = p.i - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(3));
          moved = true;
          }
        }
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(4));
          moved = true;
          }
        }
      p.j = p.j - 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(5));
          moved = true;
          }
        }
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(6));
          moved = true;
          }
        }
      p.i = p.i + 1;
      if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
        if (not is_near_any_damage(p)){
          command(id, Dir(7));
          moved = true;
          }
        }
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
    move_furyans();
    move_pioneers();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
