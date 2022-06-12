# Projet µC


//Olive
Structure DISPLAYLCD qui contient l' ensemble de la conf active de LCD
Utile pour faire des tests dans le programme?


Apres déclaré la structure et initialisé le LCD

    DISPLAYLCD DisplayLcd;
    initLCD(&DisplayLcd);

On allume de LCD

     statusLCD(&DisplayLcd,ON);    //ON ou OFF LCD

On regle l' intensité du LCD

    IntensityLCD(&DisplayLcd,0);  //Between 0 to 15


On crée une matrice de 8 segments à afficher
    uint8_t rondBas[N];
    uint8_t rondHaut[N];
    uint8_t empty[N];
  
On definit les segment à afficher dans la matrice (Cf. define.h pour les noms des segments)
  ArrayDigit(rondBas,4, M1, M0,L0,R0);  
  ArrayDigit(rondHaut,4, M1, M2,L1,R1);
  ArrayDigit(empty,0);

On affiche la matrice sur un digit choisit: Numéro de digit de 1 à 4

    DisplayArrayDigit(&DisplayLcd, 1, rondBas);  
    DisplayArrayDigit(&DisplayLcd, 2, rondHaut); 
    DisplayArrayDigit(&DisplayLcd, 3, empty);



