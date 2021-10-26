int makeArrayContinous(int i, int maxI) {                                      
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
  int j = i;
  if (i<0) {minus=true; j=j*-1;}
  if(minus) {
    j = j % (maxI+1);
    if (j == 0) return j;
    return maxI+1-j;
  }
  j = j % (maxI+1);
  return j;
}

