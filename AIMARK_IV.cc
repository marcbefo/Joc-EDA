#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME MARK_IV


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
  2 = conquereix
  3 = ataca
  4 = es mou en el seu terreny
  */
  set<Pos> H;       // Llocs on pot atacar un Hellhound
  set<Pos> F_atack; //Llocs on pot atacar un furian
  set<Pos> F;       //posicions dels furians
  void nearest_pioneer();

  Dir get_direction(Pos from, Pos to) {
    // Calculate the difference between the positions
    int di = to.i - from.i;
    int dj = to.j - from.j;

    // Determine the direction
    if (di == 1) {
        if (dj == 0) {
            return Bottom;
        } else if (dj == 1) {
            return BR;
        } else if (dj == -1) {
            return LB;
        }
    } else if (di == -1) {
        if (dj == 0) {
            return Top;
        } else if (dj == 1) {
            return RT;
        } else if (dj == -1) {
            return TL;
        }
    } else if (di == 0) {
        if (dj == 1) {
            return Right;
        } else if (dj == -1) {
            return Left;
        }
    }

    // Default: return None if no valid direction is found
    return None;
}

  int go_outside(Pos p) {
    queue<Pos> bfsQueue;
    vector<std::vector<bool>> visited(40, vector<bool>(80, false));

    // Define the directions to explore
    const Dir directions[] = {Bottom, BR, Right, RT, Top, TL, Left, LB};

    // Enqueue the initial position
    bfsQueue.push(p);
    visited[p.i][p.j] = true;

    // Perform BFS
    while (!bfsQueue.empty()) {
        Pos current = bfsQueue.front();
        bfsQueue.pop();

        // Check if the current position is on the outer edge
        if (current.i == 0 || current.i == 40 - 1 || current.j == 0 || current.j == 80 - 1) {
            // Calculate the direction to the outside position
            int dir = static_cast<int>(get_direction(p, current));
            return dir;
        }

        // Explore neighbors
        for (Dir dir : directions) {
            Pos neighbor = current + dir;

            if (pos_ok(neighbor) && !visited[neighbor.i][neighbor.j]) {
                visited[neighbor.i][neighbor.j] = true;
                bfsQueue.push(neighbor);
            }
        }
    }

    // Default: if no suitable outside position found, return a random direction
    return random(0, DirSize - 1);
}

  void detect_furyans(){
    for (int p = 0; p < 4; ++p){
      if(p != me()){
        vector <int> fury = furyans(p);
         for(int id : fury){
          F.insert(unit(id).pos);
          int i = unit(id).pos.i;
          int j = unit(id).pos.j;
          int k = unit(id).pos.k;
          i -= 2;
          int ipos = i+5;
          j -= 2;
          int jpos = j+5;
          while (i < ipos){
              while (j < jpos){
                  if(j==jpos-5 or j==jpos-1 or i==ipos-5 or i==ipos-1){
                    if(pos_ok(i, j, k)) F_atack.insert(Pos(i, j, k));
                  }
                  ++j;
              }
              ++i;
              j = jpos-5;
          }
        }
      }
    }
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
  bool is_near_any_damage(Pos p){
    p.i = p.i + 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.j = p.j + 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.i = p.i - 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.i = p.i - 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.j = p.j - 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.j = p.j - 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.i = p.i + 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
    p.i = p.i + 1;
    if((H.find(p) != H.end())or(F.find(p) != F.end())) return true;
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
  bool near_necromongers();

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
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 0;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 1;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 2;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 3;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 4;
            moves[2].push(out);
            moved = true;
            }
        p.j = p.j - 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 5;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 6;
            moves[2].push(out);
            moved = true;
            }
        p.i = p.i + 1;
        if(not moved and pos_ok(p) and cell(p).type != Rock and unit(cell(p).id).player != me()){
            out.second = 7;
            moves[2].push(out);
            moved = true;
            }
        if (not moved){
            p = unit(id).pos;
            p.i = p.i + 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 0;
                moves[4].push(out);
                moved = true;}
            p.j = p.j + 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 1;
                moves[4].push(out);
                moved = true;}
            p.i = p.i - 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 2;
                moves[4].push(out);
                moved = true;}
            p.i = p.i - 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 3;
                moves[4].push(out);
                moved = true;}
            p.j = p.j - 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 4;
                moves[4].push(out);
                moved = true;}
            p.j = p.j - 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 5;
                moves[4].push(out);
                moved = true;}
            p.i = p.i + 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 6;
                moves[4].push(out);
                moved = true;}
            p.i = p.i + 1;
            if(not moved and pos_ok(p) and cell(p).type != Rock and cell(p).id == -1) {
                out.second = 7;
                moves[4].push(out);
                moved = true;}
            if (not moved){
                out.second = go_outside(unit(id).pos);
                moves[4].push(out);
            }
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
    detect_hellhounds();
    detect_furyans();
    move_pioneers();
    move_furyans();
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
