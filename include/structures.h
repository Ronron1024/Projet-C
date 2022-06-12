
typedef struct {
  
  uint8_t id;           //id digit, 1 to 4
  uint8_t val;          //for display

} DIGIT;



typedef struct {
  
  int mode;            //status ON/OFF
  int intensity;        //Between 0, 15
  DIGIT digit[4];         
  
} DISPLAYLCD;


