#include "AIN.h"
#include <cstdio>

NodeGraph::NodeGraph(){
	m_ainetVer=0;
	m_mapVer=0;
		
	m_numOfNodes=0;
	m_numOfLinks=0;
		
	m_pNodes=NULL;
	m_pLinks=NULL;
}

bool NodeGraph::loadAIN(char* filename){
	FILE *fp = NULL;
	if((fp= fopen(filename, "rb"))==NULL){
		fprintf(stderr,"Couldn't load the file.\n");
		return false;
	}
	
	AIN_header header = {0,0};
	fread(&header,1,sizeof(AIN_header),fp);
	printf("ainet_ver: %d, map_ver: %d\n",header.ainet_ver,header.map_ver);
	
	fread(&m_numOfNodes, 1, sizeof(int),fp);
	printf("Number of Nodes: %d\n",m_numOfNodes);
	m_pNodes = new AIN_Node[m_numOfNodes];
	fread(m_pNodes,m_numOfNodes,61,fp);
	
	fread(&m_numOfLinks,1,sizeof(int),fp);
	printf("Number of Links: %d\n",m_numOfLinks);
	m_pLinks = new AIN_Link[m_numOfLinks];
	fread(m_pLinks,m_numOfLinks,sizeof(AIN_Link),fp);
	fclose(fp);
	return true;
}

void NodeGraph::printNodes(){
	printf("There are %d nodes in the Nodegraph\n",m_numOfNodes);
	for(int i=0;i<m_numOfNodes;i++){
		printNode(i);
	}
}

void NodeGraph::printLinks(){
	printf("There are %d links in the Nodegraph\n",m_numOfLinks);
	for(int i=0;i<m_numOfLinks;i++){
		printLink(i);
	}
}

void NodeGraph::printNode(int nodeID){
	printf("Node %d {\n",nodeID);
	AIN_Node node = m_pNodes[nodeID];
	printf("    Position: [%f, %f, %f]\n",node.x,node.y,node.z);
	printf("    Yaw: %f\n",node.yaw);
	printf("    flOffset: {\n");
	for(int j=0;j<NUM_HULLS;j++){
		printf("        %f\n",node.flOffsets[j]);
	}
	printf("}\n    nodeType: %u\n",node.nodeType);
	printf("    nodeInfo: %d\n",node.nodeInfo);
	printf("    zone: %d\n",node.zone);
	printf("}\n");
}

void NodeGraph::printLink(int linkID){
	AIN_Link link = m_pLinks[linkID];
	printf("Link %d goes from %d to %d. {\n",linkID,link.srcId,link.destId);
	AIN_Node a = m_pNodes[link.srcId];
	AIN_Node b = m_pNodes[link.destId];
	printf("[%f, %f, %f]\n",a.x,a.y,a.z);
	printf("[%f, %f, %f]\n}\n",b.x,b.y,b.z);
}

NodeGraph::~NodeGraph(){
	if(m_pNodes){
		delete [] m_pNodes;
	}
	
	if(m_pLinks){
		delete [] m_pLinks;
	}
}