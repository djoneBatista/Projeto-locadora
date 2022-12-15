#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 1000
#define tamanho_do_registo_total 192  

struct filmes   //  entrada de  dados 
{    char codigo_do_filme[6];
     char titulo_em_portugues[50];
     char titulo_original[50];
     char diretor[30];
     char ano_de_lancamento[5];
     char pais[20];
     char nota[2];
     char chave_primaria[6];
}FILMES;
//==========================================================================================================================================
int  inserir(char texto[100],char *variavel)// entrada  de  dados 
{  
	do{
	          printf("\n %s ",texto);
	          fflush(stdin);
		      gets(variavel);
       }while(strlen(variavel)==0); 
      return *variavel;
}
//==========================================================================================================================================
//  carrega as  informacoes  do arquivo  para a  meoria   
int carregar_vetor(char *nome_do_arquivo,char *modo,FILE *pont,char chave[max][50],int posicao[max],int *numero_de_registro)
{           int i=0,contador=0;
            char temporario[max],*codigo,*pos;  
            pont=fopen(nome_do_arquivo,modo);                                 
            fgets(temporario,max,pont); 			
			 while(!feof(pont))
			{     //Enquanto arquivo nÃ£o chegue ao fim  
			       codigo = strtok(temporario,".");  //  os   campos   esta  formatado
			       codigo = strtok(NULL,"|");       //e  esta  com   marcados 
			       pos = strtok(NULL,"|");
		 	       strcpy(chave[i],codigo); 
                   posicao[i]=atoi(pos);             
			       fgets(temporario,max,pont); // vai  pra  proxima linha
			       i++;
                   contador++;
			} 
            *numero_de_registro=contador;    //  quantidade  de dados  que foi carregado    
            fclose(pont);  
   return  chave[max][50],*posicao,*numero_de_registro;    
}
//============================================================================================================================================
//grava  os  dados do registro no arquivo    e  as chaves   correspondente fica na memoria  indices  primario e indices secundario
void gravar_do_arquivo(int numero_de_registro,char chave[max][50],char titulo[max][50],int posicao_do_chave[max],int posicao_do_titulo[max])
{     int i,contador=0,cont1=0,cont=0,tamanho_total,posicao=0,valor;
      FILE *Registro;
      char texto[10][30],temp[max],posicao_do_registro[10],informacao_do_registro[180]; 
      Registro=fopen("arquivo_de_dados.txt","a");                    
      inserir(" Titulo em portugues ",FILMES.titulo_em_portugues); 
      inserir(" Titulo original ",FILMES.titulo_original);
	  inserir(" Diretor ",FILMES.diretor);
	  for(i=0;i<=strlen(FILMES.diretor);i++)
	  {  texto[contador][cont1]=FILMES.diretor[i]; 
	     cont1++; 
	     if(FILMES.diretor[i]==' ')
	     {    texto[contador][cont1]='\0'; 	 
		      contador++;
		      cont1=0;
         }
	  }   
	do{	   inserir(" Ano de lancamento ",FILMES.ano_de_lancamento);
		   if(strlen(FILMES.ano_de_lancamento)!=4)
	       { printf("\n campo com  4  digitos  ,   digite novamente "); }   
   	  }while( strlen(FILMES.ano_de_lancamento)!=4); //  tem que ter exatamente  4 digitos 		     
      for(i=strlen(FILMES.diretor);i!=-1;i--)
	  {   
		temp[cont]=FILMES.diretor[i];
		cont++;
		if(FILMES.diretor[i]==' ')//  pega   so o  sobrenome 
		{
			break; 
		}
	  }				   
     FILMES.codigo_do_filme[0]=temp[cont-2];
	 FILMES.codigo_do_filme[1]=temp[cont-3];  //  gera   o  codigo  
	 FILMES.codigo_do_filme[2]=temp[cont-4];   
	 FILMES.codigo_do_filme[3]=FILMES.ano_de_lancamento[2];
	 FILMES.codigo_do_filme[4]=FILMES.ano_de_lancamento[3];
	  for(i=0;i<4;i++)   
	  {   
	      FILMES.codigo_do_filme[i]=toupper( FILMES.codigo_do_filme[i]); //  forma  canonica 
      }   
	  
   	    inserir(" Pais ",FILMES.pais);
		do{   inserir(" Nota ",FILMES.nota); 
			 if(strlen(FILMES.nota)!=1)
		     {
			   printf("\n campo com  1  digitos  ,   digite novamente ");  
			 }
		  }while(strlen(FILMES.nota)!=1);   
                for(i=0;i<=4;i++)
	           {informacao_do_registro[i]= FILMES.codigo_do_filme[i];  }
	            strcpy(chave[numero_de_registro],informacao_do_registro);
	            posicao_do_chave[numero_de_registro]=numero_de_registro;
	            posicao_do_titulo[numero_de_registro]=numero_de_registro;
                strcat(informacao_do_registro,"@");   
                strcat(informacao_do_registro,FILMES.titulo_em_portugues); 
                strcpy(titulo[numero_de_registro],FILMES.titulo_em_portugues);
                for(i=0;i<=strlen(FILMES.titulo_em_portugues);i++)  
                {  titulo[numero_de_registro][i]=toupper(titulo[numero_de_registro][i]);                 }//  forma  canonica    
                do{ strcat(titulo[numero_de_registro]," ");}while(strlen(titulo[numero_de_registro])!=23);
                strcat(informacao_do_registro,"@");   
                strcat(informacao_do_registro,FILMES.titulo_original); 
                strcat(informacao_do_registro,"@");   
                strcat(informacao_do_registro,texto[0]); 
                strcat(informacao_do_registro,",");   
                strcat(informacao_do_registro,texto[1]); 
                strcat(informacao_do_registro,"@");   
                strcat(informacao_do_registro,FILMES.ano_de_lancamento); 
                strcat(informacao_do_registro,"@");   
                strcat(informacao_do_registro,FILMES.pais);   
                strcat(informacao_do_registro,"@");     
                strcat(informacao_do_registro,FILMES.nota);   
                strcat(informacao_do_registro,"@");   
         do{    strcat(informacao_do_registro,"#");    }while(strlen(informacao_do_registro)!=tamanho_do_registo_total);
            fprintf(Registro,"%s",informacao_do_registro); 	
            fclose(Registro); 						
}
//==========================================================================================================================================
//  recebe o  vetor indices primario  e  indices segundario  e  ordena  
void  ordenar(int  tamanho,char chave[max][50],int posicao[max] )
{  int i,j,temporario;
   char* temp = (char*) malloc(50*sizeof(char)); 
  for(i = 1; i < tamanho; i++)
  { 
      for (j = 0; j < tamanho -1 ; j++)
      {
             if(strcmp(chave[j],chave[j+1]) > 0)
             {   
                  strcpy(temp,chave[j]);
                  temporario= posicao[j];
                  strcpy(chave[j],chave[j+1]);
                  posicao[j]=posicao[j+1];
                  strcpy(chave[j+1],temp); 
                  posicao[j+1]=temporario;                             
            }
      }
  } 
      free(temp);     
}
//==========================================================================================================================================
//  descarrega   as  informacoes  que estao  no  vetores   para   os  arquivos  indices primario  e  indices segundario
int gravar(FILE *p1,FILE *p2,char chave[max][50],int posicao_chave[max],char titulo[max][50],int posicao_titulo[max],int tamanho)
{   int i,k;
    p1=fopen("iprimary.idx","r+b");  
    p2=fopen("ititle.idx","r+b");  
    for(i=0;i<=tamanho;i++)
    {  if(strlen(chave[i])>1)          
       fprintf(p1," .%s|%d|\n",chave[i],posicao_chave[i]); 
    }  
    for(i=0;i<=tamanho;i++)
    {    if(strlen(titulo[i])>1)  
         {            
	           fprintf(p2," .%s|%d|\n",titulo[i],posicao_titulo[i]);  
         }
    }  
      fclose(p1);
      fclose(p2);
}
//==========================================================================================================================================
//verefica se  o arquivo existe  , caso nao exista     cria  um  novo arquivo 
int  criar_arquivo(char *index1,char *index2,char *arquivo_de_registro)
{   FILE *p1,*p2,*p3;  
    if((p1=fopen(index1,"r+b"))==NULL)
    {  
        return 1;      
    }
    else  if((p2=fopen(index2,"r+b"))==NULL)
    { 
        return 1;
    }
    if((p3=fopen(arquivo_de_registro,"r"))==NULL)
    {    p3=fopen(arquivo_de_registro,"w"); 
         fclose(p3);           
    }
}
//==========================================================================================================================================
// recebe a string do  arquivo  , e  imprime  so as  informecoes   do filmes
void tratar_string(char string[tamanho_do_registo_total])
{ int  i,k,linha=0,inicio_da_string=0;
  char registro[11][50],informacoes_do_filmes[11][50];
          strcpy(informacoes_do_filmes[0],"RRN                 : ");
          strcpy(informacoes_do_filmes[1],"Titulo em portugues :");
          strcpy(informacoes_do_filmes[2],"Titulo original     :");
          strcpy(informacoes_do_filmes[3],"Nome                :");
          strcpy(informacoes_do_filmes[4],"Sobrenome           :");
          strcpy(informacoes_do_filmes[5],"Ano de lançamento   :");
          strcpy(informacoes_do_filmes[6],"Pais                :");
          strcpy(informacoes_do_filmes[7],"                     ");
          strcpy(informacoes_do_filmes[8],"Nota                :");
          strcpy(informacoes_do_filmes[9],"_____________________________________________________________");

     for(i=0;i<11;i++)
     for(k=0;k<50;k++)
     registro[i][k]=' ';//  limpa a matriz 
     
     for(i=0;i<strlen(string);i++)
     {  
         if(string[i]=='@'||string[i]==',')
         {   registro[linha][i]='\0';
             linha++;
             inicio_da_string=0;
          }
            if(string[i]!='@'&&string[i]!=',')
            registro[linha][inicio_da_string]=string[i];           
           
            inicio_da_string++;
            if(string[i]=='#')
            break;
     }
        registro[linha][1]=registro[linha-2][51];
        registro[linha-2][51]=' ';
        for(i=0;i<=linha+1;i++)
       {        
            printf("\n %s %s  ",informacoes_do_filmes[i],registro[i]);
       } 
}
//==========================================================================================================================================
//  recebe a nota  que o  usuario quer  mudar  e 
void mudar_a_nota(char *string)
{     int  i,k,linha=0,inicio_da_string=0;
      char registro[11][50],informacoes_do_filmes[11][50];
     for(i=0;i<11;i++)
     for(k=0;k<50;k++)
     registro[i][k]=' ';//  limpa a matriz 
     
     for(i=0;i<strlen(string);i++)
     {  
         if(string[i]=='@'||string[i]==',')//  vai  separando  os   campos 
         {   registro[linha][i]='\0';
             linha++;
             inicio_da_string=0;
          }
            if(string[i]!='@'&&string[i]!=',')//  carrega a  matriz  com as  informacoes do filmes
            registro[linha][inicio_da_string]=string[i];           
           
            inicio_da_string++;
            if(string[i]=='#')
            break;
     }
         registro[linha][1]=registro[linha-2][51];
         registro[linha-2][51]=' ';
        for(i=0;i<=linha;i++)
        {        
            printf("\n%s  ",registro[i]);
        } 
}
//  recebe a posicao  e  vai  direto  na  posicao correto  do  registro  , dentro do arquivo
void  remover_registro(int posicao)
{   FILE *pont;
   char rem[3];
              if(!(pont = fopen("arquivo_de_dados.txt","r+")))
              { 
                 exit(1);
              }
              fseek (pont,posicao*tamanho_do_registo_total,SEEK_CUR);
              strcpy(rem,"*|");
              if(fwrite(&rem,strlen(rem),1,pont) != 1) 
              {
                  printf("Erro na escrita do arquivo!");
                  exit(2); 
             }
              printf("\n removido  \n");
              fclose(pont);
}
//recebe a  posicao  
void localizar(int  posicao)
{  FILE *pf;
   char registro[200];
             if(!(pf = fopen("arquivo_de_dados.txt","r")))
              { 
                 exit(1);
              }
              fseek (pf,posicao*tamanho_do_registo_total,SEEK_CUR);//  vai  direto na  posicao correta do registro
                                               // pois  o  registro  tem  tamanho  fixa
             if(fread(&registro,tamanho_do_registo_total,1,pf) != 1) //le  um bloco  de  dados   do  tamanho 175
             {
                 printf("Erro na leitura do arquivo!");
                 exit(3);
             }
                 tratar_string(registro);//exibe  as  informacoes  do arquivo    
}
//muda  a nota  do registro 
void  mudar_nota(int pos)
{ FILE *pf;
  char  teste[200], registro[200],i,remover[3],nota[2];
  int   opcao,sair=0,contador=0,tamanho=0,posicao=0; 
      
               if(!(pf = fopen("arquivo_de_dados.txt","r")))
              { 
                 exit(1);
              }
             fseek (pf,pos*tamanho_do_registo_total,SEEK_CUR);
             if(fread(&registro,tamanho_do_registo_total,1,pf) != 1) //recupera  este  dado do registro 
             {
                 printf("Erro na leitura do arquivo!");
                 exit(4);
             }
                 for(i=0;i<strlen(registro);i++)
                 {   
                      if(registro[i]=='@'&&registro[i+2]=='@')//localiza  onde esta  a nota 
                      {  
                           break;
                      }
                      posicao=i;//  guarda  esta  posicao 
                 }  
              if(!(pf = fopen("arquivo_de_dados.txt","r+")))
              { 
                 exit(1);
              }
                  tamanho=pos*175+posicao+2;//posiciona  no  ponto  correto do arquivo
                  printf("\n  nova  nota   : ");
                  scanf("%s",nota);
                  fseek (pf,tamanho,SEEK_CUR);// ponto correto  e  
                  fwrite(&nota,strlen(nota),1,pf); //grava  a  nova nota                 
                  fclose(pf);      
      
}
//==========================================================================================================================================
void  buscar_no_arquivo(int  pos)
{   int   opcao,sair=0;
    do{
        system("cls");
	    printf("\n 1 Remover este  registro  ");
	    printf("\n 2 Mudar nota ");
	    printf("\n 3 Voltar  ");
	    printf("\n  opcao  :");
	    scanf("%d",&opcao);
	   if(opcao>=0&&opcao<=3)
	   {
	     switch(opcao)
	     {					   		   
	      case 1:
                  remover_registro(pos);
                  sair=1;  
	     break;
	     case 2:  
                  mudar_nota(pos);                     
                  sair=1; 
	     break;
	     case 3:                 
                  sair=1; 
	     break;
        }
     }
	 else
	 {
	     printf("\n  opca invalida  , digite novamente \n");				   		
	 }
   }while(sair!=1);
}
//==========================================================================================================================================
//reconstrui  os indices    dos  arquivo  de indices primario  e  indices segundario
void reconstruir_indices()
{ char  registro_recuperado[200],titulo_restaurado[20],chave[5];
  FILE *pf,*p1,*p2;
  int i=0,k,j,y,w,contador=0;
    p1=fopen("iprimary.idx","w+b");  
    p2=fopen("ititle.idx","w+b");  
  for(i=0;i<10000;i++)//   while(!feof(pf))   nao  estava funcionando  
  {          contador=0,j=0;
              if(!(pf = fopen("arquivo_de_dados.txt","r")))
              { 
                 exit(1);
              }     
              fseek (pf,i*tamanho_do_registo_total,SEEK_CUR);
              if(fread(&registro_recuperado,tamanho_do_registo_total,1,pf) != 1) // a  condicao  de  parada
              {
                printf("\n  arquivos  de indices restaurados    ");
                i=10000;
              }
              fclose(pf);
              for(w=0;w<20;w++)
               {
                  titulo_restaurado[w]=' ';//  limpa a string
                
               }
             for(k=0;k<200;k++)
             {     
                 if(registro_recuperado[k]=='@')
                 {  
                      contador++;
                  }
                 if(k>5&&contador==1)
                 {      
                     titulo_restaurado[j]=registro_recuperado[k]; 
                      j++;  
                 }
                 
                 if(contador==3)//  as  chaves  estao construidas  
                 k=200;
             } 
               for(w=j;w<strlen(titulo_restaurado);w++)
               {
                  titulo_restaurado[w]=' ';
               }      
                 for(w=0;w<5;w++)
                 {                              
                     chave[w]=registro_recuperado[w];
                 }             
                for(w=0;w<=strlen(titulo_restaurado);w++)  
                {  titulo_restaurado[w]=toupper(titulo_restaurado[w]);                 }//  forma  canonica    
                if(i!=10000)
                {
                   fprintf(p1," .%s|%d|\n",chave,i); 
                   fprintf(p2," .%s|%d|\n",titulo_restaurado,i);
                } 
    }  
    fclose(p1);
    fclose(p2);   
}
//==========================================================================================================================================
//  cria   um novo arquivo  , so com   registro existente   do  antigo  registo  ,  os  marcado  como deletado  nao  copia
void compactar(int quantidade_de_registro)
{  FILE *pf,*compactar;
 char  registro_recuperado[tamanho_do_registo_total];
 int i;
              if(!(compactar = fopen("arquivo_compactado.txt","w")))
              { 
                 exit(1);
              }  
		for(i=0;i<quantidade_de_registro;i++)
		{      if(!(pf = fopen("arquivo_de_dados.txt","r")))
              { 
                 exit(1);
              }  
              fseek (pf,i*tamanho_do_registo_total,SEEK_CUR);
             if(fread(&registro_recuperado,tamanho_do_registo_total,1,pf) != 1) 
             {
                 printf("Erro na leitura do arquivo!");
              
             }
              fclose(pf);
              if(registro_recuperado[0]!='*')
              {
                   fprintf(compactar,"%s",registro_recuperado); 	 
			  }
		}	  
	  
	  fclose(compactar);
}
//==========================================================================================================================================
void  submenu(int contad,char chave[max][50],char titulo[max][50],int posicao_da_chave[max],int posicao_da_titulo[max])

{ int opcao,sair=0,returno,i;
   do{
        system("cls");
        returno=0;
	    printf("\n 1 chave primaria  ");
	    printf("\n 2 titulo em portugues ");
	    printf("\n 3  voltar ");
	    printf("\n   opcao : ");
	    scanf("%d",&opcao);
	   if(opcao>=0&&opcao<=3)
	   {
	     switch(opcao)
	     {
										   		   
	      case 1:	
                 returno=procurar(" chave primaria ",contad,chave,posicao_da_chave,"NAO");
                 if(returno==0)
                 {
                    printf("\n  nao  existe  este  filme  ");
                 }
                 else
                 {
                    buscar_no_arquivo(returno);  
                 }
	     break;
	     case 2:    
                  returno=procurar("titulo em portugues ",contad,titulo,posicao_da_titulo,"NAO");                        
                  if(returno==0)
                  {
                       printf("\n  nao  existe  este  filme  ");
                  }
                  else
                  {
                       buscar_no_arquivo(returno); 
                  } 
	     break;
	     case 3:	
	                 sair=1;
	     break;
       }
     }
	 else
	 {
	     printf("\n  opca invalida  , digite novamente \n");
	     system("cls");						   		
	 }
   }while(sair!=1);

}
//==========================================================================================================================================
//  procura um  registro ,  usando  a chave  primaria do filme  ou   pelo titulo    
//  esta  busca  e  feita  na memoria  
int procurar(char texto[20],int contad,char chave[max][50],int posicao[max],char lista_todos[4])
{
  int existencia_do_filme=0,i,guardar_posicao=0,flag=0;
 char nome[50];
 if(strcmp(lista_todos,"NAO")!=1)
 {
	     printf("\n %s",texto);
	    do{   fflush(stdin);
		      gets(nome);
		                    }while(strlen(nome)==0);
	 for(i=0;i<=strlen(nome);i++)   
	 {   
		nome[i]=toupper(nome[i]);   
	 } 
	 if(strlen(chave[2])>6)
	 {   do{strcat(nome," ");   }while(strlen(nome)!=23);
     }											
	 for(i=0;i<=contad;i++)
	 { 
	      if(strcmp(chave[i],nome)==0)
	      {   existencia_do_filme++;
	          guardar_posicao=posicao[i];
	          localizar(posicao[i]);
	          flag=1;
          }
	 } 
	 
   }
   else
   {  printf("\n====================  %s   ===============================\n",texto);
      for(i=0;i<=contad;i++)
	  {   
	        localizar(posicao[i]); 
	  }   
   } 
      if(flag==1)
      {
         return  guardar_posicao;
      }
      else
      {
        return 0;     
      }
    
  
}
