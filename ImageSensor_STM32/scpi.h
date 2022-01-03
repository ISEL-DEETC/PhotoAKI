
#ifndef _SCPI_H_
#define _SCPI_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "myUtils.h"

#define MAX_SUBNODES      20
#define MAX_ARG_SIZE      128

typedef void (*funcType)(char *) ;

typedef struct node_s{
  char *nodeName;
  char *shortName;
  struct node_s *childNodes[MAX_SUBNODES];
  uint8_t nChilds;
  funcType setFunction;
  funcType queryFunction;
}NodeTypedef;

NodeTypedef *SCPI_GetRootNode();
NodeTypedef *SCPI_GetCommonNode();
NodeTypedef *SCPI_GetCurrentNode();
void SCPI_Initialize();
void SCPI_AddNode(NodeTypedef *parent, const char *nodeName, const char *shortName, funcType setFunc, funcType queryFunc);
int SCPI_RunCommand(char *cmd);

NodeTypedef * GetNodeIn(NodeTypedef *parent, const char *nodeName);

#endif
