#ifndef CLASSES
#define CLASSES

using namespace std;

#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <iostream>

class field {
  /* Palyan levo egy field. Aminek van populatione,
   * es telepiteni kell ra egy adotornyot.
   * Ha 50 a populatione akkor specialis (strategiailag fontos varos) field.
   * Ha population 0 akkor water fedi.
   * 
   * Esetleg fedettsegi allapotot is tarolhatna,
   * de ha regiokba soroljuk oket,
   * akkor nem feltetlenul muszaly,
   * ezt meg kene beszelni!!! */
  private:
    tower *t;
    unsigned int population;
    bool special;
    bool water;
    /* 4 db elszomszed lehet.
     * Bal, jobb, fennt, lennt.
     *   f   felette egyel r-1
     *  b j  balra c-1 jobbra c+1
     *   l   alatta egyel r+1
     * Ezeknek az eltarololasat egy 4 tagu
     * mutato tombel oldottam meg */
    field* neighbours[4];
  public:
    field();
    field(tower*, int, field*[4]);
    int getPopulation() {return population;}
    tower* getTower() {return t;}
    bool getSpecial() {return specialis;}
    bool getWater() {return water;}
    field** getNeighbours() {return neighbours;}
    field& setPopulation(int);
    field& setTower(tower*);
    field& setSpecial();
    field& setWater();
    field& setNeighbours(field*, field*, field*, field*);
    ~field();
    /* copy const es assignment const egyenlore ki van kapcsolva */
    field(const field&) = delete;
    field& operator(const field&) = delete;
}

class tower {
  private:
    string cegazon;
    unsigned int sorszam;
    unsigned int type;
    /* A lefedettseget egy vectorban taroltam el,
     * mivel nem tudni elore mekkora lesz.
     * Plusz ebben a vektorban field mutatokat
     * fogunk eltarolni. */
    vector<field*> coverage;
    /* Elforgatas: rot
     * 0 = nincs elforgatas,
     * 1 = 90 fokos elforgatas,
     * 2 = 180 fokos elforgatas,
     * 3 = 270 fokos elforgatas. */
    unsigned int rot;
  public:
    tower();
    tower(string, unsigned int, unsigned int, vector<field*>, unsigned int);
    string getCegazon() {return cegazon;}
    unsigned int getSorszam() {return sorszam;}
    unsigned int getType() {return type;}
    vector<field*> getCoverage() {return coverage;}
    unsigned int getRot() {return rot;}
    tower& setCegazon(string);
    tower& setSorszam(unsigned int);
    tower& setType(unsigned int);
    /* setCoverage et ket modon is meg lehet hivni,
     * vagy egybol egy vektort adunk meg,
     * vagy egy field mutatot,
     * amit majd hozzaadunk a meglevo vektor vegere */
    tower& setCoverage(vector<field*>);
    tower& setCoverage(field*);
    tower& setRot();
    /* a copy const es assignment const-ort itt is deletel-juk */
    tower(const tower&) = delete;
    tower& (const tower&) = delete;
}

class region {
  /* A field-eket regiokba soroljuk,
   * igy konnyen ki lehet majd rajzolni,
   * egy lefedettsegi mapot.
   *
   * ez egy szulo osztaly lesz,
   * a gyerekei lesznek a region_type1,
   * region_type2, region_type3, region_type4, 
   * region_water, region_uncovered */
  protected:
    vector<field*> fields;
    string cegazon;
  public:
    region();
    region(vector<field*>, string);
    vector<field*> getFields() {return fields;}
    string getCegazon() {return cegazon;}
    /* Itt is ket modon lehet meghivni a setFields metodust */
    region& setFields(vector<field*>);
    region& setFields(field*);
    region& setCegazon(string);
    region(const region&) = delete;
    region& (const region&) = delete;
}

/* A region gyerek classjait meg kene irni meg.
 * De akar meg lehet oldani anelkul is.
 * Meg kell beszelni!!! */

#endif
