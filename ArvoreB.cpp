
/* 

       2014

Deivid Goes Farias Marinho          -       deividgfmarinho@gmail.com



  �rvore B com conte�do de somente valores inteiros => fins did�ticos

  
*/



#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
using namespace std;




////////////////////////////////////////////////////////////////
class NoDaArvore  
      {
      private:
          bool ehFolha;                // indica se o no � uma folha   
          int totalDeChaves;           // total de chaves presentes no no
          int ordem;                   // ordem do no
          int *chaves;                 // lista com as chaves do no
          NoDaArvore* *filhos;         // lista com os filhos do no 
          NoDaArvore* ascendente;      // no ascendente 
          NoDaArvore* irmaoAEsquerda;  // no irm�o � esquerda
          NoDaArvore* irmaoADireita;   // no irm�o � direita      
      public:


     /**
        Construtor
     */ 
     bool cria(int ordemValue, bool ehfolha)
       {  
          ehFolha = ehfolha;
          totalDeChaves = 0; 
          ordem = ordemValue;        
          ascendente = NULL;
          irmaoAEsquerda = NULL;
          irmaoADireita = NULL;
           
          // No caso aloca "um espa�o" de mem�ria a mais para servir como �rea de overflow
          // Na pr�tica:  n�mero de chaves = ordem - 1
          //              n�mero de filhos = ordem
          chaves = (int *) malloc((ordem) * sizeof(int)); 
          filhos = ehfolha ? NULL : (NoDaArvore**) malloc((ordem + 1) * sizeof(NoDaArvore*)); 
          
          if(chaves == NULL || (!ehfolha && filhos == NULL))
              return false;        
          
          
          // Inicializa as posi��es dos ponteiros filhos para apontar para NULL
          if(filhos != NULL)
              for(int i=0; i < ordem + 1; i++)
                  filhos[i] = NULL;   
          
          return true;               
       }
       
//---------------------------------------------------------------------------------------------------------
     
     /**
        Destrutor
     */ 
     void destroi()
       {  
           ascendente = NULL;
           irmaoAEsquerda = NULL;
           irmaoADireita = NULL;
                 
           if(!ehFolha)      
               // Tira da mem�ria cada ponteiro filho      
              for(int i = 0; i < totalDeChaves + 1; i++)
                free(filhos[i]);	
          
          // Limpa os vetores da mem�ria       
          free(filhos);
          free(chaves);        
       }  
//---------------------------------------------------------------------------------------------------------
       
     /**
        Retorna true se este no � uma folha
     */  
     bool ehfolha(){
         return ehFolha;     
     }  
     
//---------------------------------------------------------------------------------------------------------           
     
     /**
        Retorna o total de chaves do no (TOTAL DE FILHOS = TOTAL DE CHAVES + 1)
     */
     int getNumeroDeChaves()
     {
        return totalDeChaves;
     }     
     
//---------------------------------------------------------------------------------------------------------
         
     /**
        Retorna o ascendente do no
     */
     NoDaArvore* getAscendente(){
         return ascendente;     
     }  
     
//---------------------------------------------------------------------------------------------------------
       
     /**
        Retorna o irm�o � esquerda do no
     */  
     NoDaArvore* getIrmaoAEsquerda(){
         return irmaoAEsquerda;     
     }             

//---------------------------------------------------------------------------------------------------------
       
     /**
        Retorna o irm�o � direita do no
     */   
     NoDaArvore* getIrmaoADireita(){
         return irmaoADireita;     
     }
     
//---------------------------------------------------------------------------------------------------------
       
     /**
        Seta o ascendente do no
     */   
     void setAscendente(NoDaArvore* as){
         ascendente = as;     
     }     
     
     
//---------------------------------------------------------------------------------------------------------
       
     /**
        Seta o irm�o � esquerda do no
     */   
     void setIrmaoAEsquerda(NoDaArvore* iE){
         irmaoAEsquerda = iE;     
     }     

//---------------------------------------------------------------------------------------------------------
       
     /**
        Seta o irm�o � direita do no
     */   
     void setIrmaoADireita(NoDaArvore* iD){
         irmaoADireita = iD; 
     }      
     
     
// --------------------------------------------------------------------------------------------------------
      
     /**
        Retorna o no filho na posi��o informada. Caso a posi��o seja inv�lida ou o no � uma folha, retorna NULL
     */   
     NoDaArvore* getFilhoDaPosicao(int posicao){

         if(!ehFolha && posicao >= 0 && posicao < totalDeChaves + 1)
             return filhos[posicao];
             
         return NULL;
         
     }
     
//---------------------------------------------------------------------------------------------------------
     
     /**
        Retorna a chave na posi��o informada. Caso a posi��o seja inv�lida, retorna -1
     */
     int getChaveDaPosicao(int posicao){
         
         if(posicao >= 0 && posicao < totalDeChaves)
             return chaves[posicao];
             
         return -1;
         
     } 
 
//-----------------------------------------------------------------------------------------------------------
      
     /**
        Retorna a posi��o da chave no no. Se o no corrente n�o a contiver, retorna -1
     */
     int getPosicaoDaChave(int chave){
            
        for(int i = 0; i < totalDeChaves; i++){
           if(chave == chaves[i])
               return i;
        }
        
        return -1;
         
     }  
     
//-----------------------------------------------------------------------------------------------------------
      
     /**
        Retorna a posi��o do no filho. Se o no corrente n�o o contiver, retorna -1
     */
     int getPosicaoDoFilho(NoDaArvore* no){
        
        if(!ehFolha){
            for(int i = 0; i < totalDeChaves + 1; i++){
              if(filhos[i] == no)
                   return i;
            }
		}
        
        return -1;
         
     }  
     
     
     
 
     
    /* INSER��O */
          
//---------------------------------------------------------------------------------------------------------
      
     /**
        Adiciona a chave informada na posi��o informada.
     */
     void adicionaChaveNaPosicao(int chave, int posicao){
        
        // Verifica se a posi��o � v�lida para o vetor de chaves [0 ... ordem -1]  
        if(posicao >= 0 && posicao < ordem){  
          
            // Atualiza o contador de chaves
            totalDeChaves++;
            
            // Desloca os elementos para a direita, at� a posi��o informada
            for(int i = (totalDeChaves - 1); i > posicao; i--)
               chaves[i] = chaves[i - 1];
              
            chaves[posicao] = chave;   
            
        }   
        
     }
     
//---------------------------------------------------------------------------------------------------------     

     /**
        Adiciona a chave informada e retorna a posi��o que ela foi colocada
     */
     int adicionaChave(int chave){
        
        // Busca a posi��o correta para inserir a chave
        int posicao = getPosicaoParaANovaChave(chave); 
        
        adicionaChaveNaPosicao(chave, posicao);
        
        return posicao;
         
     } 
 
//---------------------------------------------------------------------------------------------------------     
     
     /**
        Substitue o valor da chave que estava na posi��o informada (se ela for v�lida) pelo valor informado 
     */
     void substitueChaveNaPosicao(int chave, int posicao){
         
         if(posicao >= 0 && posicao < totalDeChaves)
             // Simplesmente sobrep�e o novo valor
             chaves[posicao] = chave;
              
     }
     
     
     
//---------------------------------------------------------------------------------------------------------

     /**
        Adiciona o filho na posi��o informada
        * no : no que vai ser adicionado como filho
        * posicao : posi��o que o filho vai ser adicionada na lista de ponteiros
     */
     void adicionaFilho(NoDaArvore* no, int posicao){
        
        // Se o no for nulo ou a posi��o informada for inv�lida [0 ... ordem], n�o insere!
        if(filhos == NULL || no == NULL || posicao < 0 || posicao > ordem)
            return; 
        
        // Ajusta os ponteiros dos irm�os
        NoDaArvore* p = posicao > 0 ? filhos[posicao - 1] : NULL; // pega o elemento da posi��o anterior � informada
        
        no->setIrmaoAEsquerda(p); 
        
        if(p != NULL)
            p->setIrmaoADireita(no);  // se este elemento existir, seta o seu novo irm�o � direita
        
        p = posicao < totalDeChaves + 1 ? filhos[posicao] : NULL; // pega o elemento da posi��o posterior � que vai ser inserida
        
        no->setIrmaoADireita(p);  // seta o novo irm�o � direita (que pode ser nulo)
        
        if(p != NULL)
            p->setIrmaoAEsquerda(no); // se este elemento existir, seta o seu novo irm�o � direita   
        
        
        p = NULL;
		
		// Desloca os elementos para a direita, at� a posi��o informada
        for(int i = totalDeChaves; i > posicao; i--)
           filhos[i] = filhos[i - 1]; 
   
        // Guarda o endere�o do conte�do do no  
        filhos[posicao] = no;     
     } 
     
     
     
//--------------------------------------------------------------------------------------------------------- 

     /**
        Divide os chaves a partir do teto, e retorna o vetor com as chaves que foram excluidas desse no
        
        Observa��o: No processo de divis�o, � necess�rio chamar o m�todo dividePonteiros() antes, 
                    pois o divideChaves() vai alterar de vez o total de elementos do no
     */
     int* divideChaves()
     {  
        int teto = (int) ordem / 2; // pega a parte inteira da divis�o
        
        // Se a ordem for um n�mero impar, arredonda o n�mero "para cima"
        if(ordem % 2 != 0)
            teto++;
        
        int *chavesSeparadas;
        chavesSeparadas = (int *) malloc((totalDeChaves - teto) * sizeof(int));
        
        for(int i = teto; i < totalDeChaves; i++){
           chavesSeparadas[i - teto] = chaves[i];
           chaves[i] = 0;
        }
        
        totalDeChaves = teto;
        
        return chavesSeparadas;
     }  
     
//--------------------------------------------------------------------------------------------------------- 
          
     /**
        Divide os ponteiros a partir do teto, e retorna o vetor com os ponteiros que foram excluidos desse no
        
        Observa��o: No processo de divis�o do no, esse m�todo deve ser chamado antes do divideChaves(),
                    pois este �ltimo vai alterar de vez o total de elementos do no
     */
     NoDaArvore** divideFilhos()
     {  
        // Se for uma folha => n�o possui filhos         
        if(ehFolha)
            return NULL;        
                        
        int teto = (int) ordem / 2;
        
        // Se for um n�mero impar, arredonda o n�mero "para cima"
        if(ordem % 2 != 0)
            teto++;
        
        NoDaArvore* *filhosSeparados;
        filhosSeparados = (NoDaArvore **) malloc((totalDeChaves + 1 - teto) * sizeof(NoDaArvore*));
        
        // O primeiro filho da lista que vai ser retirada do no n�o ter� mais irm�o � esquerda 
        filhos[teto]->setIrmaoAEsquerda(NULL);
        
        // Guarda os ponteiros na nova lista criada e seta o elemento daquela posi��o para NULL
        for(int i = teto; i < totalDeChaves + 1; i++){
           filhosSeparados[i - teto] = filhos[i];
		   filhosSeparados[i - teto]->setAscendente(NULL);
           filhos[i] = NULL; 
        }
        
        // O filho que estava a esquerda do primeiro retirado agora n�o possui mais irm�o � direita
        filhos[teto - 1]->setIrmaoADireita(NULL);
        
        return filhosSeparados;
     }  
     
     
     /* FIM - INSER��O */   
       
     
     
     
     /* REMO��O */
     
//---------------------------------------------------------------------------------------------------------
           
     /**
        Retira o �ltimo ponteiro da lista de filhos e o retorna
     */
     NoDaArvore* retiraUltimoFilho()
     {                  
        return retiraFilhoDaPosicao(totalDeChaves);
     }
     
//---------------------------------------------------------------------------------------------------------           
      
     /**
        Retira o ponteiro ao filho da lista da posi��o informada 
        (deslocando todos os outros para a esquerda) e o retorna
     */
     NoDaArvore* retiraFilhoDaPosicao(int posicao)
     {  
        // Verifica se de fato possui filhos e se a posi��o informada � v�lida       
        if(!ehFolha && posicao >= 0 && posicao < totalDeChaves + 1){ 
                           
            NoDaArvore* p = filhos[posicao];
            
			if(posicao > 0)
				filhos[posicao - 1]->setIrmaoADireita(p->getIrmaoADireita());
			
			if(posicao < totalDeChaves)
				filhos[posicao + 1]->setIrmaoAEsquerda(p->getIrmaoAEsquerda());
			
			
			// Seta os ponteiros aos irm�os e ao ascendente para nulo, j� que este ser� retirado da lista
            p->setAscendente(NULL);
            p->setIrmaoAEsquerda(NULL);
            p->setIrmaoADireita(NULL);
			
			
            // A partir da posi��o, desloca os elementos para a esquerda, sobrepondo as posi��es
            for(int i = posicao; i < totalDeChaves; i++)
                filhos[i] = filhos[i + 1];
            

            // Como todos os elementos foram deslocados para a esquerda, a �ltima posi��o v�lida
            // ficou com um elemento, que � exatamente o que deve ser retirado
            filhos[totalDeChaves] = NULL;
            
            
            //pAux = NULL;
            
            return p;
        }
        
        return NULL;
     }     
     
//---------------------------------------------------------------------------------------------------------           
     
     /**
        Retira o primeiro elemento da lista de filhos 
        (deslocando todos os outros para a esquerda) e o retorna
     */
     NoDaArvore* retiraPrimeiroFilho()
     {          
        return retiraFilhoDaPosicao(0);
     }      
     
//---------------------------------------------------------------------------------------------------------           
      
     /**
        Retira o �ltimo elemento da lista e o retorna
     */
     int retiraUltimaChave()
     {                  
        return retiraChaveDaPosicao(totalDeChaves - 1);
     }
     
//---------------------------------------------------------------------------------------------------------           
     
     /**
        Retira o elemento da lista da posi��o informada 
        (deslocando todos os outros para a esquerda) e o retorna
     */
     int retiraChaveDaPosicao(int posicao)
     {  
        if(posicao >= 0 && posicao < totalDeChaves){   
		
            int chave = chaves[posicao];
            
            for(int i = posicao; i < totalDeChaves - 1; i++)
                chaves[i] = chaves[i + 1];
            
            chaves[totalDeChaves - 1] = 0;
            
            totalDeChaves--;
            
            return chave;
        }
        
        return -1;
     }     
     
//---------------------------------------------------------------------------------------------------------           
     
     /**
        Retira o primeiro elemento da lista 
        (deslocando todos os outros para a esquerda) e o retorna
     */
     int retiraPrimeiraChave()
     {          
        return retiraChaveDaPosicao(0);
     }
     
//--------------------------------------------------------------------------------------------------------- 
     
     /**
        Remove o ponteiro para o no filho da posi��o informada
     */
     void removeFilhoDaPosicao(int posicao){
        NoDaArvore* p = retiraFilhoDaPosicao(posicao);     
        
		if(p != NULL)
			free(p);   
     }
     

//---------------------------------------------------------------------------------------------------------
     
     /**
        Remove a chave da posi��o informada
     */
     void removeChaveDaPosicao(int posicao){
        
        int chave = retiraChaveDaPosicao(posicao);
        
        chave = 0;
     }
     
//---------------------------------------------------------------------------------------------------------  
   
     /**
        Remove a chave informada retorna a posi��o que ela se encontrava
     */
     int removeChave(int chave){
        
        int posicao = getPosicaoDaChave(chave); 
        
        removeChaveDaPosicao(posicao);
        
        return posicao;
         
     }  
     
     
     /* FIM - REMO��O */ 
     
     
     
     
     
     /* BUSCA E VERIFICA��O */
         
     /**
        Busca a posi��o adequada na lista de chaves que a nova chave seria inserida
     */
     int getPosicaoParaANovaChave(int chave)
     {  
        int pos = 0;
        
        for(int i = 0; i < totalDeChaves; i++){
           if(chave < chaves[i])
               break;
           else
               pos = i + 1;
        }
        
        return pos;
     }     

//---------------------------------------------------------------------------------------------------------

     /**
        Verifica se o no atual cont�m o no informado como filho
     */
     bool contemFilho(NoDaArvore* no){
         
         // Se for uma folha => N�o possui filhos
         if(ehFolha || no == NULL)
             return false;
         
         // Percorre a lista de ponteiros e busca a igualdade entre os objetos
         for(int i = 0; i < totalDeChaves + 1; i++)
             if(filhos[i] == no)
                 return true;
         
         return false;           
     }
     
//---------------------------------------------------------------------------------------------------------
 
     /**
        Verifica se o no atual cont�m a chave informada
     */
     bool contemChave(int chave){
         
         for(int i = 0; i < totalDeChaves; i++)
             if(chaves[i] == chave)
                 return true;
         
         return false;            
     }    
     
//---------------------------------------------------------------------------------------------------------

     /**
        Retorna o filho ao qual deve ser inserido a chave
		Retorna NULL se for uma folha.
     */
     NoDaArvore* getProximoNoParaAChave(int chave){
         
         if(ehFolha)
             return NULL;
         
         for(int i = 0; i < totalDeChaves; i++){
             if(chave < chaves[i])
                 return filhos[i];   
                         
         }       
         
         return filhos[totalDeChaves];   
     } 
     
     
     /* FIM - BUSCA E VERIFICA��O */  

                  
//---------------------------------------------------------------------------------------------------------
     }; // fim da classe NoDaArvore
/////////////////////////////////////////////////////////////////////// 



 
 
     
     
     
     
     
     // CLASSE DA �RVORE B
//---------------------------------------------------------------------------------------------------------------    
     class ArvoreB
      {
      private:
              NoDaArvore* raiz;         // primeiro n� da �rvore 
              int ordem;
              int totalChaves;
//---------------------------------------------------------------------------------------------------------------
     
     
     
     /* ** M�TODO PRIVADOS (ABSTRA��O) ** */

//---------------------------------------------------------------------------------------------------------------
     
     /**
        Busca no(s) irm�o(s) do no se possue(m) mais chaves que o m�nimo permitido [teto - 1]
        Se possuir, o retorna. Sen�o, retorna NULL.
     */
     NoDaArvore* getIrmaoComMaisChavesQueOMinimo(NoDaArvore* no, int teto){
         
         NoDaArvore* irmao = no->getIrmaoAEsquerda();
            
         // A preferencia � o no pela ESQUERDA
         if(irmao != NULL && irmao->getNumeroDeChaves() > teto - 1)
             return irmao;
         
         // Se n�o tiver no da esquerda, pega o da direita
         irmao = no->getIrmaoADireita();
         
         if(irmao != NULL && irmao->getNumeroDeChaves() > teto - 1)
             return irmao;
         
         irmao = NULL;
             
         // Sen�o tiver em nenhum dos dois, retorna null    
         return NULL;  
                
     }
     
//---------------------------------------------------------------------------------------------------------------
     
     /** Podem n�o ser os filhos diretamente, mas sim o filho mas a direita 
         do filho a esquerda ou o filho mais a esquerda do filho a direita. 
         Se nenhum dos dois possui mais chaves que o m�nimo,  
         retorna o da extrema direita (do filho a esquerda)
     
         * chave : chave do no que deseja fazer a busca do filho extremo
         * no : no que cont�m a chave informada
         * teto : calculado a partir da ordem
         * nivelAbaixoDoNo: retorna por esse par�metro qual o n�vel que se 
                              encontra o no extremo a partir do no informado
     */
     NoDaArvore* getFilhoComMaisChavesQueOMinimo(int chave, NoDaArvore* no, int teto, int *nivelAbaixoDoNo){
         
         *nivelAbaixoDoNo = 1;
         int nivelEsq = 0;
         
         // Pega o filho a esquerda da chave
         NoDaArvore* filho = getFilhoAEsquerda(chave, no);
         NoDaArvore* filhoMaisADireita = getFilhoMaisADireita(filho, &nivelEsq);   
         
         *nivelAbaixoDoNo += nivelEsq;
            
         // A preferencia � o no pela ESQUERDA
         if(filhoMaisADireita != NULL && filhoMaisADireita->getNumeroDeChaves() > teto - 1)            
             return filhoMaisADireita;
         
         
         // Pega o filho a direita da chave
         int nivelDir = 0;
         filho = getFilhoADireita(chave, no);
         NoDaArvore* filhoMaisAEsquerda = getFilhoMaisAEsquerda(filho, &nivelDir);
         
         if(filhoMaisAEsquerda != NULL && filhoMaisAEsquerda->getNumeroDeChaves() > teto - 1){
             *nivelAbaixoDoNo += nivelDir;              
             return filhoMaisAEsquerda;
		  }
         
         // Se ambos n�o possuirem o n�mero de chaves maior que o m�nimo, 
         // retorna o extremo da direita (filho a esquerda do no que cont�m a chave)
         return filhoMaisADireita;  
                  
     }
     
//-----------------------------------------------------------------------------------------------------------------------
     
     /**
         Busca o filho extremo (� direita ou � esquerda) da chave do no informado
         
         * chave : chave do no que deseja fazer a busca do filho extremo
         * no : no que cont�m a chave informada
         * ehODaDireita : set true para buscar o filho mais � direita. 
                          set false para buscar o filho mais � esquerda.
         * nivel: retorna por esse par�metro qual o n�vel que se encontra o no extremo 
     */
     NoDaArvore* getFilhoExtremo(int chave, NoDaArvore* no, bool ehODaDireita, int *nivel){
         
         NoDaArvore* noAux = ehODaDireita ? getFilhoADireita(chave, no) : getFilhoAEsquerda(chave, no);
         NoDaArvore* n = no;
         
         *nivel = 0;
         
         while(noAux != NULL){
            *nivel += 1;            
            n = noAux;
            int posicao = ehODaDireita ? noAux->getNumeroDeChaves() - 1 : 0;
            int k = noAux->getChaveDaPosicao(posicao); 
            noAux = ehODaDireita ? getFilhoADireita(k, noAux) : getFilhoAEsquerda(k, noAux);               
         }    
         
         return n;             
     } 
     
//----------------------------------------------------------------------------------------------------------
     
     /**
        Retorna o filho mais � esquerda do no informado
        
        * no : no que � desejado encontrar o filho mais � esquerda
        * nivel : retorna por esse par�metro o nivel que o no extremo se encontra 
     */ 
     NoDaArvore* getFilhoMaisAEsquerda(NoDaArvore* no, int *nivel){
         if(no == NULL)
             return NULL;
             
         if(no->ehfolha())
             return no;    
         
         int chave = no->getChaveDaPosicao(0);
             
         return getFilhoExtremo(chave, no, false, nivel);     
     }
     
//-----------------------------------------------------------------------------------------------------------  
      
      /**
        Retorna o filho mais � direita do no informado
        
        * no : no que � desejado encontrar o filho mais � direita
        * nivel : retorna por esse par�metro o nivel que o no extremo se encontra 
     */ 
      NoDaArvore* getFilhoMaisADireita(NoDaArvore* no, int *nivel){
         if(no == NULL)
             return NULL;
             
         if(no->ehfolha())
             return no;    
         
         int chave = no->getChaveDaPosicao(no->getNumeroDeChaves() - 1);
         
         return getFilhoExtremo(chave, no, true, nivel);     
     }            
     
//----------------------------------------------------------------------------------------------------------
     
     /**
        Retorna o filho � esquerda do no informado
        
        * chave : chave contida no no informado que � desejado encontrar o filho � esquerda
        * no : no que � desejado encontrar o filho mais a esquerda 
     */ 
     NoDaArvore* getFilhoAEsquerda(int chave, NoDaArvore* no){
         
         return getFilho(chave, no, false);     
     }
     
//-----------------------------------------------------------------------------------------------------------  
      
      /**
        Retorna o filho � direita do no informado
        
        * chave : chave contida no no informado que � desejado encontrar o filho � direita
        * no : no que � desejado encontrar o filho mais a esquerda 
     */ 
      NoDaArvore* getFilhoADireita(int chave, NoDaArvore* no){
         
         return getFilho(chave, no, true);     
     }
     
// ------------------------------------------------------------------------------------------------------------     
     
     // 
     /**
        Retorna o filho da chave informada.
        
        * chave : chave contida no no informado que � desejado encontrar o filho � direita
        * no : no que � desejado encontrar o filho mais a esquerda
        * ehODaDireita : set true para retornar o filho � direita
                    set false para retornar o filho � esquerda 
     */ 
     NoDaArvore* getFilho(int chave, NoDaArvore* no, bool ehODaDireita){
         
         int posicao = no != NULL ? no->getPosicaoDaChave(chave) : -1; 
         
         if(posicao < 0)
             return NULL;
             
         return no->getFilhoDaPosicao(ehODaDireita ? posicao + 1 : posicao);           
     }     
     
     
     
     
//---------------------------------------------------------------------------------------------------------------
     
     /** Busca e retorna o no pelo qual a chave ser� inserida
         
         * chave : chave a ser inserida
         * nivelDeParada: se for para inserir a chave informada numa folha, set -1,
                          caso contr�rio informe o valor do n�vel (1..N) em que o no deve estar para inserir a chave 
         * nivelDoNo : retorna o por esse par�metro o n�vel do n� encontrado
     */
     NoDaArvore* getNoAInserirNovaChave(int chave, int nivelDeParada, int* nivelDoNo){
          
          *nivelDoNo = 1;
          
          NoDaArvore* noAux = raiz;
          
          while(noAux != NULL){       
                             
             if((nivelDeParada == *nivelDoNo) || noAux->ehfolha())
                 return noAux;
                                                
             noAux = noAux->getProximoNoParaAChave(chave); 
			 
             *nivelDoNo = *nivelDoNo + 1;
                                            
          }   

		   return NULL; 
     }     
     
     
     
     
     
     
// --------------------------------------------------------------------------------------------------------------  
   
      
     /** O m�todo inserir � recursivo somente quando o no est� cheio
     
         * chave : chave que vai inserida no no informado
         * no : n� que vai inserir a chave
         * nivelDoNo : n�vel em que se encontra o n�
         * filhoAEsquerda : filho a esquerda da chave que vai ser inserida
         * filhoADireita : filho a direita da chave que vai ser inserida   
     */                                
     void inserir(int chave, NoDaArvore* no, int nivelDoNo, NoDaArvore* filhoAEsquerda, NoDaArvore* filhoADireita)
     {    
          
          if(raiz == NULL){  

              raiz = (NoDaArvore*) malloc(sizeof(NoDaArvore)); 
              
              if(!raiz->cria(ordem, nivelDoNo == -1)){
                  cout << "\nMemoria insuficiente!" << endl;
                  cin.get();
                  return;
              }
              
              raiz->adicionaChave(chave);
              
              if(filhoAEsquerda != NULL && filhoADireita != NULL){                  
                  raiz->adicionaFilho(filhoAEsquerda, 0);
                  raiz->adicionaFilho(filhoADireita, 1);
                  
                  filhoAEsquerda->setAscendente(raiz);
                  filhoADireita->setAscendente(raiz);
              }
              
          }else{
                
                // Pega a posi��o que a chave foi inserida no no
                int posicao = no->adicionaChave(chave);
                
                if(filhoADireita != NULL){  
                   // A partir da posi��o que a chave foi inserida, insere o ponteiro a sua direita  
                   filhoADireita->setAscendente(no);
                   no->adicionaFilho(filhoADireita, posicao + 1);
                }
                
               
               
               // Condi��o para deslocamento e divis�o do no
               if(no->getNumeroDeChaves() == ordem){
                   
                   // Divide o no                                      
                   NoDaArvore **novosFilhos = no->divideFilhos(); // guarda os filhos do novo no(se existirem)
                   int *novasChaves = no->divideChaves(); // guarda as chaves do novo no
                   int newNumberOfKeys = ordem - no->getNumeroDeChaves();
                   
                   // Cria um novo no
                   NoDaArvore* novoNo;
                   
                   novoNo = (NoDaArvore*) malloc(sizeof(NoDaArvore)); 
                   
				   if(!novoNo->cria(ordem, no->ehfolha())){
					  cout << "\nMemoria insuficiente!" << endl;
					  cin.get();
					  return;
				   }
				   
				   // ajusta os ponteiros			   
				   novoNo->setIrmaoADireita(no->getIrmaoADireita());
				   novoNo->setIrmaoAEsquerda(no);
				   
				   if(no->getIrmaoADireita() != NULL)
					  no->getIrmaoADireita()->setIrmaoAEsquerda(novoNo);
					  
				   no->setIrmaoADireita(novoNo);	
				   
				   
				   
                   // Adiciona as chaves no novo no
                   for(int i = 0; i < newNumberOfKeys; i++)
                       novoNo->adicionaChave(novasChaves[i]);
                   
				   free(novasChaves);
				   
                   // Se n�o for uma folha, adiciona os ponteiros que foram separados do no velho
                   if(novosFilhos != NULL){
                                  
                       NoDaArvore* f = NULL;
                                 
                       // Adiciona os ponteiros  
                       for(int i=0; i < newNumberOfKeys + 1; i++){  
                           f = novosFilhos[i];        
                           f->setAscendente(novoNo);
                           novoNo->adicionaFilho(f, i);
						   novosFilhos[i] = NULL;
                       }
                         
                       f = NULL;
                       
                       // limpa da mem�ria
                       free(novosFilhos);
                   }
                      
                   
                   
               
               
                   // Pega a chave que vai subir e a retira do no
                   int chavePromovida = no->retiraUltimaChave();                       
                   
                   // Define os ponteiros para o novo elemento que vai subir
                   filhoAEsquerda = no == raiz ? no : NULL; 
                   filhoADireita = novoNo;              
                   
                   if(no == raiz){
                       raiz = NULL; // o elemento a ser reinserido ser� a nova raiz 
                       no = NULL;
                   }else
                       no = no->getAscendente();
                       
                   // Reinsere o elemento no nivel acima do que ele estava 
                   inserir(chavePromovida, no, nivelDoNo - 1, filhoAEsquerda, filhoADireita);         
               } 
               
          }           
        
     } 
     

// --------------------------------------------------------------------------------------------------------------
    
    
    
    /* M�TODOS DE REMO�AO */
    
    
    /** Caso em que o no possui algum irm�o com mais chaves que o m�nimo 
        e a redistribui��o das chaves entre eles e o ascendente � realizada
        *  no : no que teve uma chave rec�m removida
        *  ascendente: no pai do no e do irmao
        *  irmao : irmao do no que possui mais chaves que o m�nimo
        *  chave : chave que foi removida
        *  deslocaPonteiro : set true se for um no n�o folha e este est� sendo tratato como folha (na remo��o)
                             e com isso um dos filhos da chave que vai ser promovida do irm�o ser� acrescentada
                             a lista de filhos do no   
    */
    void redistribueChaves(NoDaArvore* no, NoDaArvore* ascendente, NoDaArvore* irmao, int chave, bool deslocaPonteiro){
        // Promove a subida da primeira/�ltima (a direita/a esquerda) chave do no irm�o
        // e desce a chave do pai para o no que teve a chave removida e provocou a redistribui��o
        
        int chavePromovida = -1;
        int decrementoDePosicao = 0; // o decremento indica se o elemento que vai ser promovida
                                    // est� a direita ou � esquerda. Se estiver � direita, ent�o
                                    // a posi��o da chave que vai subir � decrementada em um
                                    // pois esta chave � maior que a que vai descer!  
        
        
        // Pega a primeira chave do no para comparar com a primeira chave do irm�o
        // e concluir se este � irm�o � direita ou � esquerda
        // Se o total de chaves do no corrente = 0, ent�o o primeiro elemento dele era o que acabou de ser removido                            
        int primeiraChave = no->getNumeroDeChaves() > 0 ? no->getChaveDaPosicao(0) : chave;
        
        int posNo = 0; // nova posi��o do ponteiro que vai ser deslocado (caso o argumento deslocaPonteiro seja verdadeiro)
        
        NoDaArvore* ponteiro = NULL;
        
        // Verifica se o irm�o � a esquerda ou � direita
        if(primeiraChave < irmao->getChaveDaPosicao(0)){
           // � o irm�o da direita
           
           if(deslocaPonteiro){ // Verifica se o ponteiro vai ser deslocado
               ponteiro = irmao->retiraPrimeiroFilho(); // pega o ponteiro que vai ser deslocado
               
               // Se for para deslocar o ponteiro, ent�o vai deslocar ap�s o �ltimo j� existente no no corrente!
               posNo = no->getNumeroDeChaves() + 1;    
           }
               
           chavePromovida = irmao->retiraPrimeiraChave();
           decrementoDePosicao++;
                                 
        }else{
           // � o irm�o da esquerda
            if(deslocaPonteiro) // Verifica se o ponteiro vai ser deslocado
               ponteiro = irmao->retiraUltimoFilho(); // pega o ponteiro que vai ser deslocado
            
               
           chavePromovida = irmao->retiraUltimaChave();  
        }
        
        // Pega a posi��o que a chave promovida vai ficar
        int posicaoDaChavePromovida = ascendente->getPosicaoParaANovaChave(chavePromovida) - decrementoDePosicao;
        
        // Guarda a chave que vai ser removida do ascendente
        int chaveRebaixada = ascendente->getChaveDaPosicao(posicaoDaChavePromovida);
        
        // Coloca a chave promovida no no pai e retira a que foi rebaixada
        ascendente->removeChaveDaPosicao(posicaoDaChavePromovida);
        ascendente->adicionaChave(chavePromovida);
        
        // Coloca a chave que era do no pai no no que estava com n�mero de chaves inferior ao m�nimo
        no->adicionaChave(chaveRebaixada);   
        
         // Verifica se existe algum ponteiro a ser deslocado
        if(ponteiro != NULL){
            // Significa que j� foi feita uma fus�o com a chave que est� sendo removida
            // no momento e que est� faltando um ponteiro para o filho a direita ou a esquerda
            ponteiro->setAscendente(no);
            no->adicionaFilho(ponteiro, posNo);  
        }         
    }
    
// --------------------------------------------------------------------------------------------------------------
    
     /** Caso em que o no, n�o raiz, n�o possui algum irm�o com mais chaves que o m�nimo 
        e a fus�o entre um dos seus irm�os e a chave pai � realizada
        *  no : no que teve uma chave rec�m removida
        *  ascendente: no pai do no e do irmao
        *  chave : chave que foi removida
        *  nivelDoNo : nivel em que se encontra o no que teve a chave removida
        *  teto : teto � calculado a partir da ordem 
    */
    void fundeOsNos(NoDaArvore* no, NoDaArvore* ascendente, int chave, int nivelDoNo, int teto){
       
	   
       // Prefer�ncia -> Irm�o da direita
       NoDaArvore* irmao = no->getIrmaoADireita();
       
       // Auxiliar na posi��o do ponteiro caso este precise ser deslocado para o outro lado da �rvore
       int posNo = teto - 1; // m�nimo de chaves
       
       int totalNos = teto - 1; // m�nimo de chaves
       
       // Verifica se possui de fato um irm�o � direita
       if(irmao == NULL)
           // N�o possui irm�o � direita => o no � o filho mais a direita dentre os que o ascendente informado possui!    
           irmao = no;
       else
           // Possui irm�o a direita => o total de ponteiros = total de ponteiros do irm�o
           totalNos = irmao->getNumeroDeChaves() + 1;
        
       
       
       
       // Se o total de chaves = 0 => que est� no no mais a direita e 
       // a �ltima chave v�lida dele � a que acabou de ser removida
       int primeiraChave = irmao->getNumeroDeChaves() > 0 ? irmao->getChaveDaPosicao(0) : chave;
       
       // Pega a posi��o da chave do ascendente que vai "descer"
       int posicaoKeyRebaixada = ascendente->getPosicaoParaANovaChave(primeiraChave);
       if(posicaoKeyRebaixada > 0)
          // o decremento � feito pois o irm�o � sempre um filho a direita da chave pai dos dois nos (no e irmao)
          // e por ser a direita, sempre vai ser colocada uma posi��o a mais que ela, ent�o, para se obter a correta
          // posi��o da chave que vai ser rebaixada, � s� decrementar em 1 o seu valor!
          posicaoKeyRebaixada--;
       
          
       // Guarda o valor a chave do ascendente que vai ser rebaixada
       int chaveRebaixada = ascendente->getChaveDaPosicao(posicaoKeyRebaixada);
       
	   
       // Verifica se de fato possui irm�o � direita
       if(irmao == no){
           // N�o possui irm�o � direita => o no que vai receber as chaves � o irm�o � esquerda dele, e n�o ele!     
           no = no->getIrmaoAEsquerda(); 
           // A posi��o do novo filho vai ser ap�s o �ltimo filho j� existente no irm�o
           posNo = no->getNumeroDeChaves() + 1; 
       }
	   
       
       // Funde de fato os nos, adicionando a chave que vai ser rebaixada e as chaves do irm�o � direita        
       no->adicionaChave(chaveRebaixada);
          
       for(int i=0; i < irmao->getNumeroDeChaves(); i++)
           no->adicionaChave(irmao->getChaveDaPosicao(i));
       
       
       // Adiciona tamb�m os ponteiros filhos das chaves do irm�o que foram adicionadas ao no (se n�o forem folhas)
       if(!irmao->ehfolha()){                                            
           // Adiciona os ponteiros
           NoDaArvore* f = NULL;

           for(int i=0; i < totalNos; i++){ 
                    
               f = irmao->getFilhoDaPosicao(i); 
                
               if(f != NULL){
                   // Seta o ponteiro do seu novo pai 
                   f->setAscendente(no); 
                      
                   no->adicionaFilho(f, i + posNo);
               }
           } 
           
       }
       
       
       // O no ascendente j� pode estar com a chave (que foi a substituta
       // de uma chave anteriormente removida por c�pia) => vai encontrar
       // um posi��o a mais do que deveria ser pela condi��o de distribui��o da �rvore
       if(posicaoKeyRebaixada > 0 && ascendente->contemChave(primeiraChave))
          posicaoKeyRebaixada--;
       

       // Remove o ponteiro para aquele no que foi apagado   
       ascendente->removeFilhoDaPosicao(posicaoKeyRebaixada + 1);
       
       // Ajusta os ponteiros aos irm�os
       irmao = ascendente->getFilhoDaPosicao(posicaoKeyRebaixada + 1);
       
       no->setIrmaoADireita(irmao);
       
       if(irmao != NULL)
           irmao->setIrmaoAEsquerda(no);   
       
       // Verifica se o ascendente � a raiz � s� possui 1 elemento (que � o que deve ser removido)
       if(ascendente == raiz && ascendente->getNumeroDeChaves() == 1){
           // Se a �nica chave que estava na raiz desceu, ent�o a nova raiz � 
           // o no que agora cont�m esta mesma chave           
           raiz = no;
           no->setAscendente(NULL);
           free(ascendente);
       }else
           // Chama o m�todo novamente e deleta a chave do n� n�o-folha
           // como sendo uma folha, at� que chegue ao caso de redistribui��o ou na raiz
           remover(chaveRebaixada, ascendente, nivelDoNo - 1, nivelDoNo - 1);

           
    }   
    
// --------------------------------------------------------------------------------------------------------------
    
    /** Caso em que o no que possue a chave que vai ser removida n�o � folha 
        *  no : no que contem a chave que vai ser removida
        *  chave : chave que vai ser removida
        *  nivelDoNo : nivel em que se encontra o no 
        *  teto : teto � calculado a partir da ordem 
    */
    void removePorCopia(NoDaArvore* no, int chave, int teto, int nivelDoNo){
        
        int nivelAbaixoDoNo = 0;
        
        // Pega o filho com mais chaves que o m�nimo, que pode ser um filho 
        // que N�O possue mais chaves que o m�nimo -> obrigatoriamente � o filho extremo da direita do seu 
        // filho imediato � esquerda
        NoDaArvore* filho = getFilhoComMaisChavesQueOMinimo(chave, no, teto, &nivelAbaixoDoNo);
        
        nivelDoNo += nivelAbaixoDoNo;
		

        int chavePromovida = -1;
        
        // Verifica se o filho � a esquerda ou � direita
        if(chave <= filho->getChaveDaPosicao(0)){
           // � o filho extremo � esquerda do filho � direita do no que cont�m 
           // a chave que vai ser removida -> Pega a primeira chave
           chavePromovida = filho->getChaveDaPosicao(0);
                     
        }else
           // � o filho extremo � direita do filho � esquerda do no que cont�m 
           // a chave que vai ser removida -> Pega a �ltima chave
           chavePromovida = filho->getChaveDaPosicao(filho->getNumeroDeChaves() - 1);  
        

        // Substitue o valor
        no->substitueChaveNaPosicao(chavePromovida, no->getPosicaoDaChave(chave));
        
        // Chama o m�todo novamente (recursividade) para que o elemento da folha seja deletado
        remover(chavePromovida, filho,  nivelDoNo, -1); 
              
    }     

// --------------------------------------------------------------------------------------------------------------  
     
     /** Esse m�todo � recursivo quando h� fus�o ou remo��o por c�pia 
        *  no : no que contem a chave que vai ser removida
        *  chave : chave que vai ser removida
        *  nivelDoNo : nivel em que se encontra o no 
        *  nivelDeParada :  indica que o no que cont�m a chave e n�o � uma folha ser� tratado como um no folha
                         para efetuar o processo de remo��o, afim de se obter a perfeita organiza��o da �rvore 
     */           
     void remover(int chave, NoDaArvore* no, int nivelDoNo, int nivelDeParada)
     {
                      
         int teto = (int) ordem / 2;
         if(ordem % 2 != 0)
            teto++;
         
         if(no->ehfolha() || nivelDoNo == nivelDeParada){
             
             /* � uma folha ou deve ser tratato como folha */
             
             // Guarda o seu no ascendente
             NoDaArvore* ascendente = no->getAscendente();
                                
             // Remove a chave do no
             int posicao = no->removeChave(chave);
                
             // S� entra na condi��o abaixo se, ao remover a chave, o no ficou com menos chaves que o m�nimo permitido   
             if(no->getNumeroDeChaves() < teto - 1){
                
                // Verifica se tem algum irm�o excedendo o n�mero m�nimo de chaves
                NoDaArvore* irmao = getIrmaoComMaisChavesQueOMinimo(no, teto);
                
                if(irmao != NULL){
                    // REDISTRIBUI��O!           
                    redistribueChaves(no, ascendente, irmao, chave, nivelDoNo == nivelDeParada);
                    
                }else if(ascendente != NULL){ 
                   // FUNDE OS NODOS
                   fundeOsNos(no, ascendente, chave, nivelDoNo, teto);                    
                       
                }else if(no->getNumeroDeChaves() == 0)
                   // Foi removido todos os elementos da �rvore!
                    raiz = NULL; 
                                       
             }
                                 
         }else{
            // N� n�o-folha
            removePorCopia(no, chave, teto, nivelDoNo);   
         } 
        
     }         
     
     
     /* FIM - M�TODOS DE REMO�AO */ 
      
      
      
      
     /* IMPRESS�O */
     
// --------------------------------------------------------------------------------------------------------------

    /**
       Imprime as chaves do no
     */	
	void imprimeChaves(NoDaArvore* no){
		
			if(no == NULL)
				return;
			
			cout << "  [";
			
			for(int i = 0; i < no->getNumeroDeChaves(); i++)
				cout << "  " << no->getChaveDaPosicao(i);
			
			
			cout << "  ]";
			
			// se desejar imprimir a primeira chave do ascendente,
			// irm�o � esquerda e irm�o � direita, s� descomentar!
			/*NoDaArvore* ac = no->getAscendente();
			NoDaArvore* bl = no->getIrmaoAEsquerda();
			NoDaArvore* br = no->getIrmaoADireita();
			
			if(ac != NULL)
			   cout << "(A: " << ac->getChaveDaPosicao(0) << ") ";
			   
			if(bl != NULL)
			   cout << "(E: " << bl->getChaveDaPosicao(0) << ") ";
			   
			if(br != NULL)
			   cout << "(D: " << br->getChaveDaPosicao(0) << ") "; */
			
	  }
               
               
               
    /* FIM - IMPRESS�O */
              
               
               
    /* ** FIM - M�TODO PRIVADOS ** */  
    
    
                 
              
 // -------------------------------------------------- PUBLIC ---------------------------------------------------             
      public:
                                            // construtor
     void cria(int m)
       { 
           ordem = m; 
           raiz = NULL;
           totalChaves = 0;        
        }
//--------------------------------------------------------------------------------------------------------------
     
     /**
        Encontra o n� que contem a chave. Retorna NULL se a chave n�o estiver contida na �rvore
     */
     NoDaArvore* buscar(int chave)
     {
           int nivel;   
           return buscar(chave, &nivel);
     }     
     
     
//--------------------------------------------------------------------------------------------------------------
     
     /** 
         Busca o n� que contem a chave. Retorna NULL se a chave n�o estiver contida na �rvore
         
         * Retorna o nivel do no encontrado por par�metro.
     */ 
     NoDaArvore* buscar(int chave, int *nivelDoNo)
     {     
           *nivelDoNo = 1; 
           NoDaArvore* noAux = raiz;
           
           while(noAux != NULL){
                         
                if(noAux->contemChave(chave))
                   break;       
               
               noAux = noAux->getProximoNoParaAChave(chave);
			   
               *nivelDoNo = *nivelDoNo + 1;
               
           }
              
           return noAux;   
         
     }      

     
//--------------------------------------------------------------------------------------------------------------

     /** 
         Insere uma nova chave na �rvore
         Retorna false se a ordem for inv�lida ou se a chave j� constar na �rvore
     */
     bool adicionaChave(int chave)
     {    
          if(ordem <= 2)
             return false;   
          
          int nivel = -1;
          
          NoDaArvore* no = raiz != NULL ? buscar(chave, &nivel) : NULL;
          
          // N�o permite a inser��o de chaves repetidas 
          if(no != NULL)
              return false;
              
          no = raiz != NULL ? getNoAInserirNovaChave(chave, -1, &nivel) : NULL;    
          
          totalChaves++;
          
          // Abstrai esse m�todo do usu�rio   
          inserir(chave, no, nivel, NULL, NULL);
          
          return true;
     }
     
//--------------------------------------------------------------------------------------------------------------

     /** 
         Remove a chave da �rvore. Se a chave n�o constar na �rvore, retorna false
     */
     bool removeChave(int chave)
     {    
          
          if(raiz == NULL)
             return false;
          
          int nivel = 0;
		  
          NoDaArvore* no = buscar(chave, &nivel);
  
          if(no == NULL)
              return false;
  
          totalChaves--;
          
          // Abstrai esse m�todo do usu�rio   
          remover(chave, no, nivel, -1);
          
          return true;
     }     
     
// -------------------------------------------------------------------------------------------------------------
    
    /**
        Retorna o no raiz da �rvore  
    */
    NoDaArvore* getRaiz(){
        return raiz;      
    } 
    
// -------------------------------------------------------------------------------------------------------------
    
    /** 
        Retorna o total de chaves presentes na �rvore
    */
    int getTotalChaves(){
        return totalChaves;    
    }    
    
// -------------------------------------------------------------------------------------------------------------
   
   /**
       Retorna a altura total da �rvore
   */
   int getAltura(){ 
       
       if(raiz != NULL){
                
          int altura = 1;
          
          if(!raiz->ehfolha()){ 
          
              NoDaArvore* no = getFilhoMaisAEsquerda(raiz, &altura);
              
              altura++;
              
          }
          
          return altura;
                
       } 
       
       return 0;   
   }    
    
// -------------------------------------------------------------------------------------------------------------
    
    /**
        Retorna a ordem da �rvore
    */
    int getOrdem(){
        return ordem;      
    }         


//--------------------------------------------------------------------------------------------------------------
	
	
	
	/** Imprime a �rvore na tela na ordem de n�veis (fazendo um percurso por extens�o)
        E retorna a altura e o total de chaves dessa �rvore atrav�s de par�metros por refer�ncia
    */
    void imprime(int *altura, int *totalChaves){             
		 
		 *totalChaves = 0;
		 
		 if(raiz != NULL){
			 
			 NoDaArvore*  no = raiz;
			
			 *altura = 1;
		 
			 std::queue<NoDaArvore*> filaTemp; 
			 std::queue<NoDaArvore*> nos;

			 int* totalPorNivel;
			 
			 int nivelAtual = 1;
			 
			 totalPorNivel = (int*) malloc(sizeof(int));
			 
			 totalPorNivel[0] = 1;
			 
			 
			 *totalChaves = raiz->getNumeroDeChaves();
			 
			 
			 if(!no->ehfolha()){
				
				int contNos = 1, contNosProxNivel = 0;
				
				nivelAtual++;
				totalPorNivel = (int*) realloc(totalPorNivel, nivelAtual * sizeof(int));
				totalPorNivel[nivelAtual - 1] = 0;
			 
			 
				 while(no != NULL && !no->ehfolha()){
					
					if(contNos > totalPorNivel[nivelAtual - 2]){
						
						nivelAtual++;	
						contNos = 1;	
						totalPorNivel = (int*) realloc(totalPorNivel, nivelAtual * sizeof(int));
						
						totalPorNivel[nivelAtual - 1] = 0;
						
					}
					 	
					totalPorNivel[nivelAtual - 1] = totalPorNivel[nivelAtual - 1] + no->getNumeroDeChaves() + 1;
					
					for(int i = 0; i <= no->getNumeroDeChaves(); i++){  
						filaTemp.push(no->getFilhoDaPosicao(i));                 
						nos.push(no->getFilhoDaPosicao(i));
						*totalChaves = *totalChaves + no->getFilhoDaPosicao(i)->getNumeroDeChaves();
					}
					
					no = filaTemp.front();
					
					filaTemp.pop();
					
					contNos++;			
		 
				 }
				 
			 }
			 
			 // imprime a raiz 
			 imprimeChaves(raiz);
			 
			 cout << endl;
			 
			 
			 *altura = nivelAtual;
			 
			 nivelAtual = 2;
			 
			 while(!nos.empty() && nivelAtual <= *altura){
				
				for(int k = 0; k < totalPorNivel[nivelAtual - 1]; k++){
					imprimeChaves(nos.front());
					nos.pop();
				}
				
				cout << endl;
				
				nivelAtual++;
			 } 
			 
			 free(totalPorNivel);
			 
		 }else
			*altura = 0;   			
         
    }
    
  

//--------------------------------------------------------------------------------------------------------------
    
     }; // fim da classe ArvoreB
///////////////////////////////////////////////////////////////////////
     
 
     
     
     
     
     
     
     
     
     // M�todos Complementares
     
     
     /**
         Imprime na tela a ordem, a altura e o total de chaves presentes na �rvore 
     */
     void imprimeArvore(ArvoreB* arvore){
         cout << "\nARVORE B DE ORDEM = " << arvore->getOrdem() << endl;
         
         cout << "\nALTURA DA ARVORE = " << arvore->getAltura() << "   TOTAL DE CHAVES = " << arvore->getTotalChaves() << "\n\n\n" << endl;
         
         cin.get();     
     }
     
     /**
         Imprime a �rvore na �ntegra
     */
     void imprimeArvoreCompleta(ArvoreB* arvore){
         cout << "\nARVORE B DE ORDEM = " << arvore->getOrdem() << endl;
         
         int altura = 0;
         
         int totalChaves = 0;
         
         arvore->imprime(&altura, &totalChaves);
		 
         cout << "\n\n\nALTURA DA ARVORE = " << altura << "   TOTAL DE CHAVES = " << totalChaves << "\n\n\n" << endl;;
         
         cin.get();         
     }
     
     
     
     
     
     
     /* LEITURA DO ARQUIVO TEXTO */
     
     
     /**
         Carrega as chaves de um arquivo texto com o caminho especificado
         * caminho : nome do arquivo (Ex: chaves.txt)
         * arvore
         * remover : set true se deseja carregar as chaves que devem ser removidas da �rvore. 
                     set false se deseja carregar as chaves que devem ser inseridas na �rvore.
     */
     bool carregaDadosDoArquivo(const char* caminho, ArvoreB* arvore, bool remover){
          
		  string linha;
		  
    	  int chave;
    	  
    	  ifstream arquivo (caminho); 
		  
    	  if (arquivo.is_open()){
		  
            int chaves = 0;                   
                               
    		while (!arquivo.eof()){
			
    		  getline(arquivo,linha); // como foi aberto em modo texto(padr�o)
    								 //e n�o bin�rio(ios::bin) pega cada linha
    		  stringstream s(linha);
			  
    		  s >> chave;
    		  
    		  if(!arquivo.eof()){
			  
                  if(!remover){                            
					// inserir
                      if(!arvore->adicionaChave(chave)){
					  
                        if(arvore->getOrdem() <= 2){ 
						
            				cout << "Para ser uma Arvore B, a ordem deve ser > 2";
            				cin.get();
            				return false; 
							
                        }
						
                        //cout << "\n\nChave " << chave << " ja consta na arvore e por isso nao foi inserida\n\n" << endl;
                        chaves++;

        			  }/*else{
                        cout << "\nChave " << chave << " inserida com sucesso!\n" << endl;    
        			    imprimeArvoreCompleta(arvore);
                      }*/
                      
        			  
                  }else{
                      // remover 
                      if(arvore->removeChave(chave)){
                         chaves++;
						 //cout << "\nChave " << chave << " removida com sucesso!\n\n" << endl;
                         //cin.get();
                         //imprimeArvoreCompleta(arvore);                              
                      }/*else
                         cout << "\nChave " << chave << " nao consta na arvore.\n" << endl;  
                       */
                              
                  }
				  
              }
    		  
    		}
    		
    		if(remover)
    		    cout << "\nTOTAL DE CHAVES REMOVIDAS = " << chaves << "\n" << endl;
    		else if(chaves > 0)
    		    cout << "\nTOTAL DE CHAVES QUE NAO FORAM INSERIDAS POIS JA CONSTAVAM NA ARVORE = " << chaves << "\n" << endl;
    		    
    		arquivo.close();
			
    	  }
    
    	  else{ 
                cout << "Arquivo '" << caminho <<"' nao encontrado";
                cin.get();
                return false;
          }  
          
          return true;
     }
     
     
     /**
          Carrega as chaves de um arquivo texto com o caminho especificado a serem inseridas na �rvore
     */
     bool carregaDadosDoArquivoInserir(const char* caminho, ArvoreB* arvore){
          return carregaDadosDoArquivo(caminho, arvore, false);
     }
     
     
     /**
          Carrega as chaves de um arquivo texto com o caminho especificado a serem removidas da �rvore
     */
     bool carregaDadosDoArquivoRemover(const char* caminho, ArvoreB* arvore){
          return carregaDadosDoArquivo(caminho, arvore, true);
     }
     
     /* FIM - LEITURA DO ARQUIVO TEXTO */
     
     
     
     
     
	 
	 
	 
	 void removeChaveDaArvore(ArvoreB* arvore, int chave){
         cout << "\nREMOVENDO A CHAVE  " << chave << endl;
         arvore->removeChave(chave);
         cin.get();     
     }
	 
	 
     
     
     
     
     // Fun��o Principal
     
     int main(){
         // Criando uma �rvore B de ordem definida no contrutor
         ArvoreB arvore;
         
		 // escolhe a ordem da �rvore
         arvore.cria(3);
         
         const char* arquivoInserir = "exampleI.txt"; // arquivo que cont�m as chaves que v�o ser inseridas na �rvore
         const char* arquivoRemover = "exampleR.txt"; // arquivo que cont�m as chaves que v�o ser removidas da �rvore
         
         cout << "\nINSERINDO CHAVES DO ARQUIVO '" << arquivoInserir << "'\n" << endl;

		 
         // Carrega as chaves do arquivo e insere na arvore
         if(!carregaDadosDoArquivoInserir(arquivoInserir, &arvore))
            return 1;         
         
         // Imprime na Tela
         imprimeArvoreCompleta(&arvore);
         
         cout << "\nREMOVENDO CHAVES DO ARQUIVO '" << arquivoRemover << "'\n" << endl;
         
         // Carrega as chaves do arquivo e insere na arvore
         if(!carregaDadosDoArquivoRemover(arquivoRemover, &arvore))
            return 1;   
         
		  
         
         // Imprime novamente os dados da �rvore
         imprimeArvoreCompleta(&arvore);
		 
         
         return 0;    
     }
     
     
     
     
     
     
