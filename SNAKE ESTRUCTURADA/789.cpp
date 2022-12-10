#include <allegro.h>
#include <iostream>
#include <time.h>
#define ALTO  480
#define ANCHO 640
void play();
int respBuena(int num1,int num2){
	
	int res=num1*num2;
	return res;
}
int respMala(int num1,int num2){
	int mal=(num1+(rand()%10)+1)*(num2+(rand()%10)+1);
	return mal;
} 
int puntos;
 
BITMAP *buffer;
class fruta
{
public:
    int x;
    int y;

public:
    fruta();
    void pinta(int x,int y);
    
};
fruta::fruta(){
    x=rand()%(ANCHO/20);
    y=rand()%(ALTO/20);
}
void fruta::pinta(int x,int y){
    
    rectfill(buffer, x*20, y*20, (x*20)+20, (y*20)+20, 0xFF0000);
   
}
class gusano{
   public:
   	  
      int tam;
      bool bloquea( int _x, int _y);
      
   public:
      bool gameover;
      int dir;    
      fruta cuerpo[100];
      gusano();
      bool choca();       
      void pinta();
      void teclas();
      void mueve();
      bool come(fruta comida);
      int tami();
      
};
 
 
 // Inicializa al gusano
gusano::gusano(){
   tam = 3;
   dir=1;
   bool gameover=false;
   int x = ANCHO/40;
   int y = ALTO/40;   
   for ( int c = 0; c < tam; c++){
       cuerpo[c].x = x;
       cuerpo[c].y = y+c;
   }           
};
 
// funcion para obtener el tamaño del gusano
int gusano::tami(){
    return tam;
};
  
// comprueba si el gusano choca con el mismo
bool gusano::choca(){ 
    int posx, posy;
    posx = cuerpo[0].x;
    posy = cuerpo[0].y;
    if ( dir == 1) posy = cuerpo[0].y-1;
    if ( dir == 2) posy = cuerpo[0].y+1;
    if ( dir == 3) posx = cuerpo[0].x-1;
    if ( dir == 4) posx = cuerpo[0].x+1;
 
    if ( posx < -5 ) return true;    
    if ( posy < -5 ) return true;
    if ( posx > (ANCHO/20)-1 ) return true;
    if ( posy > (ALTO/20)-1 ) return true;    
     
    for ( int c = 0; c < tam; c++){
        if (posx == cuerpo[c].x && +
            posy == cuerpo[c].y ) return true;        
    };     
    return false;
};
  
// pinta el gusano por pantalla
void gusano::pinta(){
   int x,y;
   for ( int c = tam-1; c >= 0; c--){
       x = 20 * cuerpo[c].x;
       y = 20 * cuerpo[c].y;
       if ( c == 0 ){
           rectfill(buffer, x, y, x+15, y+15, 0xFFFFFF);         
       }else{     
           rectfill(buffer, x, y, x+15, y+15, 0xFFFFFF);
       }
   }
};
 
// controla las teclas para mover al gusano, dando un valor a dir, segun la direccion que se ha pulsado.
void gusano::teclas(){
     if ( key[KEY_UP] ){
          dir = 1;
     }
     if ( key[KEY_DOWN] ){
          dir = 2;
     }
     if ( key[KEY_LEFT] ){
          dir = 3;
     }
     if ( key[KEY_RIGHT] ){
          dir = 4;
     }               
};
// mueve al gusano, la ultima parte toma el valor de su parte anterior, y asi hasta llegar 
// a la cabeza  y la cabeza toma un nuevo valor segun la direccion.
void gusano::mueve(){
   if ( !choca() ){
      
     for ( int c = tam-1; c > 0 ; c--){
         cuerpo[c].x = cuerpo[c-1].x;
         cuerpo[c].y = cuerpo[c-1].y;              
     }
     if ( dir == 1 ){
 
          cuerpo[0].y -= 1; 
     }
     if ( dir == 2 ){
 
          cuerpo[0].y += 1; 
     }
     if ( dir == 3 ){
 
          cuerpo[0].x -= 1; 
     }
     if ( dir == 4 ){
 
          cuerpo[0].x += 1; 
     }
     // colocamos los limites
     if ( cuerpo[0].x < 0 ) cuerpo[0].x=0;
     if ( cuerpo[0].x > (ANCHO/20)-1 ) cuerpo[0].x=(ANCHO/20)-1;
     if ( cuerpo[0].y < 0 ) cuerpo[0].y=0;
     if ( cuerpo[0].y > (ALTO/20)-1 ) cuerpo[0].y=(ALTO/20)-1;       
      
   }
};
 
// se encarga de comprobar si ha llegado a la comida, y aumenta su tamaño
bool gusano::come(fruta comida){
     if  ( comida.x == cuerpo[0].x && comida.y == cuerpo[0].y ){
          tam++;
          return true;          
     }
     return false;
}
  


int main() 
{    
    allegro_init();
    install_keyboard();
    install_mouse(); 
    srand (time(NULL));
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0);

	int fin=0;
	BITMAP *buffer =create_bitmap(ANCHO, ALTO);
    BITMAP *fondo1 =load_bitmap("img/fondo1.bmp",NULL);
    BITMAP *fondo2 =load_bitmap("img/fondo2.bmp",NULL);
    BITMAP *fondo3 =load_bitmap("img/fondo3.bmp",NULL);
    BITMAP *cursor =load_bitmap("img/cursor2.bmp",NULL);
	blit(buffer,screen,0,0,0,0,ANCHO, ALTO);  
	while(fin==0){
		if(mouse_x>244&&mouse_x<391&&
           mouse_y>113&&mouse_y<162){
           	blit(fondo2,screen,0,0,0,0,ANCHO, ALTO);
           	if(mouse_b & 1){
           		fin=1;
           		
			   }
		   }
		if(mouse_x>256&&mouse_x<379&&
           mouse_y>211&&mouse_y<251){
           	blit(fondo3,screen,0,0,0,0,ANCHO, ALTO);
           	if(mouse_b & 1){
           		return 0;
           		
			   }
		   }else{
		   	blit(fondo1,screen,0,0,0,0,ANCHO, ALTO);
		   }
	blit(cursor,screen,0,0,mouse_x,mouse_y,13,22); 
		
	}
	destroy_bitmap(buffer);
    play(); 
    return 0;
}
END_OF_MAIN();
void play(){
	char c1[10]; 
    
    int num1;
	int num2;
    int a;
    int b;
    puntos = 0;
    gusano serpiente;
    fruta comida,comida2; 
    buffer = create_bitmap(ANCHO, ALTO);
    comida.x = rand()%(ANCHO/20);
    comida.y = rand()%(ALTO/20); 
    comida2.x = rand()%(ANCHO/20);
    comida2.y = rand()%(ALTO/20); 
    num1=(rand()%10)+1;
  	num2=(rand()%10)+1;
 	a=respBuena(num1,num2);
    b=respMala(num1,num2);
    while ( serpiente.gameover!=true )
    {
        clear_to_color(buffer, 0x000000);  
        serpiente.teclas();
        serpiente.mueve();
        
        comida.pinta(comida.x,comida.y);
 		comida2.pinta(comida2.x,comida2.y);       
        serpiente.pinta();
        textout_ex(buffer, font, itoa(a,c1,10), comida.x*20, comida.y*20,  0xfff000, -1); 
        textout_ex(buffer, font, itoa(b,c1,10), comida2.x*20, comida2.y*20,  0xfff000, -1);
        textout_ex(buffer, font, itoa(num1,c1,10), 245, ALTO-25,  0xfff000, -1);
        textout_ex(buffer, font, "x", 260, ALTO-25,  0xfff000, -1); 
        textout_ex(buffer, font, itoa(num2,c1,10), 270, ALTO-25,  0xfff000, -1);
        if ( serpiente.come(comida) ){
            comida.x = rand()%(ANCHO/20);
            comida.y = rand()%(ALTO/20);
            comida2.x = rand()%(ANCHO/20);
            comida2.y = rand()%(ALTO/20);
            num1=(rand()%10)+1;
		  	num2=(rand()%10)+1;
		 	a=respBuena(num1,num2);
		    b=respMala(num1,num2);
		    textout_ex(buffer, font, itoa(a,c1,10), comida.x*20, comida.y*20,  0xfff000, -1); 
        	textout_ex(buffer, font, itoa(b,c1,10), comida2.x*20, comida2.y*20,  0xfff000, -1);
            
            puntos+=5;
        }
        if ( serpiente.come(comida2) ){
            comida2.x = rand()%(ANCHO/20);
            comida2.y = rand()%(ALTO/20);
            comida.x = rand()%(ANCHO/20);
            comida.y = rand()%(ALTO/20);
            num1=(rand()%10)+1;
		  	num2=(rand()%10)+1;
		 	a=respBuena(num1,num2);
		    b=respMala(num1,num2);
		    textout_ex(buffer, font, itoa(a,c1,10), comida.x*20, comida.y*20,  0xfff000, -1); 
        	textout_ex(buffer, font, itoa(b,c1,10), comida2.x*20, comida2.y*20,  0xfff000, -1);
            
            
            puntos-=5;
        }
        if (serpiente.choca()||puntos<0)
        {
            serpiente.gameover=true;
           
           
        }
        
        textout_ex(buffer, font, "Tamano:", 25, ALTO-35,  0xfff000, -1);
        textout_ex(buffer, font, itoa(serpiente.tami(),c1,10), 90, ALTO-35,  0xfff000, -1);        
        textout_ex(buffer, font, "Puntos:", 25, ALTO-25,  0xfff000, -1);
        textout_ex(buffer, font, itoa(puntos,c1,10), 90, ALTO-25,  0xfff000, -1);
        textout_ex(buffer, font, "!DEBES COMER LA RESPUESTA CORRECTA!", 220, ALTO-35,  0xfff000, -1); 
        
         
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
        rest(100);
    }
     
     
    destroy_bitmap(buffer);
}
