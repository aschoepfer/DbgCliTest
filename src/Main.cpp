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
  DbgCli_Topic* rootNode = new DbgCli_Topic(0, "mmi", "MMI node.");
  DbgCli_Node::AssignRootNode(static_cast<DbgCli_Node*>(rootNode));
  printf("MMI Node: %s\n", DbgCli_Node::RootNode()->getNodeName());
  printf("MMI Helptext: %s\n", DbgCli_Node::RootNode()->getHelpText());

  printf("\n*ADD TOPIC*\n");
  DbgCli_Topic* screenNode = new DbgCli_Topic(rootNode, "screen", "Screen Node.");
  printf("Screen Node: %s\n", screenNode->getNodeName());
  printf("Screen Helptext: %s\n", screenNode->getHelpText());

  printf("\n*ADD COMMAND*\n");
  DbgCli_Node* showCmd = new DbgCli_Command(screenNode, "show", "Show Node, shows current screen.");
  printf("MMI Screen Show Node: %s\n", showCmd->getNodeName());
  printf("Show Helptext: %s\n", showCmd->getHelpText());

  printf("\n*ADD OTHER BRANCH*\n");
  DbgCli_Topic* sensorA = new DbgCli_Topic(rootNode, "sensorA", "This is Sensor A");
  DbgCli_Topic* subX = new DbgCli_Topic(sensorA, "subX", "subsystem x of sensor A");
  DbgCli_Topic* topicY = new DbgCli_Topic(subX, "topicY", "TopicY in subsystemX of sensor A");
  new DbgCli_Command(subX, "commandZ", "CommandZ in subsystemX of sensor A");
  printf("TopicY Node: %s\n", topicY->getNodeName());
  printf("TopicY Helptext: %s\n", topicY->getHelpText());
  printf("----\n");

  printf("\n*GET EXISTING NODE*\n");
  DbgCli_Node* tmpNode = DbgCli_Node::RootNode()->getChildNode("screen");
  printf("MMI Node: %s\n", tmpNode->getNodeName());
  printf("MMI Helptext: %s\n", tmpNode->getHelpText());

  tmpNode = tmpNode->getChildNode("show");
  printf("MMI Screen Node: %s\n", tmpNode->getNodeName());
  printf("Screen Helptext: %s\n", tmpNode->getHelpText());
  printf("----\n");

  printf("\n*EXECUTE NODES*");
  const char* args_mmi_screen_show[] = {"mmi", "screen", "show"};
  unsigned int argc = 3;
  printf("\nAccess all nodes\n");
  DbgCli_Node::RootNode()->execute(argc, args_mmi_screen_show, 1);

  const char* args_mmi_screen[] = {"mmi", "screen"};
  argc = 2;
  printf("\nAccess node in the middle\n");
  DbgCli_Node::RootNode()->execute(argc, args_mmi_screen, 1);

  const char* args_mmi[] = {"mmim"};
  argc = 1;
  printf("\nAccess invalid root node\n");
  DbgCli_Node::RootNode()->execute(argc, args_mmi, 0);

  const char* args_mmi_screeni[] = {"mmi", "screeni"};
  argc = 2;
  printf("\nAccess invalid node\n");
  DbgCli_Node::RootNode()->execute(argc, args_mmi_screeni, 1);

  const char* args_branch2_subX[] = {"mmi", "sensorA", "subX"};
  argc = 3;
  printf("\nAccess middle node from other branch\n");
  DbgCli_Node::RootNode()->execute(argc, args_branch2_subX, 1);

  const char* args_branch2_topicY[] = {"mmi", "sensorA", "subX", "topicY"};
  argc = 4;
  printf("\nAccess last node from other branch\n");
  DbgCli_Node::RootNode()->execute(argc, args_branch2_topicY, 1);

  return 0;
}


