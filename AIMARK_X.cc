#include "Player.hh"
#include <climits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_IX


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  set <Pos> H;
  map<int, queue <pair<int, int>>> moves;
  /*
  0 = arac per hellhound proper
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

 void detect_hellhounds(){
        vector <int> hell = hellhounds();
        for(int id : hell){
        int i = unit(id).pos.i;
        int j = unit(id).pos.j;
        int k = unit(id).pos.k;
        i -= 3;
        int ipos = i+7;
        j -= 3;
        int jpos = j+7;
        while (i < ipos){
            while (j < jpos){
                if(j==jpos-7 or j==jpos-6 or j==jpos-2 or j==jpos-1 or i==ipos-7 or i==ipos-6 or i==ipos-2 or i==ipos-1){
                if(pos_ok(i, j, k)) H.insert(Pos(i, j, k));
                }
                ++j;
            }
            ++i;
            j = jpos-7;
        }
    }
  }

  pair<Pos, string> bfs_pioneer(const Pos& start) {
    vector<vector<bool>> visited(39, vector<bool>(80, false));
    queue<pair<Pos, string>> q;
    q.push({start ,""});
    visited[start.i][start.j] = true;
    while (!q.empty()) {
        Pos act = q.front().first;
        string act_str = q.front().second;
        q.pop();
        if (cell(act).id != -1) {
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

  bool is_near_any_normal_damage(Pos p){
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.j = p.j + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.i = p.i - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.i = p.i - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.j = p.j - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.j = p.j - 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    p.i = p.i + 1;
    if(pos_ok(p) and cell(p).id != -1 and (unit(cell(p).id).type == Furyan or unit(cell(p).id).type == Necromonger)) return true;
    return false;
  }
  
  bool is_near_any_hellhound(Pos p){
    for(int i = 0; i < 8; ++i){
        Pos aux = p + Dir(i);
        if(H.find(aux) != H.end()) return true;
    }
    return false;
  }

  int move_avoiding_near_damage(Pos p){
    for (int i = 0; i < 8; ++i){
        Pos aux = p + Dir(i);
        if(pos_ok(aux) and pos_ok(p + Dir((i+4)%8)) and cell(aux).id != -1 and cell(aux).type != Rock and (unit(cell(aux).id).type == Furyan or unit(cell(aux).id).type == Necromonger or unit(cell(aux).id).type == Hellhound)) return (i+4)%8;
    }
    return 8;
  }

  int move_avoiding_near_hellhound(Pos p){
    for (int i = 0; i < 8; ++i){
        Pos aux = p + Dir(i);
        if(H.find(aux) != H.end()) return (i+4)%8;
    }
    return 8;
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
    if(par.second.empty())return Dir(8);
    else return Dir(par.second[0]-'0');
  }

  Dir dir_near_outside_position(Pos p){ 
  pair <Pos, string> par = bfs_pioneer(p);
    if(par.second.empty())return Dir(8);
    else return Dir(par.second[0]-'0');
  }

  void move_furyans() {
    vector <int> F = furyans(me());
    for (int id : F) {
      // search nearest pioneer()
      Pos p = unit(id).pos;
      pair<int, int> out;
      out.first = id;
      if (is_near_any_hellhound(p)){
        out.second = move_avoiding_near_hellhound(p);
        moves[4].push(out);
      }
      else if (is_near_any_normal_damage(p)){
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
      if (is_near_any_hellhound(p)){
        out.second = move_avoiding_near_hellhound(p);
        moves[4].push(out);
      }
      else if (is_near_any_normal_damage(p)){
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
            out.second = dir_near_outside_position(unit(id).pos);
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
    detect_hellhounds();
    move_furyans();
    move_pioneers();
    for (int i = 0; i <= 4; ++i){
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