#pragma once

#include <stdio.h>

#define NUM_HULLS 10	//Valve Developer Wiki states this is almost always 10.


struct AIN_header {
	unsigned int ainet_ver;
	unsigned int map_ver;
};

#pragma pack(push,1)
struct AIN_Node {
	float x;
	float y;
	float z;
	float yaw;
	float flOffsets[NUM_HULLS];
	char nodeType;
	unsigned short nodeInfo;
	short zone;
};
#pragma pack(pop)
static_assert(sizeof(AIN_Node)==61);

#pragma pack(push,1)
struct AIN_Link {
	short srcId;
	short destId;
	char moves[NUM_HULLS];
};
#pragma pack(pop)
static_assert(sizeof(AIN_Link)==14);


class NodeGraph {
public:
	NodeGraph();
	~NodeGraph();
	bool loadAIN(char* filename);
	void printNodes();
	void printLinks();
	
	void printNode(int nodeID);
	void printLink(int linkID);
private:
	int m_ainetVer;	//AIN file version
	int m_mapVer;	//Map version
	
	int m_numOfNodes;	//Number of navigation nodes
	int m_numOfLinks;	//Number of node links
	
	AIN_Node *m_pNodes;
	AIN_Link *m_pLinks;
};
