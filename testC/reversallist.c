listNode *reversalList(listNode *head){
	listNode *pNode = head;
	listNode *pPrev = NULL;

	while(pNode != NULL){
		listNode *pNext = pNode->next;
		pNode->next = pPrev;
		pPrev = pNode;
		pNode = pNext;
	}
	return pPrev;	//pNext = NULL;
}