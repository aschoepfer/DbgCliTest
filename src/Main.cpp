/*
 * Main.cpp
 *
 *  Created on: 14.02.2015
 *      Author: niklausd
 */
#include "DbgCliNode.h"
#include "DbgCliTopic.h"
#include "DbgCliCommand.h"

#include <stdio.h>

int main()
{
  printf("*CREATE ROOT NODE*\n");
  DbgCli_Node* mmiNode = new DbgCli_Topic("", "mmi", "MMI node.");
  DbgCli_Node::AssignRootNode(mmiNode);
  printf("MMI Node: %s\n", mmiNode->getNodeName());
  printf("%s - %s - %s\n", mmiNode->getParentPath(), mmiNode->getNodeName(), mmiNode->getHelpText());

  printf("\n*ADD TOPIC*\n");
  DbgCli_Node* screenNode = new DbgCli_Topic("mmi", "screen", "Screen Node.");
  printf("MMI Screen Node: %s\n", screenNode->getNodeName());
  printf("%s - %s - %s\n", screenNode->getParentPath(), screenNode->getNodeName(), screenNode->getHelpText());

  printf("\n*ADD COMMAND*\n");
  DbgCli_Node* showCmd = new DbgCli_Command("mmi screen", "show", "Show Node, shows current screen.");
  printf("MMI Screen Show Node: %s\n", showCmd->getNodeName());
  printf("%s - %s - %s\n", showCmd->getParentPath(), showCmd->getNodeName(), showCmd->getHelpText());
  printf("----\n");

  printf("\n*GET EXISTING NODE*\n");
  DbgCli_Node* tmpNode = DbgCli_Node::RootNode()->getNode("screen");
  printf("MMI Node: %s\n", tmpNode->getNodeName());
  printf("%s - %s - %s\n", tmpNode->getParentPath(), tmpNode->getNodeName(), tmpNode->getHelpText());

  tmpNode = tmpNode->getNode("show");
  printf("MMI Screen Node: %s\n", tmpNode->getNodeName());
  printf("%s - %s - %s\n", tmpNode->getParentPath(), tmpNode->getNodeName(), tmpNode->getHelpText());
  printf("----\n");

  unsigned int argc = 3;
  const char* args_mmi_screen_show[] = {"mmi", "screen", "show"};

  printf("\n*EXECUTE NODES*\n");
  printf("\n%d\n", argc);
  DbgCli_Topic::RootNode()->execute(argc, args_mmi_screen_show, 1);

  const char* args_mmi_screen[] = {"mmi", "screen"};
  argc = 2;
  printf("\n%d\n", argc);
  DbgCli_Topic::RootNode()->execute(argc, args_mmi_screen, 1);

  const char* args_mmi[] = {"mmi"};
  argc = 1;
  printf("\n%d\n", argc);
  DbgCli_Topic::RootNode()->execute(argc, args_mmi, 1);

  return 0;
}


