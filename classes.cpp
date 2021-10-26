#include "classes.hpp"

field::field() {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  t = NULL;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  population = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  special = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  water = true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  for(unsigned int i = 0; neighbours; i++) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    neighbours[i] = NULL;                                                                                                                                     
  }                                                                                                                                                          
  for(unsigned int i = 0; i < sizeof(coverageType); i++) {                                                                                                    
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
  for(unsigned int i = 0; i < 4; i++) {                                                                                                                       
    neighbours[i] = NULL;                                                                                                                                     
  }                                                                                                                 
  for(unsigned int i = 0; i < sizeof(coverageType); i++) {                                        
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
tower::tower(unsigned int ssz, unsigned int t, vector<field*> c, unsigned short r) {                                                                          
  sorszam = ssz;                                                                                                                                              
  type = t;                                                                                                                                                   
  coverage = c;                                                                                                                                               
  rot = r;                                                                                                                                                    
}                                                                                                                                                             
tower& tower::setCegazon(string ca) {cegazon = ca; return *this;}                                                                                             
tower& tower::setSorszam(unsigned int ssz) {sorszam = ssz; return *this;}                                                                                     
tower& tower::setType(unsigned int t) {type = t; return *this;}                                                                                               
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
  for (int i = 0; i < 4; i++) regionType[i] = false;                                                                                                          
  water = false;                                                                                                                                              
  uncovered = true;                                                                                                                                           
}                                                                                                                                                             
region::region(field* f) {                                                                                                                                    
  fields.push_back(f);                                                                                                                                        
  uncovered = false;                                                                                                                                          
}                                                                                                                                                             
region& region::setFields(vector<field*> v) {fields=v;return *this;}                                                                                          
region& region::setFields(field* f) {fields.push_back(f); return *this;}                                                                                      
region& region::setCegazon(string ca) {cegazon = ca; return *this;}                                                                                           
region::~region() {}                                                                            
