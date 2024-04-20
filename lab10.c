#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie{	
	struct Trie *next[26];
	int num;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
	struct Trie* createTrie();

	for(int i = 0; word[i] != '\0'; i++){
		int k = word[i] - 'a';

		if(pTrie->next[k] == NULL){
			pTrie->next[k] = createTrie();
		}

		pTrie = pTrie->next[k];
	}
	pTrie->num++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word){
	for(int i = 0; word[i] != '\0'; i++){
		int k = word[i] - 'a';

		if(pTrie->next[k] == NULL){
			return 0 ;
		}
		pTrie = pTrie->next[k];
	}
	return pTrie->num;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie){
	for(int i = 0; i < 26; i++){
		free(pTrie->next[i]);
	}
	
	free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie(){
	struct Trie* myTree = malloc(sizeof(struct Trie));
	myTree->num = 0;

	for(int i = 0; i < 26; i++){
		myTree->next[i] = NULL;
	}

	return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){
	FILE* file = fopen(filename, "r");
	
	if(file == NULL){
		printf("No file found.\n");
		return 0;
	}

	int num;
	fscanf(file, "%d", &num);

	for(int i = 0; i < num; i++){
		pInWords[i] = (char*)malloc(256 * sizeof(char));
		fscanf(file, "%s", pInWords[i]);
	}

	fclose(file);
	return num;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}

	pTrie = deallocateTrie(pTrie);

	if (pTrie != NULL){
		//printf("There is an error in this program\n");
	}
	return 0;
}