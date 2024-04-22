#include "Player.hh"
#include <climits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_V


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
  bool dfs_furyans(Pos p, vector<vector<bool>> &vis, Pos& go){
    bool resultado = false;
    vis[p.i][p.j] = true;
    Pos n;
    if (cell(p).id != -1 and unit(cell(p).id).type == Pioneer and unit(cell(p).id).player != me()) {go = p; return true;}
    go = p + Dir(0);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 0
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(1);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 1
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(2);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 2
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(3);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 3
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(4);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 4
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(5);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 5
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(6);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 6
      resultado = resultado or dfs_furyans(go,vis,n);
      if (resultado) {go = n; return true;}
    }
    go = p + Dir(7);
    if (pos_ok(go) and cell(go).type != Rock and !vis[go.i][go.j]){    // pos 7
      resultado = resultado or dfs_furyans(go,vis,n);
    }
    go = n;
    return resultado;
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

  Dir dir_near_atack(Pos p){
    Pos go;
    vector<vector<bool> > vis(40,vector<bool> (80,false));
    bool exist = dfs_furyans(p, vis, go);
    if (exist){
      cerr << "---- DFS furty pos (" << p.i << ", " << p.j << ") atack pioneer pos (" << go.i << ", " << go.j << ")" << endl;
      return getDirection(p, go);
    }
    return Dir(None);
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
            out.second = dir_near_atack(unit(id).pos);
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
