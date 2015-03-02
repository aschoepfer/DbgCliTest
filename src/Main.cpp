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
/**
 * Test Tree
 *
 *            mmi (root)
 *            /
 *        screen-------sensorA   (sibling of screen)
 *          /              \
 *    show (command)      subX
 *                           \
 *                         topicY----topicZ
 */



  printf("*CREATE ROOT NODE*\n");
  DbgCli_Node* rootNode = new DbgCli_Topic("", "mmi", "MMI node.");
  DbgCli_Node::AssignRootNode(rootNode);
  printf("MMI Node: %s\n", DbgCli_Node::RootNode()->getNodeName());
  printf("%s - %s - %s\n", DbgCli_Node::RootNode()->getParentPath(), DbgCli_Node::RootNode()->getNodeName(), DbgCli_Node::RootNode()->getHelpText());

  printf("\n*ADD TOPIC*\n");
  DbgCli_Node* screenNode = new DbgCli_Topic("mmi", "screen", "Screen Node.");
  printf("MMI Screen Node: %s\n", screenNode->getNodeName());
  printf("%s - %s - %s\n", screenNode->getParentPath(), screenNode->getNodeName(), screenNode->getHelpText());

  printf("\n*ADD COMMAND*\n");
  DbgCli_Node* showCmd = new DbgCli_Command("mmi screen", "show", "Show Node, shows current screen.");
  printf("MMI Screen Show Node: %s\n", showCmd->getNodeName());
  printf("%s - %s - %s\n", showCmd->getParentPath(), showCmd->getNodeName(), showCmd->getHelpText());

  printf("\n*ADD OTHER BRANCH*\n");
  new DbgCli_Topic("mmi", "sensorA", "This is Sensor A");
  new DbgCli_Topic("mmi sensorA", "subX", "subsystem x of sensor A");
  DbgCli_Node* topicY = new DbgCli_Topic("mmi sensorA subX", "topicY", "TopicY in subsystemX of sensor A");
  new DbgCli_Command("mmi sensorA subX", "topicZ", "TopicZ in subsystemX of sensor A");
  printf("TopicY Node: %s\n", topicY->getNodeName());
  printf("%s - %s - %s\n", topicY->getParentPath(), topicY->getNodeName(), topicY->getHelpText());
  printf("----\n");

  printf("\n*GET EXISTING NODE*\n");
  DbgCli_Node* tmpNode = DbgCli_Node::RootNode()->getChildNode("screen");
  printf("MMI Node: %s\n", tmpNode->getNodeName());
  printf("%s - %s - %s\n", tmpNode->getParentPath(), tmpNode->getNodeName(), tmpNode->getHelpText());

  tmpNode = tmpNode->getChildNode("show");
  printf("MMI Screen Node: %s\n", tmpNode->getNodeName());
  printf("%s - %s - %s\n", tmpNode->getParentPath(), tmpNode->getNodeName(), tmpNode->getHelpText());
  printf("----\n");

  printf("\n*EXECUTE NODES*");
  const char* args_mmi_screen_show[] = {"mmi", "screen", "show"};
  unsigned int argc = 3;
  printf("\nAccess all nodes\n");
  DbgCli_Topic::RootNode()->execute(argc, args_mmi_screen_show, 1);

  const char* args_mmi_screen[] = {"mmi", "screen"};
  argc = 2;
  printf("\nAccess node in the middle\n");
  DbgCli_Topic::RootNode()->execute(argc, args_mmi_screen, 1);

  const char* args_mmi[] = {"mmim"};
  argc = 1;
  printf("\nAccess invalid root node\n");
  DbgCli_Topic::RootNode()->execute(argc, args_mmi, 0);

  const char* args_mmi_screeni[] = {"mmi", "screeni"};
  argc = 2;
  printf("\nAccess invalid node\n");
  DbgCli_Topic::RootNode()->execute(argc, args_mmi_screeni, 1);

  const char* args_branch2_subX[] = {"mmi", "sensorA", "subX"};
  argc = 3;
  printf("\nAccess middle node from other branch\n");
  DbgCli_Topic::RootNode()->execute(argc, args_branch2_subX, 1);

  const char* args_branch2_topicY[] = {"mmi", "sensorA", "subX", "topicY"};
  argc = 4;
  printf("\nAccess last node from other branch\n");
  DbgCli_Topic::RootNode()->execute(argc, args_branch2_topicY, 1);

  return 0;
}


