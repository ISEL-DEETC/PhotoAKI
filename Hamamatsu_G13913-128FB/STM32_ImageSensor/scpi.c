
#include "scpi.h"

static NodeTypedef *currentNode;
static NodeTypedef *rootNode;
static NodeTypedef *commonNode;

void UndefinedFunc(char *arg){}

NodeTypedef *SCPI_GetRootNode(){
  return rootNode;
}

NodeTypedef *SCPI_GetCommonNode(){
  return commonNode;
}

NodeTypedef *SCPI_GetCurrentNode(){
  return currentNode;
}

void SCPI_Initialize(){
  /* Common commands */
  commonNode = (NodeTypedef*)malloc(sizeof(NodeTypedef));
  commonNode->nodeName = (char*)malloc(sizeof(char)*7);
  strcpy(commonNode->nodeName, "common");
  commonNode->nodeName;
  strcpy(commonNode->nodeName, "common");
  commonNode->nChilds = 0;
  //commonNode->changePath = true;
  commonNode->setFunction = &UndefinedFunc;
  commonNode->queryFunction = &UndefinedFunc;

  /* Root node init */
  rootNode = (NodeTypedef*)malloc(sizeof(NodeTypedef));
  
  rootNode->nodeName = (char*)malloc(sizeof(char)*5);
  strcpy(rootNode->nodeName, "root");

  rootNode->nodeName;
  strcpy(rootNode->nodeName, "root");
  
  rootNode->nChilds = 0;
  rootNode->setFunction = &UndefinedFunc;
  rootNode->queryFunction = &UndefinedFunc;
  
  currentNode = rootNode;

  
}

void SCPI_AddNode(NodeTypedef *parent, const char *nodeName, const char *shortName, funcType setfunc, funcType queryfunc){

  NodeTypedef *newNode = (NodeTypedef*)malloc(sizeof(NodeTypedef));

  newNode->nodeName = (char*)malloc(sizeof(char)*(strlen(nodeName)+1));
  strcpy(newNode->nodeName, nodeName);

  if(shortName != NULL){
    newNode->shortName = (char*)malloc(sizeof(char)*(strlen(shortName)+1));
    strcpy(newNode->shortName, shortName);
  }else{
    newNode->shortName = (char*)malloc(sizeof(char)*1);
    *(newNode->shortName) = '\0';
  }
  newNode->nChilds = 0;
  newNode->setFunction = setfunc;
  newNode->queryFunction = queryfunc;

  if(parent != NULL){
    parent->childNodes[parent->nChilds++] = newNode;
  }
}

NodeTypedef * GetNodeIn(NodeTypedef *parent, const char *nodeName){
  if(parent == NULL){
    parent = rootNode;
  }
  for(int i = 0; i < parent->nChilds; ++i){
    if(WordIs(parent->childNodes[i]->nodeName, nodeName) || WordIs(parent->childNodes[i]->shortName, nodeName)){
      return parent->childNodes[i];
    }
  }
  return NULL;
}


char * DoFunctionAndMove(NodeTypedef *node, char *cmd)
{
  for(int i = 0; i < node->nChilds; ++i){
    if(WordIs(node->childNodes[i]->nodeName, cmd) || WordIs(node->childNodes[i]->shortName, cmd)){
      cmd += WordSizeIs(cmd); // AvanÃ§a para depois da keyword
      cmd = FindNextNonWhitespace(cmd);
      // Verifica se o comando é de set ou query
      bool flagQuery = false;    
      if(cmd[0] == '?'){
        flagQuery = true;
        cmd += 1;
      }
      // Obtem argumentos
      char arg[MAX_ARG_SIZE] = {'\0'};   
      char *lastChr = FindLastCharOfArgument(cmd);   
      if(lastChr != NULL){
        uint32_t arg_size = lastChr-cmd +1;
        strncpy(arg, cmd, arg_size );  
        arg[arg_size] = '\0';
      }
      if(flagQuery){         
        node->childNodes[i]->queryFunction(arg);   // executa funcao de query
      }else{
        node->childNodes[i]->setFunction(arg);     // executa funcao de set
      }
      
      if(node != commonNode){
        if(currentNode->childNodes[i]->nChilds > 0){  // Verifica se deve actualizar o currentNode
          currentNode = currentNode->childNodes[i];
        }
        cmd = FindNextPunctuation(cmd);
        if(cmd[0] == ':'){ // Evita leitura de ':' na função SCPI_RunCommand, reiniciando o currentNode
          cmd += 1;
        }
      }else{
        cmd = strchr(cmd, ';'); // Node comum apenas tem um nivel. Procura proximo comando
      }
      return cmd;
    }
  }
  cmd = strchr(cmd, ';'); // Não encontrou palavra, procura o proximo comando
  return cmd;
}


int SCPI_RunCommand(char *cmd){
  if(cmd == NULL || cmd[0] == '\0')
    return 0;
  cmd = FindNextNonWhitespace(cmd);
  char * aux;
  
  switch(cmd[0]){
    case '*':
      cmd = FindNextWord(cmd);
      aux = FindNextPunctuation(cmd);
      if(aux != NULL && cmd != NULL && aux < cmd){ // Caso encontre pontuacao antes da proxima palavra
        return SCPI_RunCommand(aux);
      }
      cmd = DoFunctionAndMove(commonNode, cmd);
      return SCPI_RunCommand(cmd);
    case ';':
      return SCPI_RunCommand(cmd+1);
    case ':':
      currentNode = rootNode;
      cmd = FindNextWord(cmd);
      aux = FindNextPunctuation(cmd);
      if(aux != NULL && cmd != NULL && aux < cmd){ // Caso encontre pontuacao antes da proxima palavra
        cmd = aux;
      }else if(cmd == NULL){ // Caso a proxima palavra nao exista
        return 0;
      }
    default:
      cmd = DoFunctionAndMove(currentNode, cmd);
      return SCPI_RunCommand(cmd);
  }
}
