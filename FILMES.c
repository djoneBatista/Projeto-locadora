#include <stdlib.h>
#include "biblioteca.h"
//=============================================================================//
// Trabalho   3  de  Algoritimos e estruturas de dados       ||
// Nome  :  João Carlos Batista (djone@grad.icmc.usp.br)                 6792197
// Nome  :  Cassiano Olavo C M Santos  (cassiano@grad.icmc.usp.br)       4950651
//==============================================================================//
int main(int argc, char *argv[])
{
FILE *Registro,*indice_primario,*indice_secundario;
char chave[max][50],titulo[max][50],restaurar_chave[max][50],restaurar_titulo[max][50];    
int posicao_chave[max],posicao_titulo[max],contad=0,opcao,returno_da_funcao;
if(criar_arquivo("iprimary.idx","ititle.idx","arquivo_de_dados.txt")==1)// caso nao  exista  reconstroi o arquivo indices
reconstruir_indices();  
carregar_vetor("iprimary.idx","r+b",indice_primario,chave,posicao_chave,&contad);
carregar_vetor("ititle.idx","r+b",indice_secundario,titulo,posicao_titulo,&contad);
         ordenar(contad,chave,posicao_chave);
         ordenar(contad,titulo,posicao_titulo);

do{      printf("\n  ==============MENU PRINCIPAL ===============\n");
         printf("\n 1 Inserir um novo filme no catalogo ");
	     printf("\n 2 Remover um filme a partir da chave primaria.");
	     printf("\n 3 Modificar o campo nota de um filme a partir da chave primaria");
	     printf("\n 4 Buscar filmes ");
         printf("\n 5 Listar todos os filmes no catalogo");
         printf("\n 6 compactar  arquivo ");
	     printf("\n 7 sair \n");
	     printf("\n   opcao : ");
	     scanf("%d",&opcao);
         if(opcao>=0&&opcao<=7)
	     {	   switch(opcao)
			   {	       case 1:	 
                                   gravar_do_arquivo(contad,chave,titulo,posicao_chave,posicao_titulo);
                                   contad++;
				            break; 
				   		    case 2:	
                                    if((procurar(" chave primaria : ",contad,chave,posicao_chave,"NAO"))==0)
				                    {    printf("\n   nao existe este  filme  : ");  
                                    }else
                                    {   remover_registro(returno_da_funcao);
                                    } 
				   		    break;
				   		    case 3:	
					    			if((procurar(" chave primaria : ",contad,chave,posicao_chave,"NAO"))==0)
				                    {    printf("\n   nao existe este  filme  : ");  
                                    }
                                    else
                                    {  
                                         mudar_nota(returno_da_funcao);
                                    } 				 
				   		    break;
			   		        case 4:   
					                submenu(contad,chave,titulo,posicao_chave,posicao_titulo);
				   		    break;
				   		    case 5:	
					                procurar(" catalogos ",contad,titulo,posicao_titulo,"SIM");
				   		    break;
				   		    case 6:
						   		     compactar(contad);
				   		    break;
				   		    default:	
						 	        printf("\n  saindo do sistema  ...  \n"); 
					 	            gravar(indice_primario,indice_secundario,chave,posicao_chave,titulo,posicao_titulo,contad); 
				   		   break;		  
               }
         }
		 else
         {
			   printf("\n  opca invalida  , digite novamente \n");	  
		 }				   
 }while(opcao!=7);
  return 0;
}
