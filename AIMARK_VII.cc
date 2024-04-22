#include "Player.hh"
#include <climits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_VII


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }


  map<int, queue <pair<int, int>>> moves;
  /*
  1 = pioneer/furian ha de ser atacat
  2 = ataca
  3 = conquereix
  4 = es mou en el seu terreny
  */
  pair<Pos, string> bfs(const Pos& start) {
    vector<vector<bool>> visited(39, vector<bool>(80, false));
    queue<pair<Pos, string>> q;
    q.push({start ,""});
    visited[start.i][start.j] = true;
    while (!q.empty()) {
        Pos act = q.front().first;
        string act_str = q.front().second;
        q.pop();
        if (cell(act).id != -1 and unit(cell(act).id).player != me() and (unit(cell(act).id).type == Furyan or unit(cell(act).id).type == Pioneer)) {
            return {act, act_str};
        }
        vector<pair<Pos, string>> neighbors = {{act + Dir(0), act_str + "0"},{act + Dir(1), act_str + "1"},
        			                            {act + Dir(2), act_str + "2"},{act + Dir(3), act_str + "3"},
        			                            {act + Dir(4), act_str + "4"},{act + Dir(5), act_str + "5"},
        			                            {act + Dir(6), act_str + "6"},{act + Dir(7), act_str + "7"}};
        for (auto neighbor : neighbors) {
            if (pos_ok(neighbor.first) and cell(neighbor.first).type != Rock and not visited[neighbor.first.i][neighbor.first.j]) {
                q.push(neighbor);
                visited[neighbor.first.i][neighbor.first.j] = true;
            }
        }
    }
    return {Pos(-1, -1, -1), "8"};
}

  Dir getDirection(const Pos& a, const Pos& b) {
    if(a == b) return Dir(None);
    if(a.i == b.i){
      if(a.j > b.j) return Dir(2);
      else return Dir(6);
    }
    if(a.j == b.j){
      if(a.i > b.i) return Dir(4);
      else return Dir(0);
    }
    if(a.i < b.i){
      if(a.j < b.j) return Dir(1);
      else return Dir(7);
    }
    if(a.i > b.i){
      if(a.j < b.j) return Dir(3);
      else return Dir(5);
    }
    return Dir(None);
  }

  bool is_near_any_damage(Pos p){
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.j = p.j + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.i = p.i - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.i = p.i - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.j = p.j - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.j = p.j - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return true;
    return false;
  }
  
  int move_avoiding_near_damage(Pos p){
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 4 ;
    p.j = p.j + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 5 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 6 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 7 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 0 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 1 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 2 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 3 ;
  return 9;
  }
  
  int move_atack_near_damage(Pos p){
    Pos last = p;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 4 ;
    p.j = p.j + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 5 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 6 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 7 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 0 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 1 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 2 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Necromonger or unit(cell(p).id).type == Hellhound)) return 3 ;
    p = last;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 0 ;
    p.j = p.j + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 1 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 2 ;
    p.i = p.i - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 3 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 4 ;
    p.j = p.j - 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 5 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 6 ;
    p.i = p.i + 1;
    if(cell(p).id != -1 and (unit(cell(p).id).type == Furyan)) return 7 ;
    return 0;
  } 

  Dir dir_near_pioneer(Pos p){
    pair <Pos, string> par = bfs(p);
    //cerr << "---- DFS furyan pos (" << p.i << ", " << p.j << ") atack pioneer pos (" << par.first.i << ", " << par.first.j << ") movements: " << par.second << "next move: " <<par.second[0] << endl;
    return Dir(par.second[0]-'0');
  }

  void move_furyans() {
    vector <int> F = furyans(me());
    for (int id : F) {
      // search nearest pioneer()
      Pos p = unit(id).pos;
      pair<int, int> out;
      out.first = id;
      if (is_near_any_damage(p)){
        out.second = move_atack_near_damage(p);
        moves[1].push(out);
      }
      else{
        bool moved = false;
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 0;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 1;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 2;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 3;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 4;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 5;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 6;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id != -1 and unit(cell(p).id).player != me()){
            out.second = 7;
            moves[2].push(out);
            moved = true;
            }
        if (not moved){
            out.second = dir_near_pioneer(unit(id).pos);
            moves[4].push(out);
        }
      }
    }
  }

  void move_pioneers() {
    vector<int> P = pioneers(me());
    for (int id : P) {
      Pos p = unit(id).pos;
      pair<int, int> out;
      out.first = id;
      if (is_near_any_damage(p)){
        out.second = move_avoiding_near_damage(p);
        moves[1].push(out);
      }
      else{
        bool moved = false;
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 0;
            moves[3].push(out);
            moved = true;
            }
        p.j = p.j + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 1;
            moves[3].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 2;
            moves[3].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 3;
            moves[3].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 4;
            moves[3].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 5;
            moves[3].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 6;
            moves[3].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).owner != me() and cell(p).id == -1 and cell(p).id == -1) {
            out.second = 7;
            moves[3].push(out);
            moved = true;
            }
        if (not moved){
            out.second = random(0, 7);
            moves[4].push(out);
        }
      }
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
    for (int i = 1; i <= 4; ++i){
        while(not moves[i].empty()){
            command(moves[i].front().first, Dir(moves[i].front().second));
            moves[i].pop();
        }
    }

  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
