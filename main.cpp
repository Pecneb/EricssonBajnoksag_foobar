#include "classes.hpp"

//-------------------- classes.hpp fuggvenyeinek implementalasa-------------------
//--------------- field class
field::field() {
  t = NULL;
  population = 0;
  special = false;
  water = true;
  for(unsigned short i = 0; i < 4; i++) {
    neighbours[i] = NULL;
  }
  for(unsigned short i = 0; i < sizeof(coverageType); i++) {
    coverageType[i] = false;
  }
}
field::field(unsigned short pop) : population(pop) {
  if (population == 50) {
    special = true;
    water = false;
  }
  else if (population == 0) {
    water = true;
    special = false;
  }
  else {
    special = false;
    water = false;
  }
  for(unsigned short i = 0; i < 4; i++) {
    neighbours[i] = NULL;
  }
  for(unsigned short i = 0; i < sizeof(coverageType); i++) {
    coverageType[i] = false;
  }
}
field& field::setPopulation(unsigned short pop) {
  if (pop >= 0 && pop <=100) population = pop;
  return *this;
}
field& field::setTower(tower* tower) {t=tower; return *this;}
field& field::setSpecial() {
  if (getPopulation() == 50) special = true;
  return *this;
}
field& field::setWater() {
  if (getPopulation() == 0) water = true;
  return *this;
}
field& field::setNeighbours(field *above, field *left, field *right, field *under) {
  neighbours[0] = above;
  neighbours[1] = left;
  neighbours[2] = right;
  neighbours[3] = under;
  return *this;
}

field::~field() {}

//----------------------- tower class
tower::tower() {}
tower::tower(unsigned short ssz, unsigned short t, vector<field*> c, unsigned short r) {
  sorszam = ssz;
  type = t;
  coverage = c;
  rot = r;
  cegazon = "Foobar";
}
tower& tower::setCegazon(string ca) {cegazon = ca; return *this;}
tower& tower::setSorszam(unsigned short ssz) {sorszam = ssz; return *this;}
tower& tower::setType(unsigned short t) {type = t; return *this;}
tower& tower::setCoverage(vector<field*> c) {coverage = c; return *this;}
tower& tower::setCoverage(field* f) {coverage.push_back(f); return *this;}
tower& tower::setRot(unsigned short r) {
  if (r == 0 || r == 1 || r == 2 || r == 3) rot = r;
  else cerr << "Rotation csak 0, 1 (90 fok), 2(180 fok), 3 (270 fok) lehet\n";
  return *this;
}
tower::~tower() {}
//-------------------------- region class
region::region() {
  for (short i = 0; i < 4; i++) regionType[i] = false;
  water = false;
  uncovered = true;
  cegazon = "Foobar";
}
region::region(field* f) {
  fields.push_back(f);
  uncovered = false;
  cegazon = "Foobar";
}
region& region::setFields(vector<field*> v) {fields=v;return *this;}
region& region::setFields(field* f) {fields.push_back(f); return *this;}
region& region::setCegazon(string ca) {cegazon = ca; return *this;}
region& region::setRegionType(unsigned short t) {if (t <= 4 && t >= 1) regionType[t-1] = true; return *this;}
region::~region() {}
//------------------------ classes.hpp fuggvenyeinek vege-----------------------------


void readData(Reader &result) {
    std::string line;
    result.conditionalTask = false;
    result.needsAnswer = false;
    
    while (std::getline(std::cin, line)) {
        if (!line.rfind('.', 0))
            return;
        
        if (!line.rfind("WRONG", 0) ||
            !line.rfind("SUCCESS", 0) ||
            !line.rfind("FAILED", 0)) {
            result.hasEnded = true;
            result.message = std::move(line);
        } else if (!line.rfind("REQ", 0)) {
            result.needsAnswer = true;
            std::stringstream(std::move(line).substr(4)) >> result.data[0] >> result.data[1] >> result.data[2];
        } else if (!line.rfind("COND", 0)) {
            result.conditionalTask = true;
        } else if (!line.rfind("TYPE", 0)) {
            std::stringstream(std::move(line).substr(5)) >> result.towerTypes[0], result.towerTypes[1];
            for (short row = 0; row < 4; row++) {
                std::getline(std::cin, line);
                std::stringstream(line)
                        >> result.towerCoverage[row][0]
                        >> result.towerCoverage[row][1]
                        >> result.towerCoverage[row][2]
                        >> result.towerCoverage[row][3];
            }
        } else {
            std::cerr << "READER ERROR: Unrecognized command: " << line << std::endl;
            result.hasEnded = true;
            return;
        }
    }
    std::cerr << "Unexpected end of input." << std::endl;
    result.hasEnded = true;
}

//----------- Jatek lebonyolitasahoz kello fugvenyek

field** initBoard(unsigned short** p, unsigned short height, unsigned short width) {
  // Jatekter inicializalasa, egy height*width nagysagu
  // field matrixban.
  field** playBoard = new field*[height];

  // Matrix feltoltese field objektumokkal,
  // amiknek a populacioja p[y][x].
  for (short y=0; y<height; y++) {
    playBoard[y] = new field[width];
    for (short x=0; x<width; x++) {
      playBoard[y][x].setPopulation(p[y][x]).setSpecial().setWater();
    }
  }
  return playBoard;
}

short makeArrayContinous(short i, short maxI) {
  /* fuggveny 0 vagy pozitiv egesz indexet ad vissza.
   * Az indexeles 0 tol kezdodik. Ha pl a tomb 10 elembol
   * all, akkor a maxI = 9.
   * i: i. elem
   * max: nem negativ maximum hatar
   * Pelda: i = -5, max = 9.
   * Tulindexeles:       19 18 17 16 15 14 13 12 11  10
   * Elorol indexeles:    9  8  7  6  5  4  3  2  1   0
   * Hatulrol indexeles: -1 -2 -3 -4 -5 -6 -7 -8 -9 -10   
   * A pelda azt mutatja meg hogy mit is kellene visszaadnia
   * a fuggvenynek. 
   * Az otlet maga az. Hogyha alulindexelunk -1, akkor 9 nek
   * kell visszaternie. Ha tulidexelunk a megadott maxon, akkor
   * ha a tulindexelo szamot eloszjuk modulo maxI+1 el, akkor 
   * a helyes poziciot kapjuk meg. A negativ indexnel is hasonlo
   * az eljaras, csak ott venni kell az abszolut erteket, majd 
   * ellenorizni hogy nem nagyobb a abszolut ertek a maxI nel,
   * majd ha kivonjuk maxI+1 bol az abszolut erteket, akkor 
   * ismet a helyes poziciot kapjuk meg a tombon belul.     */
  if (i >= 0 && i <= maxI) return i;
  bool minus = false;
  short j = i;
  if (i<0) {minus=true; j=j*-1;}
  if(minus) {
    j = j % (maxI+1);
    if (j == 0) return j;
    return maxI+1-j;
  }
  j = j % (maxI+1);
  return j;
}

field** calcNeighbours(field** playBoard, unsigned short height, unsigned short width, unsigned short y, unsigned short x) {
  /* Egy field mutatokbol allo tombot ad vissza,
   * a megadott field szomszedjait. */
  field** nb = new field*[4];
  // Balra
  nb[1] = &playBoard[y][makeArrayContinous(x-1, width-1)];
  // Jobbra
  nb[2] = &playBoard[y][makeArrayContinous(x+1, width-1)];
  // Fennt
  nb[0] = &playBoard[makeArrayContinous(y+1, height-1)][x];
  // Lennt
  nb[3] = &playBoard[makeArrayContinous(y-1, height-1)][x];
  return nb;
}

void setNeighbours(field** playBoard, unsigned short height, unsigned short width, unsigned short y, unsigned short x) {
  /* A megkeresett szomszedokat (field** nb) allitja be az yx koordinataju fieldnek */
  field** nb = calcNeighbours(playBoard, height, width, y, x);
  playBoard[y][x].setNeighbours(nb[0], nb[1], nb[2], nb[3]);
}

void initBoardNeighbours(field** playBoard, unsigned short height, unsigned short width) {
  /* Megadott palyanak az elemeire beallitja a szomszedokat */
  for (unsigned short i = 0; i<height; i++) {
    for (unsigned short j = 0; j<width; j++) {
      setNeighbours(playBoard, height, width, i, j);
    }
  }
}

vector<field*> parseCoverageData(array<array<unsigned char, 4>, 4> c, unsigned short y, unsigned short x, field** playBoard, unsigned short height, unsigned short width) {
  /* Egy megadott torony lefedesi adatait konvertalja at,
   * oly modon hogy a tower class ertelmezni tudja.
   * Ehez kell egy bemenetrol kapott nyers lefedettsegi
   * tartomany array.
   * Kell a tower helye (y:magassag, x:szelesseg) aminek a lefedettseget akarjuk megadni.
   * A height es width argumentumok a playBoard magassaga es szelessege.
   * Ez azert kell hogy megkonnyitse a playBoard-al valo munkat. */
  vector<field*> towerCoverage;
  short iT;
  short jT;
  
  /* Meg kell keresni a tower relativ poziciojat a kapott
   * unsigned char matrixban es hozza adjuk a coverage vectorhoz*/
  for (short i=0; i<4; i++) {
    for(short j=0; j<4; j++) {
      if (c[i][j]=='O') {
        iT = i;
        jT = j;
        towerCoverage.push_back(&playBoard[y][x]);
        break;
      }
    }
  }
  /* Meg kell keresni a lefedettsegek relativ poziciojat
   * a tower poziciojahoz kepest.
   * Pl.:   0 1 2 3
   *      0 . . X .    yC = relativ pozicio O magassagahoz 
   *      1 X X O X    xC = relativ poz O szelessegehez
   *      2 . X X .
   *      3 . . X .                                        */
  for (short i=0; i<4; i++) {
    for (short j=0; j<4; i++) {
      switch(c[i][j]) {
        case 'X':
          short yC, xC;
          if (j < jT) { /* Balra van */
            xC = jT - j;
            if (i == iT) yC = iT; /* Megnezei hogy atlosan van e. */
            else if(i < iT ) yC = iT - i;
            else yC = iT + i; 
          }
          else if (j > jT) { /* Jobbra van */
            xC = jT + j;
            if (i == iT) yC = iT; /* Megnezei hogy atlosan van e. */
            else if(i < iT ) yC = iT - i;
            else yC = iT + i;
          }
          else if (j == jT) { /* Felette, alatta van */ 
            xC = jT;
            if (i < iT) yC = iT - i;
            else yC = iT + i;
          }
          /* Itt adom hozza a vectorhoz a lefedett teruletre mutato poshortert.
           * Itt is hasznalom a makeArrayContinous mert ha a relativ pozicio negativ
           * vagy tobb mshort kellene, akkor a makeArrayContinous fuggveny korrigalja ezt. */
          towerCoverage.push_back(&playBoard[makeArrayContinous(y+yC ,height-1)][makeArrayContinous(x+xC, width-1)]);
          break;
      }
    }
  }
  return towerCoverage;
}

bool inRegion(field* f, vector<field*> &r) {
  field** fr = r.data();
  for (unsigned short i = 0; i<r.size(); i++) {
    if (f != fr[i]) {
      return false;
    }
  }
  return true;
}

void findRegions(vector<region*> &r, field** playBoard, unsigned short height, unsigned short width, unsigned short regionType) {
  for (unsigned short i = 0; i<height; i++) {
    for (unsigned short j = 0; j < width; j++) {
      for (unsigned short k = 0; k<r.size(); k++) {
        if (!inRegion(&playBoard[i][j], *r[k]->getFields())) {
          r[k]->setFields(&playBoard[i][j]);
        } else {
          region* nR = new region(&playBoard[i][j]);
          nR->setRegionType(regionType);
          r.push_back(nR);
        }
      }
    }
  }
}

//---------------- Fuggvenyek vege

//---------------- Teruleti Feltetelek megirasa



int main() {
    std::string teamToken = "5qvbnfKKNj";
    short seed = 2;
    std::cout << "LOGIN " << teamToken
            << " " << seed
              << std::endl << "." << std::endl;
    
    std::string line;
    unsigned short gameID;
    std::getline(std::cin, line);
    std::stringstream(std::move(line).substr(6)) >> gameID;
    char criterias[4];
    std::getline(std::cin, line);
    std::stringstream (std::move(line).substr(5))
            >> criterias[0]
            >> criterias[1]
            >> criterias[2]
            >> criterias[3];
    unsigned short populations[21][28];
    std::getline(std::cin, line);
    for (auto &row : populations) {
        std::getline(std::cin, line);
        std::stringstream sstream(line);
        for (auto &col : row) {
            sstream >> col;
        }
    }
    std::getline(std::cin, line);
    
    Reader reader{};
  
    unsigned short** pop = new unsigned short*[21];
    for (short i=0; i<21; i++) {
      pop[i] = new unsigned short[28];
      for (short j=0; j<28; j++) {
        pop[i][j] = populations[i][j];
      }
    }
    field** playBoard = initBoard(pop, 21, 28);
    for (short i=0; i<21; i++) {
      delete pop[i];
    }
    delete[] pop;

    

    vector<region> type1;
    vector<region> type2;
    vector<region> type3;
    vector<region> type4;



    while (true) {
        readData(reader);
        if (reader.hasEnded)
            break;
        if (!reader.needsAnswer)
            continue;
    
        // Ha szeretnetek debug uzenetet kuldeni, akkor megtehetitek.
        // Maximalisan csak 1024 * 1024 bajtot!
        std::cerr << "Send response" << std::endl;
        unsigned short x,y,rot;
        x=y=rot=0;
        // standard out-ra meg mehet ki a megoldas! Mas ne irodjon ide ki ;)
        std::cout << "RES " << reader.data[0] << " " << reader.data[1] << " " << reader.data[2] << std::endl;
        std::cout << "PUT "<< y << " "<< x << " " << reader.towerTypes[0] << " "<< rot << std::endl;
        std::cout << "." << std::endl;
    }
    
    std::cerr << "END (message): " << reader.message << std::endl;
    
    return 0;
}
