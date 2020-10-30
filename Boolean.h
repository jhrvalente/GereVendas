#ifndef Boolean_h 
#define Boolean_h

#define True 1
#define False 0

typedef int bool;
typedef struct bln* Boolean;

/*Inicia a estrutura Boolean.O valor lógico é sempre inicializado como False*/
Boolean initBool(void);
/*Devolve o valor lógico guardado na estrutura Boolean*/
bool getBool(Boolean);
/*Permite alterar o valor lógico guardado pela estrutura Boolean*/
Boolean setBool(Boolean ,bool );
/*Liberta a memória ocupada pela estrutura Boolean*/
void removeBoolean(Boolean );

#endif
